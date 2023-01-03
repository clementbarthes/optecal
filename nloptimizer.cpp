#include "nloptimizer.h"


nlOptimizer::nlOptimizer(subsetProperties subsetToBeSolved,
                         int subsetSizeInput, int interpolationDegreeInput, double tolConvergenceInput, int maxIterInput,
                         double corrRejection, cv::Mat& refCoeffsInput, cv::Mat& currentCoeffsInput)
{


    // Initialize the convergence ratios
    convergenceRatio = corrRejection;
    poorConvergenceRatio = .8;

    this->subsetToBeSolved = subsetToBeSolved;
    subsetSize = subsetSizeInput;
    nPixels = subsetSize*subsetSize;
    refPointsInit = cv::Mat(nPixels,1,CV_64FC2);
    currentCoeffs = currentCoeffsInput;
    refCoeffs = refCoeffsInput;
    int nPx = 0;
    for(int i=-subsetSize/2;i<=subsetSize/2;++i){
        for(int j=-subsetSize/2;j<=subsetSize/2;++j){
            refPointsInit.at<cv::Vec2d>(nPx,0) = cv::Point2d(i,j);
            nPx += 1;
        }
    }

    cv::transform(refPointsInit,refPointsInit,subsetToBeSolved.prevWarp);
    interpolationDegree = interpolationDegreeInput;
    tolConvergence = tolConvergenceInput;
    maxIter = maxIterInput;
    subsetCenter = subsetToBeSolved.center;
    warpCurrent = subsetToBeSolved.warp;

    convergence = NO_CONVERGENCE;
    interpolate = new interpolator();

}

nlOptimizer::~nlOptimizer()
{ 

    delete interpolate;
    refCoeffs.release();
    currentCoeffs.release();
    refPointsInit.release();
    refPointsDeformed.release();
    currentPointsDeformed.release();
    refGray.release();
    currentGray.release();
    diffRefGray.release();
    dRefdWarp.release();
}

void nlOptimizer::run()
{

    cv::Matx61d deltaWarp;
    //cv::Matx33d deltaWarpMtx = cv::Matx33d::eye();
    int k = 0;
    double normDeltaWarp = 1.;

    refGray = cv::Mat::zeros(nPixels,1,CV_64F);
    currentGray = cv::Mat::zeros(nPixels,1,CV_64F);
    diffRefGray = cv::Mat::zeros(nPixels,2,CV_64F);
    //diffCurrentGray = cv::Mat::zeros(nPixels,2,CV_64F);
    dRefdWarp = cv::Mat::zeros(nPixels,6,CV_64F);

    // Compute the current Points location
    cv::transform(refPointsInit,currentPointsDeformed,warpCurrent);

    // Compute F, G and dG/dX
    nlOptimizer::grayRef();
    nlOptimizer::grayCurrent();




    // Compute Correl. coef.
    correlCoefCompute();

    qDebug() << "Corr coef: "<< correlCoef;

    // Compute Hessian
    hessianCompute();

    cv::Matx66d invertedHessian = hessian.inv(cv::DECOMP_CHOLESKY);

//    double kappa = 0.;
//    double kappaMax = 20.;
//    double dampingRatio = 2.;

    while(normDeltaWarp>tolConvergence && k< maxIter){ //
        ++k;

//        double prevCorrCoef = correlCoef;
        // Compute gradient
        gradientCompute();
        // Compute deltaWarp
        deltaWarp = invertedHessian*gradient;
        //deltaWarp = (hessian+kappa*cv::Matx66d::eye()).inv(cv::DECOMP_CHOLESKY)*gradient;

//        qDebug() << "p0" << deltaWarp(0,0) << "p1" << deltaWarp(1,0);
//        qDebug() << "p2" << deltaWarp(2,0) << "p3" << deltaWarp(3,0);
//        qDebug() << "p4" << deltaWarp(4,0) << "p5" << deltaWarp(5,0);

        // Update warp parameters
        normDeltaWarp = cv::norm(deltaWarp);

//        deltaWarpMtx(0,2) = deltaWarp(0,0); deltaWarpMtx(1,2) = deltaWarp(1,0);
//        deltaWarpMtx(0,0) = 1. + deltaWarp(2,0); deltaWarpMtx(0,1) = deltaWarp(3,0);
//        deltaWarpMtx(1,0) = deltaWarp(4,0); deltaWarpMtx(1,1) = 1. + deltaWarp(5,0);

        cv::Matx23d invDeltaWarp;
        cv::Matx22d invTemp(1.+deltaWarp(5,0),-deltaWarp(3,0),
                                 -deltaWarp(4,0),1.+deltaWarp(2,0));

        invTemp = (1./((1.+deltaWarp(2,0))*(1.+deltaWarp(5,0))-
                           deltaWarp(3,0)*deltaWarp(4,0)))*invTemp;

        invDeltaWarp(0,0) = invTemp(0,0);invDeltaWarp(0,1) = invTemp(0,1);
        invDeltaWarp(1,0) = invTemp(1,0);invDeltaWarp(1,1) = invTemp(1,1);
        invDeltaWarp(0,2) = (-invTemp.get_minor<1,2>(0,0)*deltaWarp.get_minor<2,1>(0,0))(0,0);
        invDeltaWarp(1,2) = (-invTemp.get_minor<1,2>(1,0)*deltaWarp.get_minor<2,1>(0,0))(0,0);

        warpCurrent = warpOfWarp(warpCurrent,invDeltaWarp);
        // Compute the current Points location
        cv::transform(refPointsInit,currentPointsDeformed,warpCurrent);

        // Compute G and dG/dX
        //grayRef();
        nlOptimizer::grayCurrent();

        // Compute Correl. coef.
        //correlCoefCompute();
//        if(correlCoef < prevCorrCoef){
//            kappa *= 1./dampingRatio;
//        } else if (kappa < kappaMax){
//            kappa *= dampingRatio;
//        }
//        qDebug() << "Norm: "<< normDeltaWarp;


    }

    // Compute Correl. coef.
    correlCoefCompute();

    if (correlCoef < convergenceRatio) {
        convergence = CONVERGED;
    } else if (correlCoef < poorConvergenceRatio){
        convergence = POOR_CONVERGENCE;
    } else {
        convergence = NO_CONVERGENCE;
    }
    qDebug() << "Iter: " << k << "Corr. coef: " <<correlCoef
                << "Convergence ratio: " << convergenceRatio;
    subsetToBeSolved.warp = warpCurrent;
    subsetToBeSolved.corrCoef = correlCoef;
    subsetToBeSolved.converged = convergence;
    emit finished();
}

