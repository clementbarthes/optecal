#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#include <QDebug>

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
class interpolator
{

public:
    interpolator();

    double	InterpolatedValue
    (
            cv::Mat* Bcoeff,	/* input B-spline array of coefficients */
            double	x,			/* x coordinate where to interpolate */
            double	y,			/* y coordinate where to interpolate */
            long	SplineDegree/* degree of the spline model */
            );

    double	InterpolatedDerivativeX
    (
            cv::Mat* Bcoeff,	/* input B-spline array of coefficients */
            double	x,			/* x coordinate where to interpolate */
            double	y,			/* y coordinate where to interpolate */
            long	SplineDegree/* degree of the spline model */
            );

    double	InterpolatedDerivativeY
    (
            cv::Mat* Bcoeff,	/* input B-spline array of coefficients */
            double	x,			/* x coordinate where to interpolate */
            double	y,			/* y coordinate where to interpolate */
            long	SplineDegree/* degree of the spline model */
            );
};

#endif // INTERPOLATOR_H
