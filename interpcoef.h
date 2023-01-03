#ifndef INTERPCOEF_H
#define INTERPCOEF_H
#include <QDebug>

#include	<float.h>
#include	<math.h>
#include	<stddef.h>
#include	<stdio.h>
#include	<stdlib.h>
#include "opencv2/opencv.hpp"
class interpCoef
{

public:
    interpCoef();

    //void computeCoefMatrix(cv::Mat* image);
    int SamplesToCoefficients(
            cv::Mat* ImageMat,		/* in-place processing */
            long	SplineDegree/* degree of the spline model */
            );


private:

    static void ConvertToInterpolationCoefficients
                    (
                        double	c[],		/* input samples --> output coefficients */
                        long	DataLength,	/* number of samples or coefficients */
                        double	z[],		/* poles */
                        long	NbPoles,	/* number of poles */
                        double	Tolerance	/* admissible relative error */
                    );


    static void GetColumn
                    (
                        float	*Image,		/* input image array */
                        long	Width,		/* width of the image */
                        long	x,			/* x coordinate of the selected line */
                        double	Line[],		/* output linear array */
                        long	Height		/* length of the line and height of the image */
                    );

    /*--------------------------------------------------------------------------*/
    static void		GetRow
                    (
                        float	*Image,		/* input image array */
                        long	y,			/* y coordinate of the selected line */
                        double	Line[],		/* output linear array */
                        long	Width		/* length of the line and width of the image */
                    );

    /*--------------------------------------------------------------------------*/
    static double	InitialCausalCoefficient
                    (
                        double	c[],		/* coefficients */
                        long	DataLength,	/* number of coefficients */
                        double	z,			/* actual pole */
                        double	Tolerance	/* admissible relative error */
                    );

    /*--------------------------------------------------------------------------*/
    static double	InitialAntiCausalCoefficient
                    (
                        double	c[],		/* coefficients */
                        long	DataLength,	/* number of samples or coefficients */
                        double	z			/* actual pole */
                    );

    /*--------------------------------------------------------------------------*/
    static void		PutColumn
                    (
                        float	*Image,		/* output image array */
                        long	Width,		/* width of the image */
                        long	x,			/* x coordinate of the selected line */
                        double	Line[],		/* input linear array */
                        long	Height		/* length of the line and height of the image */
                    );

    /*--------------------------------------------------------------------------*/
    static void		PutRow
                    (
                        float	*Image,		/* output image array */
                        long	y,			/* y coordinate of the selected line */
                        double	Line[],		/* input linear array */
                        long	Width		/* length of the line and width of the image */
                    );
};

#endif // INTERPCOEF_H