cv::Matx23d nlOptimizer::warpOfWarp(cv::Matx23d leftSide, cv::Matx23d rightSide)
{
    cv::Matx23d outputMat;
    outputMat(0,0) = leftSide(0,0)*rightSide(0,0) + leftSide(0,1)*rightSide(1,0);
    outputMat(0,1) = leftSide(0,0)*rightSide(0,1) + leftSide(0,1)*rightSide(1,1);
    outputMat(1,0) = leftSide(1,0)*rightSide(0,0) + leftSide(1,1)*rightSide(1,0);
    outputMat(1,1) = leftSide(1,0)*rightSide(0,1) + leftSide(1,1)*rightSide(1,1);
    outputMat(0,2) = leftSide(0,0)*rightSide(0,2) + leftSide(0,1)*rightSide(1,2) + leftSide(0,2);
    outputMat(1,2) = leftSide(1,0)*rightSide(0,2) + leftSide(1,1)*rightSide(1,2) + leftSide(1,2);
    return outputMat;
}
void nlOptimizer::grayInterp(cv::Mat* subsetPoints, cv::Mat image, int getDiff, cv::Mat* grayValue, cv::Mat* diffGray = 0)
{


    cv::Mat_<cv::Vec2d>::iterator coordPtr = subsetPoints->begin<cv::Vec2d>(),
            itEnd = subsetPoints->end<cv::Vec2d>();
    int iIndex = 0;
    if (nlOptimizer::interpolationDegree == 1){
        // Bilinear interpolation
        cv::Matx12d bilinKernelX;
        cv::Matx21d bilinKernelY;
        cv::Matx22d imageCrop;
        for(;coordPtr!=itEnd;++coordPtr,++iIndex){
            bilinKernelX(0,1) = (*coordPtr)[0] - floor((*coordPtr)[0]);
            bilinKernelX(0,0) = 1-bilinKernelX(0,1);
            bilinKernelY(1,0) = (*coordPtr)[1] - floor((*coordPtr)[1]);
            bilinKernelY(0,0) = 1 - bilinKernelY(1,0);
            imageCrop = cv::Matx22d(image(cv::Rect(floor((*coordPtr)[0] + subsetCenter.x),
                                             floor((*coordPtr)[1] + subsetCenter.y),2,2)));
            grayValue->at<double>(iIndex,0) = (bilinKernelX*imageCrop*bilinKernelY)(0,0);
            if(getDiff){
                diffGray->at<double>(iIndex,0) = (cv::Matx12d(-1.,1.)*imageCrop*bilinKernelY)(0,0);
                diffGray->at<double>(iIndex,1) = (bilinKernelX*imageCrop*cv::Matx21d(-1.,1.))(0,0);
            }
        }
    } else{
        for(;coordPtr!=itEnd;++coordPtr,++iIndex){
            grayValue->at<double>(iIndex,0) =
                    interpolate->InterpolatedValue(&image, (*coordPtr)[0] + subsetCenter.x,(*coordPtr)[1] + subsetCenter.y, nlOptimizer::interpolationDegree);
            if(getDiff){
                diffGray->at<double>(iIndex,0) =
                        interpolate->InterpolatedDerivativeX(&image,(*coordPtr)[0] + subsetCenter.x,
                        (*coordPtr)[1] + subsetCenter.y, nlOptimizer::interpolationDegree);
                diffGray->at<double>(iIndex,1) =
                        interpolate->InterpolatedDerivativeY(&image,(*coordPtr)[0] + subsetCenter.x,
                        (*coordPtr)[1] + subsetCenter.y, nlOptimizer::interpolationDegree);
            }
        }
    }

}

