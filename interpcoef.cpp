#include "interpcoef.h"

interpCoef::interpCoef()
{
}

//void interpCoef::computeCoefMatrix(cv::Mat *image)
//{
//    ///Define the 1D kernel
//    double testArray[] = {1./120, 13./60, 11./20, 13./60, 1./120};
//    cv::Mat kernel(5,1,CV_64FC1,testArray);
//    cv::sepFilter2D(*image,*image,-1,kernel,kernel.t());
////    (*image).convertTo(*image,CV_8U);
////    cv::namedWindow("Interpolated_Image",cv::WINDOW_AUTOSIZE);
////    cv::imshow("Interpolated_Image",*image);

//}


/*****************************************************************************
 *	Definition of static procedures
 ****************************************************************************/
/*--------------------------------------------------------------------------*/
void interpCoef::ConvertToInterpolationCoefficients
                (
                    double	c[],		/* input samples --> output coefficients */
                    long	DataLength,	/* number of samples or coefficients */
                    double	z[],		/* poles */
                    long	NbPoles,	/* number of poles */
                    double	Tolerance	/* admissible relative error */
                )

{ /* begin ConvertToInterpolationCoefficients */

    double	Lambda = 1.0;
    long	n, k;

    /* special case required by mirror boundaries */
    if (DataLength == 1L) {
        return;
    }
    /* compute the overall gain */
    for (k = 0L; k < NbPoles; k++) {
        Lambda = Lambda * (1.0 - z[k]) * (1.0 - 1.0 / z[k]);
    }
    /* apply the gain */
    for (n = 0L; n < DataLength; n++) {
        c[n] *= Lambda;
    }
    /* loop over all poles */
    for (k = 0L; k < NbPoles; k++) {
        /* causal initialization */
        c[0] = InitialCausalCoefficient(c, DataLength, z[k], Tolerance);
        /* causal recursion */
        for (n = 1L; n < DataLength; n++) {
            c[n] += z[k] * c[n - 1L];
        }
        /* anticausal initialization */
        c[DataLength - 1L] = InitialAntiCausalCoefficient(c, DataLength, z[k]);
        /* anticausal recursion */
        for (n = DataLength - 2L; 0 <= n; n--) {
            c[n] = z[k] * (c[n + 1L] - c[n]);
        }
    }
} /* end ConvertToInterpolationCoefficients */

/*--------------------------------------------------------------------------*/
double interpCoef::InitialCausalCoefficient
                (
                    double	c[],		/* coefficients */
                    long	DataLength,	/* number of coefficients */
                    double	z,			/* actual pole */
                    double	Tolerance	/* admissible relative error */
                )

{ /* begin InitialCausalCoefficient */

    double	Sum, zn, z2n, iz;
    long	n, Horizon;

    /* this initialization corresponds to mirror boundaries */
    Horizon = DataLength;
    if (Tolerance > 0.0) {
        Horizon = (long)ceil(log(Tolerance) / log(fabs(z)));
    }
    if (Horizon < DataLength) {
        /* accelerated loop */
        zn = z;
        Sum = c[0];
        for (n = 1L; n < Horizon; n++) {
            Sum += zn * c[n];
            zn *= z;
        }
        return(Sum);
    }
    else {
        /* full loop */
        zn = z;
        iz = 1.0 / z;
        z2n = pow(z, (double)(DataLength - 1L));
        Sum = c[0] + z2n * c[DataLength - 1L];
        z2n *= z2n * iz;
        for (n = 1L; n <= DataLength - 2L; n++) {
            Sum += (zn + z2n) * c[n];
            zn *= z;
            z2n *= iz;
        }
        return(Sum / (1.0 - zn * zn));
    }
} /* end InitialCausalCoefficient */

/*--------------------------------------------------------------------------*/
void interpCoef::GetColumn
                (
                    float	*Image,		/* input image array */
                    long	Width,		/* width of the image */
                    long	x,			/* x coordinate of the selected line */
                    double	Line[],		/* output linear array */
                    long	Height		/* length of the line */
                )

{ /* begin GetColumn */

    long	y;

    Image = Image + (ptrdiff_t)x;
    for (y = 0L; y < Height; y++) {
        Line[y] = (double)*Image;
        Image += (ptrdiff_t)Width;
    }
} /* end GetColumn */

/*--------------------------------------------------------------------------*/
void interpCoef::GetRow
                (
                    float	*Image,		/* input image array */
                    long	y,			/* y coordinate of the selected line */
                    double	Line[],		/* output linear array */
                    long	Width		/* length of the line */
                )

{ /* begin GetRow */

    long	x;

    Image = Image + (ptrdiff_t)(y * Width);
    for (x = 0L; x < Width; x++) {
        Line[x] = (double)*Image++;
    }
} /* end GetRow */

