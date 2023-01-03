#ifndef NLOPTIMIZER_H
#define NLOPTIMIZER_H
#include <QDebug>
#include <QRunnable>
#include <QMutex>
#include <QElapsedTimer>

#include "interpolator.h"
#include "qobject.h"

class interpCoef;
class interpolator;

class nlOptimizer: public QObject, public QRunnable
{
    Q_OBJECT
    /// Interpolation degree
    /// 1:bilinear, 3,5,7,9: B-spline of that degree
    int interpolationDegree;
    /// B-Spline coefficients of the reference and current images
    /// (should be image itself if interpolationDegree = 1)
    cv::Mat refCoeffs;
    cv::Mat currentCoeffs;

    // Mutex
    QMutex mutex;

    /// Subset Width
    int subsetSize;

    /// Number of pixels in the subset
    int nPixels;

    /// Max number of iterations
    int maxIter;

    /// Convergence tolerance
    double tolConvergence;

    /// Initial coordinates of the subset
    /// (npoints x 1 matrix, x stored in channel[0] and y stored in channel[1])
    cv::Mat refPointsInit;


    /// Center of the subset
    cv::Point2i subsetCenter;



    /// Deformed coordinates of the reference subset and current subset
    cv::Mat refPointsDeformed;
    cv::Mat currentPointsDeformed;

    /// Gray values associated with refPointsDeformed
    /// and currentPointsDeformed
    cv::Mat refGray;
    cv::Mat currentGray;

    /// First spatial derivatives of the Gray values
    /// associated with refPointsDeformed and currentPointsDeformed
    /// Col 0: dX, Col 1: dY
    cv::Mat diffRefGray;
    //cv::Mat diffCurrentGray;


    /// Norms of the reference and current gray arrays
    double refNorm;
    double currentNorm;


    /// warp matrices:
    /// dst(x,y) = src(M_00*x+M_01*y +M_02,
    ///                M_10*x+M_11*y+M_12)
    /// Warp for the reference image
    cv::Matx23d warpRef;
    /// Warp for the current image
    cv::Matx23d warpCurrent;

    cv::Matx23d referenceWarp;


    ///Correlation coefficient
    double correlCoef;

    /// d(grayref)/dwarp
    cv::Mat dRefdWarp;


    double meanRefGray;
    double meanCurrentGray;

    /// Pointer to interpolator
    interpolator *interpolate;

    /// Gradient vector
    cv::Matx61d gradient;
    ///Hessian matrix
    cv::Matx66d hessian;

    /// Convergence flag
    int convergence;

    double convergenceRatio;
    double poorConvergenceRatio;

public:
    static const int CONVERGED = 1;
    static const int NO_CONVERGENCE = 0;
    static const int POOR_CONVERGENCE = 2;

    struct subsetProperties {
        cv::Point2i center;
        cv::Matx23d warp;
        cv::Matx23d prevWarp; //Previous warp used for updated reference
        double corrCoef;
        double prevCorrCoef; //Previous corr. coef for updated reference.
        int converged;
        bool operator < (const subsetProperties  &a) const
        {
            return corrCoef < a.corrCoef;
        }
    };
    subsetProperties subsetToBeSolved;

    nlOptimizer(subsetProperties subsetToBeSolved,
                int subsetSizeInput, int interpolationDegreeInput, double tolConvergenceInput, int maxIterInput, double corrRejection,
                cv::Mat &refCoeffsInput, cv::Mat &currentCoeffsInput);

    void run();
    void grayInterp(cv::Mat* subsetPoints, cv::Mat image, int getDiff, cv::Mat* grayValue, cv::Mat *diffGray);

    /// Get the warp of the current image subset
    cv::Matx23d getWarp();

    /// Computes the warp of a warp
    static cv::Matx23d warpOfWarp(cv::Matx23d leftSide, cv::Matx23d rightSide);

    /// Get the convergence Status
    int getConvergence();
    /// Get the correlation coefficient
    double getCorrCoef();

    ~nlOptimizer();


private:

    /// Computes the gray values of the reference
    /// configuration and the current configuration
    void grayRef();
    void grayCurrent();


    /// Computes the optimisation coefficient
    void correlCoefCompute();


    /// Computes the Hessian matrix
    void hessianCompute();

    /// Computes the gradient
    void gradientCompute();

    /// Clear all members
    void clear();

signals:
    void finished();

};

#endif // NLOPTIMIZER_H