void nlOptimizer::grayRef()
{
    cv::Mat onesMat = cv::Mat::ones(nPixels,1,CV_64F);
    /// Call the interpolator
    nlOptimizer::grayInterp(&refPointsInit, refCoeffs, 1 ,&refGray,&diffRefGray);

    //qDebug() << "ref"  << refPointsInit.at<double>(1,1);
    /// Subtract the mean
    meanRefGray = cv::mean(refGray)(0);
    refGray -= meanRefGray*onesMat;
    onesMat.release();

}

void nlOptimizer::grayCurrent()
{
    cv::Mat onesMat = cv::Mat::ones(nPixels,1,CV_64F);
    /// Call the interpolator
    nlOptimizer::grayInterp(&currentPointsDeformed, currentCoeffs, 0, &currentGray);
    //qDebug() << "current" << currentPointsDeformed.at<double>(1,1);
    /// Subtract the mean
    meanCurrentGray = cv::mean(currentGray)(0);
    currentGray -= meanCurrentGray*onesMat;
    onesMat.release();
    //meanGray.release();
}

void nlOptimizer::correlCoefCompute()
{
    cv::Mat mulSol = cv::Mat::zeros(nPixels,1,CV_64F);
    double fBarGBarOverGBarSquared;
    cv::Mat correlOut(1,1,CV_64F);
    cv::multiply(currentGray,refGray,mulSol);
    fBarGBarOverGBarSquared = cv::sum(mulSol)(0);
    cv::multiply(currentGray,currentGray,mulSol);
    fBarGBarOverGBarSquared *= 1./cv::sum(mulSol)(0);


    cv::mulTransposed(fBarGBarOverGBarSquared*currentGray/meanCurrentGray-refGray/meanRefGray,correlOut,true);
    correlCoef = correlOut.at<double>(0,0)/(double)refGray.rows;
    mulSol.release();
    correlOut.release();
}