/*--------------------------------------------------------------------------*/
double interpCoef::InitialAntiCausalCoefficient
                (
                    double	c[],		/* coefficients */
                    long	DataLength,	/* number of samples or coefficients */
                    double	z			/* actual pole */
                )

{ /* begin InitialAntiCausalCoefficient */

    /* this initialization corresponds to mirror boundaries */
    return((z / (z * z - 1.0)) * (z * c[DataLength - 2L] + c[DataLength - 1L]));
} /* end InitialAntiCausalCoefficient */

/*--------------------------------------------------------------------------*/
void interpCoef::PutColumn
                (
                    float	*Image,		/* output image array */
                    long	Width,		/* width of the image */
                    long	x,			/* x coordinate of the selected line */
                    double	Line[],		/* input linear array */
                    long	Height		/* length of the line and height of the image */
                )

{ /* begin PutColumn */

    long	y;

    Image = Image + (ptrdiff_t)x;
    for (y = 0L; y < Height; y++) {
        *Image = (float)Line[y];
        Image += (ptrdiff_t)Width;
    }
} /* end PutColumn */

/*--------------------------------------------------------------------------*/
void interpCoef::PutRow
                (
                    float	*Image,		/* output image array */
                    long	y,			/* y coordinate of the selected line */
                    double	Line[],		/* input linear array */
                    long	Width		/* length of the line and width of the image */
                )

{ /* begin PutRow */

    long	x;

    Image = Image + (ptrdiff_t)(y * Width);
    for (x = 0L; x < Width; x++) {
        *Image++ = (float)Line[x];
    }
} /* end PutRow */

/*****************************************************************************
 *	Definition of extern procedures
 ****************************************************************************/
/*--------------------------------------------------------------------------*/
int interpCoef::SamplesToCoefficients
                (
                    cv::Mat* ImageMat,		/* in-place processing */
                    long	SplineDegree/* degree of the spline model */
                )

{ /* begin SamplesToCoefficients */

    double	*Line;
    double	Pole[4];
    float* Image = &(ImageMat->at<float>(0,0));
    long Width = ImageMat->cols;
    long Height = ImageMat->rows;
    long	NbPoles;
    long	x, y;

    /* recover the poles from a lookup table */
    switch (SplineDegree) {
        case 1L:
            return(0);
        case 3L:
            NbPoles = 1L;
            Pole[0] = sqrt(3.0) - 2.0;
            break;

        case 5L:
            NbPoles = 2L;
            Pole[0] = sqrt(135.0 / 2.0 - sqrt(17745.0 / 4.0)) + sqrt(105.0 / 4.0)
                - 13.0 / 2.0;
            Pole[1] = sqrt(135.0 / 2.0 + sqrt(17745.0 / 4.0)) - sqrt(105.0 / 4.0)
                - 13.0 / 2.0;
            break;

        case 7L:
            NbPoles = 3L;
            Pole[0] = -0.53528043079643816554240378168164607183392315234269;
            Pole[1] = -0.12255461519232669051527226435935734360548654942730;
            Pole[2] = -0.0091486948096082769285930216516478534156925639545994;
            break;

        case 9L:
            NbPoles = 4L;
            Pole[0] = -0.60799738916862577900772082395428976943963471853991;
            Pole[1] = -0.20175052019315323879606468505597043468089886575747;
            Pole[2] = -0.043222608540481752133321142979429688265852380231497;
            Pole[3] = -0.0021213069031808184203048965578486234220548560988624;
            break;
        default:
            printf("Invalid spline degree\n");
            return(1);
    }

    /* convert the image samples into interpolation coefficients */
    /* in-place separable process, along x */
    Line = (double *)malloc((size_t)(Width * (long)sizeof(double)));
    if (Line == (double *)NULL) {
        printf("Row allocation failed\n");
        return(1);
    }
    for (y = 0L; y < Height; y++) {
        GetRow(Image, y, Line, Width);
        ConvertToInterpolationCoefficients(Line, Width, Pole, NbPoles, DBL_EPSILON);
        PutRow(Image, y, Line, Width);
    }
    free(Line);

    /* in-place separable process, along y */
    Line = (double *)malloc((size_t)(Height * (long)sizeof(double)));
    if (Line == (double *)NULL) {
        printf("Column allocation failed\n");
        return(1);
    }
    for (x = 0L; x < Width; x++) {
        GetColumn(Image, Width, x, Line, Height);
        ConvertToInterpolationCoefficients(Line, Height, Pole, NbPoles, DBL_EPSILON);
        PutColumn(Image, Width, x, Line, Height);
    }
    free(Line);

    return(0);
} /* end SamplesToCoefficients */