void nlOptimizer::hessianCompute()
{
    cv::Mat Fx = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat Fy = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat x = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat y = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat mulSol = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat mulTransSol = cv::Mat::zeros(1,1,CV_64F);

    std::vector<cv::Mat> xAndY;
    xAndY.push_back(x);
    xAndY.push_back(y);
    cv::split(refPointsInit,xAndY);

    diffRefGray.col(0).copyTo(Fx.col(0));
    diffRefGray.col(1).copyTo(Fy.col(0));



    cv::mulTransposed(Fx,mulTransSol,true);
    hessian(0,0) = mulTransSol.at<double>(0,0);

    cv::mulTransposed(Fy,mulTransSol,true);
    hessian(1,1) = mulTransSol.at<double>(0,0);

    cv::multiply(Fx,Fy,mulSol);
    hessian(0,1) = sum(mulSol)(0);
    hessian(1,0) = hessian(0,1);

    cv::multiply(Fx,Fx,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(0,2) = sum(mulSol)(0);
    hessian(2,0) = hessian(0,2);

    cv::multiply(Fx,Fx,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(0,3) = sum(mulSol)(0);
    hessian(3,0) = hessian(0,3);

    cv::multiply(Fx,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(0,4) = sum(mulSol)(0);
    hessian(4,0) = hessian(0,4);

    cv::multiply(Fx,Fy,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(0,5) = sum(mulSol)(0);
    hessian(5,0) = hessian(0,5);

    hessian(1,2) = hessian(0,4);
    hessian(2,1) = hessian(1,2);
    hessian(1,3) = hessian(0,5);
    hessian(3,1) = hessian(1,3);


    cv::multiply(Fy,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(1,4) = sum(mulSol)(0);
    hessian(4,1) = hessian(1,4);

    cv::multiply(Fy,Fy,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(1,5) = sum(mulSol)(0);
    hessian(5,1) = hessian(1,5);

    cv::multiply(Fx,Fx,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(2,2) = sum(mulSol)(0);

    cv::multiply(Fx,Fx,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(2,3) = sum(mulSol)(0);
    hessian(3,2) = hessian(2,3);

    cv::multiply(Fx,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(2,4) = sum(mulSol)(0);
    hessian(4,2) = hessian(2,4);

    cv::multiply(Fx,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(2,5) = sum(mulSol)(0);
    hessian(5,2) = hessian(2,5);

    cv::multiply(Fx,Fx,mulSol);
    cv::multiply(mulSol,y,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(3,3) = sum(mulSol)(0);

    hessian(3,4) = hessian(2,5);
    hessian(4,3) = hessian(3,4);

    cv::multiply(Fx,Fy,mulSol);
    cv::multiply(mulSol,y,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(3,5) = sum(mulSol)(0);
    hessian(5,3) = hessian(3,5);

    cv::multiply(Fy,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,x,mulSol);
    hessian(4,4) = sum(mulSol)(0);

    cv::multiply(Fy,Fy,mulSol);
    cv::multiply(mulSol,x,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(4,5) = sum(mulSol)(0);
    hessian(5,4) = hessian(4,5);

    cv::multiply(Fy,Fy,mulSol);
    cv::multiply(mulSol,y,mulSol);
    cv::multiply(mulSol,y,mulSol);
    hessian(5,5) = sum(mulSol)(0);

    Fx.release();
    Fy.release();
    x.release();
    y.release();
    xAndY.clear();
    mulSol.release();
    mulTransSol.release();
}

void nlOptimizer::gradientCompute()
{
    cv::Mat Fx = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat Fy = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat x = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat y = cv::Mat::zeros(nPixels,1,CV_64F);
    cv::Mat mulSol = cv::Mat::zeros(nPixels,1,CV_64F);
    double fBarGBarOverGBarSquared;

    std::vector<cv::Mat> xAndY;
    xAndY.push_back(x);
    xAndY.push_back(y);
    cv::split(refPointsInit,xAndY);


    cv::multiply(currentGray,refGray,mulSol);
    fBarGBarOverGBarSquared = cv::sum(mulSol)(0);
    cv::multiply(currentGray,currentGray,mulSol);
    fBarGBarOverGBarSquared *= 1./cv::sum(mulSol)(0);

    diffRefGray.col(0).copyTo(Fx.col(0));
    diffRefGray.col(1).copyTo(Fy.col(0));

    cv::multiply(Fx,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(0,0) = sum(mulSol)(0);

    cv::multiply(Fy,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(1,0) = sum(mulSol)(0);

    cv::multiply(Fx,x,mulSol);
    cv::multiply(mulSol,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(2,0) = sum(mulSol)(0);

    cv::multiply(Fx,y,mulSol);
    cv::multiply(mulSol,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(3,0) = sum(mulSol)(0);

    cv::multiply(Fy,x,mulSol);
    cv::multiply(mulSol,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(4,0) = sum(mulSol)(0);

    cv::multiply(Fy,y,mulSol);
    cv::multiply(mulSol,fBarGBarOverGBarSquared*currentGray-refGray,mulSol);
    gradient(5,0) = sum(mulSol)(0);

    Fx.release();
    Fy.release();
    x.release();
    y.release();
    mulSol.release();
    xAndY.clear();
}

void nlOptimizer::clear()
{

}

cv::Matx23d nlOptimizer::getWarp()
{

    return warpCurrent;
}

int nlOptimizer::getConvergence()
{
    return convergence;
}

double nlOptimizer::getCorrCoef()
{
    return correlCoef;
}
