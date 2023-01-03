#include "displacements.h"
#include "staticreadwritefunctions.h"

displacements::displacements()
{
    medianFilterValue= 3;
    gaussianFilterValue = 3;
    correlClipVal = .05;
}

displacements::~displacements()
{
    clear();

}

void displacements::clear(){
    subsetPts.clear();
    correlCoef.release();
    dispU.release();
    dispV.release();
    rotation.release();
    coordX.release();
    coordY.release();
    Exx.release();
    Eyy.release();
    Exy.release();
    exx.release();
    eyy.release();
    exy.release();
    mask.release();
    warp00.release();
    warp01.release();
    warp02.release();
    warp10.release();
    warp11.release();
    warp12.release();
    dispUUser.release();
    dispVUser.release();
    E11User.release();
    E22User.release();
    E12User.release();
    EP1User.release();
    EP2User.release();
    ED1User.release();
    ED2User.release();
    EVM.release();
    ETresca.release();
    xRemap.release();
    yRemap.release();
    xResized.release();
    yResized.release();
    uResized.release();
    vResized.release();
    exxResized.release();
    eyyResized.release();
    exyResized.release();
    corrCoefResized.release();
    maskResized.release();
    maskDisplay.release();
    results.release();
    coordXUser.release();
    coordYUser.release();
    rotationOutput.release();
}

displacements& displacements::operator=(const displacements &other)
{
    subsetSize = other.subsetSize;
    subsetSpacing = other.subsetSpacing;
    medianFilterValue = other.medianFilterValue;
    gaussianFilterValue = other.gaussianFilterValue;
    correlClipVal = other.correlClipVal;
    memcpy(autoBounds,other.autoBounds,sizeof(double[15][2]));
    return *this;
}


cv::Mat displacements::getResults(int solFlag)
{
    switch(solFlag)
    {
    case getU:
        return warp02;
        break;
    case getV:
        return warp12;
        break;
    case getRot:
        return warp12;
        break;
    case getExx:
        return Exx;
        break;
    case getEyy:
        return Eyy;
        break;
    case getExy:
        return Exy;
        break;
    case getCorr:
        return correlCoef;
        break;
    case getX:
        return coordX;
        break;
    case getY:
        return coordY;
        break;
    case getMask:
        return mask;
        break;
    }
    return cv::Mat::zeros(1,1,CV_64F);
}

cv::Matx23d displacements::getWarp(int row, int col)
{
    cv::Matx23d warpOutput;
    warpOutput(0,0) = warp00.at<double>(row,col);
    warpOutput(0,1) = warp01.at<double>(row,col);
    warpOutput(0,2) = warp02.at<double>(row,col);
    warpOutput(1,0) = warp10.at<double>(row,col);
    warpOutput(1,1) = warp11.at<double>(row,col);
    warpOutput(1,2) = warp12.at<double>(row,col);
    return warpOutput;
}

double displacements::getCorrCoef(int row, int col)
{
    return correlCoef.at<double>(row,col);
}


std::vector<cv::Point2i> displacements::getResultsPts()
{
    return subsetPts;
}

void displacements::addSolution(int subsetSpacing, cv::Mat* currentImage , std::vector<nlOptimizer::subsetProperties> solution)
{

    //Initialize solution size (Image size divided by subset spscing)
    int solColumns = currentImage->cols/subsetSpacing;
    int solRows = currentImage->rows/subsetSpacing;
    correlCoef = cv::Mat::zeros(solRows,solColumns,CV_64F);
    dispU = cv::Mat::zeros(solRows,solColumns,CV_64F);
    dispV = cv::Mat::zeros(solRows,solColumns,CV_64F);
    rotation = cv::Mat::zeros(solRows,solColumns,CV_64F);
    coordX = cv::Mat::zeros(solRows,solColumns,CV_64F);
    coordY = cv::Mat::zeros(solRows,solColumns,CV_64F);
    mask = -1.*cv::Mat::ones(solRows,solColumns,CV_32F);
    warp00 = cv::Mat::ones(solRows,solColumns,CV_64F);
    warp01 = cv::Mat::zeros(solRows,solColumns,CV_64F);
    warp02 = cv::Mat::zeros(solRows,solColumns,CV_64F);
    warp10 = cv::Mat::zeros(solRows,solColumns,CV_64F);
    warp11 = cv::Mat::ones(solRows,solColumns,CV_64F);
    warp12 = cv::Mat::zeros(solRows,solColumns,CV_64F);

    nlOptimizer::subsetProperties solIdx;
    int solX, solY;
    cv::Matx23d globalWarp;


    for(int index = 0; index < (int)solution.size(); ++index)
    {
        solIdx = solution[index];
        globalWarp = nlOptimizer::warpOfWarp(solIdx.warp, solIdx.prevWarp);
        solX = solIdx.center.x/subsetSpacing;
        solY = solIdx.center.y/subsetSpacing;
        subsetPts.push_back(solIdx.center);
        warp00.at<double>(solY,solX) = globalWarp(0,0);
        warp01.at<double>(solY,solX) = globalWarp(0,1);
        warp02.at<double>(solY,solX) = globalWarp(0,2);
        warp10.at<double>(solY,solX) = globalWarp(1,0);
        warp11.at<double>(solY,solX) = globalWarp(1,1);
        warp12.at<double>(solY,solX) = globalWarp(1,2);

        coordX.at<double>(solY,solX) = (double)solIdx.center.x;
        autoBounds[6][1] = ((coordX.at<double>(solY,solX) > autoBounds[6][1]) || (index == 0) ? coordX.at<double>(solY,solX): autoBounds[6][1]);
        autoBounds[6][0] = ((coordX.at<double>(solY,solX) < autoBounds[6][0]) || (index == 0) ? coordX.at<double>(solY,solX): autoBounds[6][0]);

        coordY.at<double>(solY,solX) = (double)solIdx.center.y;
        autoBounds[7][1] = ((coordY.at<double>(solY,solX) > autoBounds[7][1]) || (index == 0) ? coordY.at<double>(solY,solX): autoBounds[7][1]);
        autoBounds[7][0] = ((coordY.at<double>(solY,solX) < autoBounds[7][0]) || (index == 0) ? coordY.at<double>(solY,solX): autoBounds[7][0]);

        correlCoef.at<double>(solY,solX) = (double)solIdx.corrCoef;
        autoBounds[5][1] = ((correlCoef.at<double>(solY,solX) > autoBounds[5][1]) || (index == 0) ? correlCoef.at<double>(solY,solX): autoBounds[5][1]);
        autoBounds[5][0] = ((correlCoef.at<double>(solY,solX) < autoBounds[5][0]) || (index == 0) ? correlCoef.at<double>(solY,solX): autoBounds[5][0]);

        dispU.at<double>(solY,solX) = (double)globalWarp(0,2);
        autoBounds[0][1] = ((dispU.at<double>(solY,solX) > autoBounds[0][1]) || (index == 0) ? dispU.at<double>(solY,solX): autoBounds[0][1]);
        autoBounds[0][0] = ((dispU.at<double>(solY,solX) < autoBounds[0][0]) || (index == 0) ? dispU.at<double>(solY,solX): autoBounds[0][0]);

        dispV.at<double>(solY,solX) = (double)globalWarp(1,2);
        autoBounds[1][1] = ((dispV.at<double>(solY,solX) > autoBounds[1][1]) || (index == 0) ? dispV.at<double>(solY,solX): autoBounds[1][1]);
        autoBounds[1][0] = ((dispV.at<double>(solY,solX) < autoBounds[1][0]) || (index == 0) ? dispV.at<double>(solY,solX): autoBounds[1][0]);



        mask.at<float>(solY,solX) = 1.;

    }
    //buildStrains();

    // Extend border pixel outside the mask to have better boundary conditions for filtering
    for (int j= 0; j<30 ; ++j) {
        //extendEdges(correlCoef);
        extendEdges(warp00);
        extendEdges(warp01);
        extendEdges(warp02);
        extendEdges(warp10);
        extendEdges(warp11);
        extendEdges(warp12);
        extendEdges(coordX);
        extendEdges(coordY);
    }


    solution.clear();
    currentImage->release();
}

void displacements::extendEdges(cv::Mat& image){
    cv::Mat result;
    result.create(image.size(), image.type());

    for(int j = 0; j < image.rows; ++j)
    {
        double* previous = image.ptr<double>(j - 1);
        double* current  = image.ptr<double>(j    );
        double* next;
        if((j+1) < image.rows)
            next = image.ptr<double>(j + 1);
        else
            next = image.ptr<double>(j);


        double* output = result.ptr<double>(j);
        double maxRow;
        double maxCol;
        for(int i = 0; i < (image.cols); ++i, ++output)
        {
            if (current[i] == 0.){
                if(i==0){
                    maxRow = current[i+1];
                } else if (i==(image.cols-1)){
                    maxRow = current[i-1];
                } else{
                    maxRow = abs(current[i-1]) > abs(current[i+1]) ?
                                current[i-1]:current[i+1];
                }
                if (j==0){
                    maxCol = next[i];
                } else if (j==(image.cols-1)){
                    maxCol = previous[i];
                }
                else {
                    maxCol = abs(previous[i]) > abs(next[i]) ? previous[i] : next[i];
                }
                *output = abs(maxRow) > abs(maxCol) ? maxRow : maxCol;

            } else {

                *output = current[i];

            }
        }
    }
    result.copyTo(image);
}



cv::Mat displacements::computeUserCoords(drawOrigin &originAndAxesLayer, int getCoordFlag)
{
    if (!originAndAxesLayer.flipXY)
    {
        coordXUser = coordX.clone();
        coordYUser = coordY.clone();
    } else {
        coordYUser = coordX.clone();
        coordXUser = coordY.clone();
    }
    // Adjust coord X and Y
    double angle = (double)originAndAxesLayer.getAngle();
    cv::Point2i origin;
    if (!originAndAxesLayer.flipXY){
        origin = originAndAxesLayer.getOrigin();
    } else {
        origin.x = originAndAxesLayer.getOrigin().y;
        origin.y = originAndAxesLayer.getOrigin().x;
    }

    if (originAndAxesLayer.polarCartFlag == drawOrigin::cartesianCoord){
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        cv::Mat_<double>::iterator coordXUserIter = coordXUser.begin<double>();
        cv::Mat_<double>::iterator coordYUserIter = coordYUser.begin<double>();
        switch (getCoordFlag){
        case getX:
            for(; coordXUserIter != coordXUser.end<double>(); ++coordXUserIter, ++coordYUserIter){
                *coordXUserIter = (*coordXUserIter - origin.x)*cosAngle + (*coordYUserIter - origin.y)*sinAngle;
            }
            return coordXUser;
            break;
        case getY:
            for(; coordXUserIter != coordXUser.end<double>(); ++coordXUserIter, ++coordYUserIter){
                *coordYUserIter = -(*coordXUserIter - origin.x)*sinAngle + (*coordYUserIter - origin.y)*cosAngle;
            }
            return coordYUser;
            break;
        }


    } else {
        const double PI = 3.141592653;
        cv::Mat_<double>::iterator coordXUserIter = coordXUser.begin<double>();
        cv::Mat_<double>::iterator coordYUserIter = coordYUser.begin<double>();
        switch (getCoordFlag){
        case getX:
            for(; coordXUserIter != coordXUser.end<double>(); ++coordXUserIter, ++coordYUserIter){
                *coordXUserIter = pow(pow((*coordXUserIter - origin.x),2) + pow((*coordYUserIter - origin.y),2),.5);
            }
            return coordXUser;
            break;
        case getY:
            for(; coordXUserIter != coordXUser.end<double>(); ++coordXUserIter, ++coordYUserIter){
                *coordYUserIter = atan2((*coordYUserIter - origin.y),(*coordXUserIter - origin.x))-angle;
                if (*coordYUserIter < -PI){
                    *coordYUserIter = fmod(*coordYUserIter - PI,2*PI) + PI;
                } else if( *coordYUserIter > PI){
                    *coordYUserIter = fmod(*coordYUserIter + PI,2*PI) - PI;
                }
            }
            coordYUser *= 180./PI;
            return coordYUser;
            break;
        }
    }

    return cv::Mat::zeros(coordX.rows,coordX.cols,coordX.type());
}

cv::Mat displacements::computeRotation(drawOrigin &originAndAxesLayer){
    const double PI = 3.141592653;
    rotationOutput = cv::Mat::zeros(warp00.size(),CV_64F);
    int multiplesOfPi = 0;
    cv::Mat_<double>::iterator rotIter = rotationOutput.begin<double>();
    cv::Mat_<double>::iterator warp00Iter = warp00.begin<double>();
    cv::Mat_<double>::iterator warp01Iter = warp01.begin<double>();
    cv::Mat_<double>::iterator warp10Iter = warp10.begin<double>();
    cv::Mat_<double>::iterator warp11Iter = warp11.begin<double>();

    for(; warp00Iter != warp00.end<double>(); ++warp00Iter, ++warp01Iter, ++warp10Iter,
        ++warp11Iter, ++rotIter){
        cv::Matx22d fMatrix(*warp00Iter,*warp01Iter, *warp10Iter, *warp11Iter);
        cv::Matx22d cMatrix;
        cv::Matx22d cMatSqrt(0.,0.,0.,0.);
        cv::mulTransposed(fMatrix, cMatrix, true);
        cv::Matx21d eigenVals;
        cv::Matx22d eigenVecs;
        if((cMatrix(0,0) !=0.) && (cMatrix(1,1) !=0.)){
            if(cv::eigen(cMatrix,eigenVals,eigenVecs)){
                cMatSqrt = eigenVecs.t()*
                        cv::Matx22d(sqrt(eigenVals(0,0)),0.,0.,sqrt(eigenVals(1,0)))*eigenVecs;
            }
        }
        cv::Matx22d rMat = fMatrix*cMatSqrt.inv();
        if(originAndAxesLayer.flipXY){
            *rotIter = -atan2(rMat(1,0),rMat(0,0));
        } else {
            *rotIter = atan2(rMat(1,0),rMat(0,0));
        }
        multiplesOfPi = ((int)abs(*rotIter/PI) > abs(multiplesOfPi)) ? (int)(*rotIter/PI) : multiplesOfPi;
    }

    rotationOutput -= cv::Mat::ones(rotationOutput.rows,rotationOutput.cols,CV_64F)*(multiplesOfPi)*PI;
    rotationOutput *= 180./PI;

 return rotationOutput;
}

cv::Mat displacements::computeUserDisplacements(
        drawOrigin &originAndAxesLayer, int getDispFlag){
    const double PI = 3.141592653;
    double angle = (double)originAndAxesLayer.getAngle();
    if (!originAndAxesLayer.flipXY)
    {
        dispUUser = warp02.clone();
        dispVUser = warp12.clone();
    } else {
        dispVUser = warp02.clone();
        dispUUser = warp12.clone();
    }
    cv::Mat_<double>::iterator dispUUserIter = dispUUser.begin<double>();
    cv::Mat_<double>::iterator dispVUserIter = dispVUser.begin<double>();
    if (originAndAxesLayer.polarCartFlag == drawOrigin::cartesianCoord){
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        switch (getDispFlag){
        case getU:
            for(; dispUUserIter != dispUUser.end<double>(); ++dispUUserIter, ++dispVUserIter){
                *dispUUserIter = (*dispUUserIter)*cosAngle + (*dispVUserIter)*sinAngle;
            }
            return dispUUser;
            break;
        case getV:
            for(; dispUUserIter != dispUUser.end<double>(); ++dispUUserIter, ++dispVUserIter){
                *dispVUserIter = -(*dispUUserIter)*sinAngle + (*dispVUserIter)*cosAngle;
            }
            return dispVUser;
            break;
        }
    }  else {
        cv::Mat coordYUser;
        coordYUser = PI/180.*computeUserCoords(originAndAxesLayer,getY);
        cv::Mat_<double>::iterator angleIter = coordYUser.begin<double>();
        switch (getDispFlag){
        case getU:
            for(; dispUUserIter != dispUUser.end<double>(); ++dispUUserIter, ++dispVUserIter, ++angleIter){
                *dispUUserIter = *dispUUserIter*cos(*angleIter) + *dispVUserIter*sin(*angleIter);
            }
            coordYUser.release();
            return dispUUser;
            break;
        case getV:
            for(; dispUUserIter != dispUUser.end<double>(); ++dispUUserIter, ++dispVUserIter, ++angleIter){
                *dispVUserIter =  -*dispUUserIter*sin(*angleIter) + *dispVUserIter*cos(*angleIter);
            }
            coordYUser.release();
            return dispVUser;
            break;
        }
    }
    return cv::Mat::zeros(warp00.rows,warp00.cols,warp00.type());
}



cv::Mat displacements::computeUserStrains(
        drawOrigin &originAndAxesLayer, int getStrainFlag){

    double angle = originAndAxesLayer.getAngle();
    if (!originAndAxesLayer.flipXY)
    {
        if(originAndAxesLayer.spatialCoordinates){
            E11User = exx.clone();
            E22User = eyy.clone();
            E12User = exy.clone();
        } else {
            E11User = Exx.clone();
            E22User = Eyy.clone();
            E12User = Exy.clone();
        }
    } else {
        if(originAndAxesLayer.spatialCoordinates){
            E11User = eyy.clone();
            E22User = exx.clone();
            E12User = exy.clone();
        } else {
            E11User = Eyy.clone();
            E22User = Exx.clone();
            E12User = Exy.clone();
        }
    }
    double tempMat11, tempMat12, tempMat21, tempMat22;
    cv::Mat_<double>::iterator E11UserIter = E11User.begin<double>();
    cv::Mat_<double>::iterator E22UserIter = E22User.begin<double>();
    cv::Mat_<double>::iterator E12UserIter = E12User.begin<double>();
    if (originAndAxesLayer.polarCartFlag == drawOrigin::cartesianCoord){
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        switch (getStrainFlag){
        case getExx:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cosAngle + *E12UserIter*sinAngle;
                tempMat12 = -*E11UserIter*sinAngle + *E12UserIter*cosAngle;
                tempMat21 = *E12UserIter*cosAngle + *E22UserIter*sinAngle;
                tempMat22 = -*E12UserIter*sinAngle + *E22UserIter*cosAngle;
                *E11UserIter = cosAngle*tempMat11 + sinAngle*tempMat21;
            }
            return E11User;
            break;
        case getEyy:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cosAngle + *E12UserIter*sinAngle;
                tempMat12 = -*E11UserIter*sinAngle + *E12UserIter*cosAngle;
                tempMat21 = *E12UserIter*cosAngle + *E22UserIter*sinAngle;
                tempMat22 = -*E12UserIter*sinAngle + *E22UserIter*cosAngle;
                *E22UserIter = -sinAngle*tempMat12 + cosAngle*tempMat22;
            }
            return E22User;
            break;
        case getExy:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cosAngle + *E12UserIter*sinAngle;
                tempMat12 = -*E11UserIter*sinAngle + *E12UserIter*cosAngle;
                tempMat21 = *E12UserIter*cosAngle + *E22UserIter*sinAngle;
                tempMat22 = -*E12UserIter*sinAngle + *E22UserIter*cosAngle;
                *E12UserIter = cosAngle*tempMat12 + sinAngle*tempMat22;
            }
            return E12User;
            break;
        }
    }  else {
        cv::Mat coordYUser;
        coordYUser = computeUserCoords(originAndAxesLayer,getY);
        cv::Mat_<double>::iterator angleIter = coordYUser.begin<double>();
        switch (getStrainFlag){
        case getExx:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cos(*angleIter) + *E12UserIter*sin(*angleIter);
                tempMat12 = -*E11UserIter*sin(*angleIter) + *E12UserIter*cos(*angleIter);
                tempMat21 = *E12UserIter*cos(*angleIter) + *E22UserIter*sin(*angleIter);
                tempMat22 = -*E12UserIter*sin(*angleIter) + *E22UserIter*cos(*angleIter);
                *E11UserIter = cos(*angleIter)*tempMat11 + sin(*angleIter)*tempMat21;
            }
            coordYUser.release();
            return E11User;
            break;
        case getEyy:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cos(*angleIter) + *E12UserIter*sin(*angleIter);
                tempMat12 = -*E11UserIter*sin(*angleIter) + *E12UserIter*cos(*angleIter);
                tempMat21 = *E12UserIter*cos(*angleIter) + *E22UserIter*sin(*angleIter);
                tempMat22 = -*E12UserIter*sin(*angleIter) + *E22UserIter*cos(*angleIter);
                *E22UserIter = -sin(*angleIter)*tempMat12 + cos(*angleIter)*tempMat22;
            }
            coordYUser.release();
            return E22User;
            break;
        case getExy:
            for(; E11UserIter != E11User.end<double>(); ++E11UserIter, ++E22UserIter, ++E12UserIter){
                tempMat11 = *E11UserIter*cos(*angleIter) + *E12UserIter*sin(*angleIter);
                tempMat12 = -*E11UserIter*sin(*angleIter) + *E12UserIter*cos(*angleIter);
                tempMat21 = *E12UserIter*cos(*angleIter) + *E22UserIter*sin(*angleIter);
                tempMat22 = -*E12UserIter*sin(*angleIter) + *E22UserIter*cos(*angleIter);
                *E12UserIter = cos(*angleIter)*tempMat12 + sin(*angleIter)*tempMat22;
            }
            coordYUser.release();
            return E12User;
            break;
        }
    }
    return cv::Mat::zeros(Exx.rows,Exx.cols,Exx.type());
}


cv::Mat displacements::computePrincipalStrains(
        drawOrigin &originAndAxesLayer, int getStrainFlag){
    double angle = originAndAxesLayer.getAngle();
    cv::Mat Eoutput = cv::Mat::zeros(Exx.rows,Exx.cols,CV_64F);

    cv::Mat strain11, strain12, strain22;
    if (originAndAxesLayer.spatialCoordinates){
        strain11 = exx;
        strain22 = eyy;
        strain12 = exy;
    } else {
        strain11 = Exx;
        strain22 = Eyy;
        strain12 = Exy;
    }
    cv::Mat_<double>::iterator ExxIter = strain11.begin<double>();
    cv::Mat_<double>::iterator EyyIter = strain22.begin<double>();
    cv::Mat_<double>::iterator ExyIter = strain12.begin<double>();
    cv::Mat_<double>::iterator EoutputIter = Eoutput.begin<double>();
    const double PI = 3.141592653;
    int multiplesOfPi = 0;
    switch (getStrainFlag){
    case getPS1:
        for(; ExxIter != strain11.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            double pt5ExxEyy = 0.5*(*ExxIter + *EyyIter);
            double pt5ExxMinusEyy = 0.5*(*ExxIter - *EyyIter);
            *EoutputIter = pt5ExxEyy + sqrt(pow(pt5ExxMinusEyy,2) + pow(.5*(*ExyIter),2));
        }
        return Eoutput;
        break;
    case getPS2:
        for(; ExxIter != strain11.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            double pt5ExxEyy = 0.5*(*ExxIter + *EyyIter);
            double pt5ExxMinusEyy = 0.5*(*ExxIter - *EyyIter);
            *EoutputIter = pt5ExxEyy - sqrt(pow(pt5ExxMinusEyy,2) + pow(.5*(*ExyIter),2));
        }
        return Eoutput;
        break;
    case getPD1:

        for(; ExxIter != strain11.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            *EoutputIter = .5*atan2(2.*(*ExyIter),(*ExxIter - *EyyIter))+angle;
            multiplesOfPi = ((int)abs(*EoutputIter/PI) > abs(multiplesOfPi)) ? (int)(*EoutputIter/PI) : multiplesOfPi;
        }

        Eoutput -= cv::Mat::ones(Eoutput.rows,Eoutput.cols,CV_64F)*(multiplesOfPi)*PI;
        Eoutput *= 180./PI;
        return Eoutput;
        break;

    case getPD2:
        for(; ExxIter != strain11.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            *EoutputIter = .5*atan2(2.*(*ExyIter),(*ExxIter - *EyyIter))+angle + PI/2.;
            multiplesOfPi = ((int)abs(*EoutputIter/PI) > abs(multiplesOfPi)) ? (int)(*EoutputIter/PI) : multiplesOfPi;
        }

        Eoutput -= cv::Mat::ones(Eoutput.rows,Eoutput.cols,CV_64F)*(multiplesOfPi)*PI;
        Eoutput *= 180./PI;
        return Eoutput;
        break;

    }
    return cv::Mat::zeros(Exx.rows,Exx.cols,Exx.type());
}

cv::Mat displacements::computeTrescaVMStrains(int getStrainFlag)
{
    cv::Mat Eoutput = cv::Mat::zeros(Exx.rows,Exx.cols,CV_64F);

    cv::Mat_<double>::iterator ExxIter = Exx.begin<double>();
    cv::Mat_<double>::iterator EyyIter = Eyy.begin<double>();
    cv::Mat_<double>::iterator ExyIter = Exy.begin<double>();
    cv::Mat_<double>::iterator EoutputIter = Eoutput.begin<double>();
    switch (getStrainFlag){
    case getVM:
        for(; ExxIter != Exx.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            *EoutputIter = sqrt(pow(*ExxIter,2) + pow(*EyyIter,2) + 3.*pow((*ExyIter),2) - *ExxIter*(*EyyIter));
        }
        return Eoutput;
        break;
    case getTresca:
        for(; ExxIter != Exx.end<double>(); ++ExxIter, ++EyyIter, ++ExyIter, ++EoutputIter){
            double pt5ExxEyy = 0.5*(*ExxIter + *EyyIter);
            double pt5ExxMinusEyy = 0.5*(*ExxIter - *EyyIter);
            double strain1 = pt5ExxEyy + sqrt(pow(pt5ExxMinusEyy,2) + pow(.5*(*ExyIter),2));
            double strain2 = pt5ExxEyy - sqrt(pow(pt5ExxMinusEyy,2) + pow(.5*(*ExyIter),2));
            *EoutputIter = strain1-strain2;
        }
        return Eoutput;
        break;
    }
    return cv::Mat::zeros(Exx.rows,Exx.cols,Exx.type());

}

void displacements::createResizedSolution(cv::Mat currentIm)
{
    // This way, it is possible to rotate axes, convert to polar etc...
    //    cv::resize(coordX,xResized,cv::Size(currentIm->cols,currentIm->rows),0,0,cv::INTER_NEAREST);
    //    cv::resize(coordY,yResized,cv::Size(currentIm->cols,currentIm->rows),0,0,cv::INTER_NEAREST);
    cv::resize(warp02,uResized,cv::Size(currentIm.cols,currentIm.rows),0,0,cv::INTER_LINEAR);
    cv::resize(warp12,vResized,cv::Size(currentIm.cols,currentIm.rows),0,0,cv::INTER_LINEAR);
    //    cv::resize(Exx,exxResized,cv::Size(currentIm->cols,currentIm->rows),0,0,cv::INTER_NEAREST);
    //    cv::resize(Eyy,eyyResized,cv::Size(currentIm->cols,currentIm->rows),0,0,cv::INTER_NEAREST);
    //    cv::resize(Exy,exyResized,cv::Size(currentIm->cols,currentIm->rows),0,0,cv::INTER_NEAREST);

    // Create the matrices for fast remapping
    cv::resize(correlCoef,corrCoefResized,cv::Size(currentIm.cols,currentIm.rows),0,0,cv::INTER_LINEAR);
    cv::resize(mask,maskResized,cv::Size(currentIm.cols,currentIm.rows),0,0,cv::INTER_LINEAR);
    qDebug() << "Solution resized";
}



void displacements::computeMaskAndLimits(int dataIdx, drawOrigin *originAndAxesLayer)
{
    results.release();
    float mapAmplification = 1.;
    switch (dataIdx)
    {
    case getX:
        results = computeUserCoords(*originAndAxesLayer, getX);
        break;
    case getY:
        results = computeUserCoords(*originAndAxesLayer, getY);
        break;
    case getU:
        results = computeUserDisplacements(*originAndAxesLayer, getU);
        break;
    case getV:
        results = computeUserDisplacements(*originAndAxesLayer, getV);
        break;
    case getRot:
        results = computeRotation(*originAndAxesLayer);
        break;
    case getExx:
        results = computeUserStrains(*originAndAxesLayer, getExx);
        break;
    case getEyy:
        results = computeUserStrains(*originAndAxesLayer, getEyy);
        break;
    case getExy:
        results = computeUserStrains(*originAndAxesLayer, getExy);
        break;
    case getPS1:
        results = computePrincipalStrains(*originAndAxesLayer,getPS1);
        break;
    case getPS2:
        results = computePrincipalStrains(*originAndAxesLayer,getPS2);
        break;
    case getPD1:
        results = computePrincipalStrains(*originAndAxesLayer,getPD1);
        break;
    case getPD2:
        results = computePrincipalStrains(*originAndAxesLayer,getPD2);
        break;
    case getVM:
        results = computeTrescaVMStrains(getVM);
        break;
    case getTresca:
        results = computeTrescaVMStrains(getTresca);
        break;
    case getCorr:
        results = corrCoefResized;
        break;
    case getAmplified:
        results = cv::imread(imageFiles->getRefImagePath().toLatin1().data(),0);
        results.convertTo(results,CV_64F);
        mapAmplification = originAndAxesLayer->motionAmplification;
    }

    mask.copyTo(maskDisplay);


    /// Assign a larger value only if the correlation
    // coefficient associated with it is smaller than the clipping value
    double minVal = 1.E10;
    double maxVal = -1.E10;
    cv::Mat_<double>::iterator resultsIterator = results.begin<double>();
    cv::Mat_<double>::iterator correlIterator = correlCoef.begin<double>();
    cv::Mat_<float>::iterator maskIterator = mask.begin<float>();
    cv::Mat_<float>::iterator maskDisplayIterator = maskDisplay.begin<float>();
    qDebug() << "Correl clipping val: " << correlClipVal;
    for ( ; resultsIterator != results.end<double>(); ++resultsIterator, ++correlIterator, ++maskIterator, ++maskDisplayIterator){
        if (*maskIterator > 0.){
            if(*correlIterator <= correlClipVal){
                minVal = *resultsIterator < minVal ? *resultsIterator : minVal;
                maxVal = *resultsIterator > maxVal ? *resultsIterator : maxVal;
            } else{
                *maskDisplayIterator = -1.;
            }
        }
    }


//    cv::resize(results,results,cv::Size(2*results.cols,2*results.rows));
    cv::resize(maskDisplay,maskDisplay,maskResized.size());
    cv::resize(results,results,maskResized.size());
    /// warp solution to fit current configuration

    if((dataIdx != getCorr) && originAndAxesLayer->deformedConfiguration){
//        int X = 0;
//        int Y = 0;
//        cv::Mat resultsDeformed = cv::Mat::zeros(results.size(),results.type());
//        cv::Mat tempResults = resultsDeformed.clone();

//        cv::Mat_<double>::iterator warp00Iter = warp00.begin<double>();
//        cv::Mat_<double>::iterator warp01Iter = warp01.begin<double>();
//        cv::Mat_<double>::iterator warp02Iter = warp02.begin<double>();
//        cv::Mat_<double>::iterator warp10Iter = warp10.begin<double>();
//        cv::Mat_<double>::iterator warp11Iter = warp11.begin<double>();
//        cv::Mat_<double>::iterator warp12Iter = warp12.begin<double>();
//        for(; warp00Iter != warp00.end<double>();
//            ++warp00Iter,++warp01Iter,++warp02Iter,
//            ++warp10Iter,++warp11Iter,++warp12Iter){
//            // Build coordinates of current solution point
//            cv::Rect subsetLocation(2*X,2*Y,2,2);
//            // Build warp
////            cv::Matx23d warpSubset(*warp00Iter,*warp01Iter,*warp02Iter+2.*(double)X,
////                                   *warp10Iter,*warp11Iter,*warp12Iter+2.*(double)Y);
//            cv::Matx23d warpSubset(1.,0.,2.*(-(*warp02Iter)/subsetSize+(double)X),
//                                   0.,1.,2.*(-(*warp12Iter)/subsetSize+(double)Y));

//            // Grab undeformed subset
//            cv::Mat subsetUndeformed = results(subsetLocation);
//            // Deform it and include it into result
//            cv::warpAffine(subsetUndeformed,tempResults,warpSubset,tempResults.size());
//            cv::Mat_<double>::iterator resultsDeformedIter = resultsDeformed.begin<double>();
//            cv::Mat_<double>::iterator addedWarpIter = tempResults.begin<double>();
//            for(; resultsDeformedIter != resultsDeformed.end<double>();
//                resultsDeformedIter++ , addedWarpIter++){
//                if(*addedWarpIter != 0.){
//                    *resultsDeformedIter = *addedWarpIter;
//                    if(*resultsDeformedIter != 0.){
//                        *resultsDeformedIter = .5*(*resultsDeformedIter + *addedWarpIter);
//                    } else {

//                    }
//                }
//            }
//            if(++X == warp00.cols){
//                Y++;
//                X=0;
//            }
//        }
//            resultsDeformed.copyTo(results);

       xRemap.create(maskResized.size(),CV_32FC1);
       yRemap.create(maskResized.size(),CV_32FC1);
       for(int j = 0; j < xRemap.rows; ++j){
           float* outputX = xRemap.ptr<float>(j);
           float* outputY = yRemap.ptr<float>(j);
           for(int i = 0; i < (xRemap.cols); ++i, ++outputX, ++outputY)
           {
               *outputX = i;
               *outputY = j;
           }
       }
       qDebug() << "Subset spacing" << subsetSpacing;

       //cv::Mat correlCoefOut, maskOut;
       //cv::remap(corrCoefResized,corrCoefResized, xRemap, yRemap,cv::INTER_LINEAR);
       maskDisplayRemap.create(2*maskResized.rows,2*maskResized.cols,maskResized.type());
       resultsRemap = maskDisplayRemap.clone();
       //cv::Rect roiTemp(maskResized.cols/4,maskResized.rows/4,maskResized.cols,maskResized.rows);
       maskDisplayRemap = maskDisplay.clone();
       resultsRemap = results.clone();
       remapResultsAndMask(mapAmplification, originAndAxesLayer);
    }
    if(dataIdx != getAmplified){
        /// Set the mim and max bounds
        //if (dataIdx != getCorr){
        autoBounds[dataIdx][0] = minVal;
        autoBounds[dataIdx][1] = maxVal;
        //}
        // If autoscale is on, then set manual bounds equal to auto scale bounds
        if(originAndAxesLayer->autoScaleOn[dataIdx]){
            qDebug() << "Auto bound values assigned";
            originAndAxesLayer->manualBounds[dataIdx][0] = minVal;
            originAndAxesLayer->manualBounds[dataIdx][1] = maxVal;
            originAndAxesLayer->manualMinMaxSlider[dataIdx][0] = minVal;
            originAndAxesLayer->manualMinMaxSlider[dataIdx][1] = maxVal;
        }
    }
    return;
}

void displacements::remapResultsAndMask(float mapAmplification, drawOrigin *originAndAxesLayer)
{
    cv::Mat disp32;
    uResized.convertTo(disp32,CV_32FC1);
    qDebug() <<mapAmplification;
    qDebug() << disp32.cols << disp32.rows << disp32.type();
    qDebug() << xRemap.cols << xRemap.rows << xRemap.type();
    // Make all the matrices twice the size of the image and center the image on it
    cv::Mat xRemapTemp;
    xRemapTemp.create(maskResized.rows,maskResized.cols,maskResized.type());
    cv::Mat yRemapTemp = xRemapTemp.clone();
    cv::Mat resultsTemp = xRemapTemp.clone();
    cv::Mat maskTemp = xRemapTemp.clone();
    // Define ROI as the whole image

    //cv::Rect roiTemp(xRemap.cols/4,yRemap.rows/4,xRemap.cols,xRemap.rows);
    xRemapTemp = xRemap - (mapAmplification/originAndAxesLayer->getImageResizeCoef())*disp32;
    qDebug() << "Break 1";
    vResized.convertTo(disp32,CV_32FC1);
    yRemapTemp = yRemap - (mapAmplification/originAndAxesLayer->getImageResizeCoef())*disp32;


//    cv::Mat_<float>::iterator xRemapIterator = xRemapTemp.begin<float>();
//    cv::Mat_<float>::iterator yRemapIterator = yRemapTemp.begin<float>();
//    for ( ; xRemapIterator != xRemapTemp.end<float>(); ++xRemapIterator, ++yRemapIterator){
//        *xRemapIterator = *xRemapIterator < 1.f ? 1.f : *xRemapIterator;
//        *xRemapIterator = *xRemapIterator > (float)xRemap.cols -2.f ? (float)xRemap.cols - 2.f : *xRemapIterator;
//        *yRemapIterator = *yRemapIterator < 0.f ? 0.f : *yRemapIterator;
//        *yRemapIterator = *yRemapIterator > (float)xRemap.rows -2.f ? (float)xRemap.rows - 2.f: *yRemapIterator;
//    }
    qDebug() << "Remap point" << results.cols << results.rows << xRemap.cols << xRemap.rows;
    //cv::convertMaps(xRemapTemp, yRemapTemp, xRemapTemp, yRemapTemp, CV_16SC2);
    cv::remap(maskDisplayRemap, maskTemp, xRemapTemp, yRemapTemp,cv::INTER_LINEAR);
    cv::remap(resultsRemap, resultsTemp, xRemapTemp, yRemapTemp,cv::INTER_LINEAR);
    xRemapTemp.release();
    yRemapTemp.release();

    results = resultsTemp;//(roiTemp);
    maskDisplay = maskTemp;//(roiTemp);
}

cv::Mat displacements::computeColorMap(int dataIdx, float imageResizeCoef, drawOrigin* originAndAxesLayer){
    cv::Mat resultsDisplay;
    cv::Mat colorMap;
    results.copyTo(resultsDisplay);

    if (dataIdx != getAmplified){
        // Max colormap val
        double maxColorMapVal = 255.;



        // Assign min and max values to the colormaps bounds sliders
        double upperBound = originAndAxesLayer->manualBounds[dataIdx][1];
        double lowerBound = originAndAxesLayer->manualBounds[dataIdx][0];

        //Compute scaling factors of the color map
        double slope = maxColorMapVal/( upperBound-lowerBound);

        //  Apply the slope and offset for the colormap
        for ( cv::Mat_<double>::iterator resultsIterator = resultsDisplay.begin<double>(); resultsIterator != resultsDisplay.end<double>(); ++resultsIterator)
        {
            *resultsIterator = slope*(*resultsIterator-lowerBound);
            if (*resultsIterator>maxColorMapVal) *resultsIterator = maxColorMapVal;
            else if (*resultsIterator<0.) *resultsIterator = 0.;
        }
        // Cast the results matrix to uchar
        resultsDisplay.convertTo(resultsDisplay,CV_8UC1);


        // Apply median filter
        //Scale the median filter value to the nearest odd integer
        double filterScaledDouble = (double)medianFilterValue/imageResizeCoef;
        int filterScaled = floor(filterScaledDouble/2.)*2+1;
        if(filterScaled >= 3){
            cv::medianBlur(resultsDisplay,resultsDisplay,filterScaled);
        }

        // Apply Gauss filter
        // Scale to the nearest integer
        filterScaledDouble = (double)gaussianFilterValue/imageResizeCoef;
        filterScaled = floor(filterScaledDouble/2.)*2+1;
        qDebug() << "Break1";
        qDebug() << gaussianFilterValue << imageResizeCoef << resultsDisplay.rows;
        if (filterScaled >=3){
            cv::GaussianBlur(resultsDisplay,resultsDisplay,
                             cv::Size(filterScaled,filterScaled),0,0);
        }
        cv::applyColorMap(255-resultsDisplay, colorMap, cv::COLORMAP_JET);
        resultsDisplay.release();

    }
    else {
        results.convertTo(colorMap,CV_8UC1);
        cvtColor(colorMap, colorMap, cv::COLOR_GRAY2RGB);
    }
    return colorMap;
}


void displacements::buildStrains()
{
    Exx = cv::Mat::zeros(warp00.size(),warp00.type());
    Eyy = cv::Mat::zeros(warp00.size(),warp00.type());
    Exy = cv::Mat::zeros(warp00.size(),warp00.type());
    exx = cv::Mat::zeros(warp00.size(),warp00.type());
    eyy = cv::Mat::zeros(warp00.size(),warp00.type());
    exy = cv::Mat::zeros(warp00.size(),warp00.type());

    // Iterate over the entire solution
    cv::Mat_<double>::iterator warp00Iter = warp00.begin<double>();
    cv::Mat_<double>::iterator warp01Iter = warp01.begin<double>();
    cv::Mat_<double>::iterator warp02Iter = warp02.begin<double>();
    cv::Mat_<double>::iterator warp10Iter = warp10.begin<double>();
    cv::Mat_<double>::iterator warp11Iter = warp11.begin<double>();
    cv::Mat_<double>::iterator warp12Iter = warp12.begin<double>();
    cv::Mat_<double>::iterator ExxIter = Exx.begin<double>();
    cv::Mat_<double>::iterator EyyIter = Eyy.begin<double>();
    cv::Mat_<double>::iterator ExyIter = Exy.begin<double>();
    cv::Mat_<double>::iterator exxIter = exx.begin<double>();
    cv::Mat_<double>::iterator eyyIter = eyy.begin<double>();
    cv::Mat_<double>::iterator exyIter = exy.begin<double>();

    for(; warp00Iter != warp00.end<double>();
        ++warp00Iter,++warp01Iter,++warp02Iter,++warp10Iter,++warp11Iter,++warp12Iter,
        ++ExxIter, ++EyyIter, ++ExyIter, ++exxIter, ++eyyIter, ++exyIter){
        // Build deformation gradient
        cv::Matx22d defGradient(*warp00Iter,*warp01Iter,*warp10Iter,*warp11Iter);
        cv::Matx22d rightCauchyGreen;
        cv::Matx22d leftCauchyGreen;
        cv::mulTransposed(defGradient,rightCauchyGreen,true);
        cv::mulTransposed(defGradient,leftCauchyGreen,false);

         //Build Green-Lagrange strain
        *ExxIter = 0.5*(rightCauchyGreen(0,0)-1.);
        *EyyIter = 0.5*(rightCauchyGreen(1,1)-1.);
        *ExyIter = .5*rightCauchyGreen(0,1);
        // Invert rightGreenCauchy and build Green-Almansi strain
        cv::Matx22d invLeftCauchyGreen = leftCauchyGreen.inv();
        *exxIter = 0.5*(1. - invLeftCauchyGreen(0,0));
        *eyyIter = 0.5*(1. - invLeftCauchyGreen(1,1));
        *exyIter = -0.5*invLeftCauchyGreen(0,1);


    }
}



cv::Mat displacements::drawScale(int dataIdx, drawOrigin *originAndAxesLayer, calibration *cam1Calibration)
{
    int nDivisions = 16;
    int width = 500;
    int height = 2000;

    const int barWidth = 100;
    const int textMargin = 10;
    const int verticalMargin = 10;
    const int topHorizontalMargin = 150;
    const int bottomHorizontalMargin = 20;

    double minVal = originAndAxesLayer->manualBounds[dataIdx][0];
    double maxVal = originAndAxesLayer->manualBounds[dataIdx][1];

    int barHeight = height-(topHorizontalMargin+bottomHorizontalMargin);

    double scaleFactor = 1.;
    QString unitLabel;
    if (((dataIdx == getU) || (dataIdx == getV) ||(dataIdx == getX)) ||((dataIdx == getY) && (originAndAxesLayer->polarCartFlag == drawOrigin::cartesianCoord))){
        switch (originAndAxesLayer->unitDisplayFlag) {
        case drawOrigin::pixelUnit:
            unitLabel = "pixels";
            scaleFactor = 1.;
            break;
        case drawOrigin::mmUnit:
            unitLabel = "mm";
            scaleFactor = cam1Calibration->mmPerPixel;
            break;
        case drawOrigin::cmUnit:
            unitLabel = "cm";
            scaleFactor = .01*cam1Calibration->mmPerPixel;
            break;
        case drawOrigin::mUnit:
            unitLabel = "m";
            scaleFactor = .001*cam1Calibration->mmPerPixel;
            break;
        case drawOrigin::inUnit:
            unitLabel = "in";
            scaleFactor = 0.0393701*cam1Calibration->mmPerPixel;
            break;
        case drawOrigin::ftUnit:
            unitLabel = "ft";
            scaleFactor = 0.00328084*cam1Calibration->mmPerPixel;
            break;
        default:
            unitLabel = "pixels";
            scaleFactor = 1.;
            break;
        }
    }

    cv::Point2i topRect(verticalMargin,topHorizontalMargin);
    cv::Point2i bottomRect(verticalMargin+barWidth,height-bottomHorizontalMargin);
    cv::Mat scaleMat(height,width,CV_8UC3);
    scaleMat.setTo(cv::Scalar(255,255,255));
    cv::rectangle(scaleMat,topRect,bottomRect,cv::Scalar(0,0,0),2);

    cv::Mat colorBar(barHeight,barWidth,CV_8UC1);
    for(int j = 0; j < colorBar.rows; ++j)
    {
        uchar* current  = colorBar.ptr<uchar>(j    );
        for(int i = 0; i < (colorBar.cols); ++i)
        {
            current[i] = (double)j/(double)colorBar.rows*255;
        }
    }
    cv::applyColorMap(colorBar, colorBar, cv::COLORMAP_JET);
    cv::Mat colorBarRoi(scaleMat, cv::Rect(verticalMargin,topHorizontalMargin,barWidth,barHeight));
    colorBar.copyTo(colorBarRoi);

    putText(scaleMat, std::to_string(minVal*scaleFactor), cv::Point2i(verticalMargin + barWidth + textMargin,barHeight+ topHorizontalMargin),
            cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0,0,0), 3, cv::LINE_AA);
    putText(scaleMat, std::to_string(maxVal*scaleFactor), cv::Point2i(verticalMargin + barWidth + textMargin,topHorizontalMargin),
            cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0,0,0), 3, cv::LINE_AA);
    for (int i=1; i<nDivisions;++i){
        // Split lines
        int lineHeight = topHorizontalMargin+ (int)(((double)(nDivisions - i)/(double)(nDivisions))*barHeight);
        cv::line(scaleMat,cv::Point2i(verticalMargin,lineHeight),
                 cv::Point2i(verticalMargin+barWidth,lineHeight),cv::Scalar(0,0,0),2);
        // Text
        putText(scaleMat, std::to_string(((double)(i)/(double)(nDivisions)*(maxVal-minVal)+minVal)*scaleFactor), cv::Point2i(verticalMargin + barWidth + textMargin,lineHeight),
                cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0,0,0), 3, cv::LINE_AA);
    }

    //Title
    QString Ulabel = "U [" + unitLabel + "]";
    QString Vlabel = "V [" + unitLabel + "]";
    QString Xlabel = "X [" + unitLabel + "]";
    QString Ylabel = "Y [" + unitLabel + "]";
    QString Urlabel = "Ur [" + unitLabel + "]";
    QString Utlabel = "Utheta [" + unitLabel + "]";
    QString Rlabel = "R [" + unitLabel + "]";
    QString Thetalabel = "Theta [deg]";
    std::vector<std::string> labelCart;
    labelCart.push_back(Ulabel.toStdString());
    labelCart.push_back(Vlabel.toStdString());
    labelCart.push_back("Rotation [deg]");
    labelCart.push_back("Exx");
    labelCart.push_back("Eyy");
    labelCart.push_back("Exy");
    labelCart.push_back("Pr. Strain 1");
    labelCart.push_back("Pr. Strain 2");
    labelCart.push_back("Pr. Direction 1 [deg]");
    labelCart.push_back("Pr. Direction 2 [deg]");
    labelCart.push_back("Von-Mises Strain");
    labelCart.push_back("Tresca Strain");
    labelCart.push_back("Correl. Coef.");
    labelCart.push_back(Xlabel.toStdString());
    labelCart.push_back(Ylabel.toStdString());

    std::vector<std::string> labelPolar;
    labelPolar.push_back(Urlabel.toStdString());
    labelPolar.push_back(Utlabel.toStdString());
    labelPolar.push_back("Rotation [deg]");
    labelPolar.push_back("Err");
    labelPolar.push_back("Ett");
    labelPolar.push_back("Ert");
    labelPolar.push_back("Pr. Strain 1");
    labelPolar.push_back("Pr. Strain 2");
    labelPolar.push_back("Pr. Direction 1 [deg]");
    labelPolar.push_back("Pr. Direction 2 [deg]");
    labelPolar.push_back("Von-Mises Strain");
    labelPolar.push_back("Tresca Strain");
    labelPolar.push_back("Correl. Coef.");
    labelPolar.push_back(Rlabel.toStdString());
    labelPolar.push_back(Thetalabel.toStdString());


    if (originAndAxesLayer->polarCartFlag == originAndAxesLayer->cartesianCoord){
        putText(scaleMat,labelCart[dataIdx],cv::Point2i(textMargin,5*textMargin),cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0,0,0), 3, cv::LINE_AA);
    } else {
        putText(scaleMat,labelPolar[dataIdx],cv::Point2i(textMargin,5*textMargin),cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0,0,0), 3, cv::LINE_AA);
    }
    return scaleMat;

}

bool displacements::isEmpty()
{
    return warp00.empty();
}


void displacements::write(cv::FileStorage& fs) const                        //Write serialization for this class
{
    fs << "{"
       << "subsetSize" << subsetSize
       <<"subsetSpacing" << subsetSpacing
      <<  "minMaxAutoVals" << "[";
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            fs << autoBounds[j][i];
        }
    }
    fs <<"]"
      << "correlCoef" << correlCoef
      << "coordX" << coordX
      << "coordY" << coordY
      << "mask" << mask
      << "warp00" << warp00 << "warp01" << warp01 << "warp02" << warp02
      << "warp10" << warp10 << "warp11" << warp11 << "warp12" << warp12 << "}";

}
void displacements::read(const cv::FileNode& node)
{
    qDebug() << "reading";
    node["subsetSize"] >> subsetSize;
    node["subsetSpacing"] >> subsetSpacing;
    cv::FileNodeIterator minMaxAutoIt = node["minMaxAutoVals"].begin();
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            autoBounds[j][i] = (double)*minMaxAutoIt;
            ++minMaxAutoIt;
        }
    }

    subsetPts.clear();
    node["correlCoef"] >> correlCoef;
    node["coordX"] >> coordX;
    node["coordY"] >> coordY;
    node["mask"] >> mask;
    node["warp00"] >> warp00;
    node["warp01"] >> warp01;
    node["warp02"] >> warp02;
    node["warp10"] >> warp10;
    node["warp11"] >> warp11;
    node["warp12"] >> warp12;

    buildStrains();
    qDebug() << "Done reading";
}



bool displacements::openSolutionFile(int val, fileList *correlationFiles ,displacements *dispSol){


    qDebug() << "openSolutionFile";
    QFileInfo imgFilePath(correlationFiles->getFilePath(val));
    std::string solFilePathStd = imgFilePath.absolutePath().toStdString() + "/"
            + imgFilePath.baseName().toStdString() + ".optsln";

    qDebug() << "Sol exists: "
             <<(QFile::exists(QString::fromStdString(solFilePathStd)));
    if (QFile::exists(QString::fromStdString(solFilePathStd))){
        correlationFiles->setIsSolved(val,true);
        qDebug() <<"Loading: " << QString::fromStdString(solFilePathStd);
        cv::FileStorage fs(solFilePathStd, cv::FileStorage::READ);
        qDebug() << "Done with filePath";
        fs["Solution"] >> *dispSol;
        dispSol->imageFiles = correlationFiles;
        fs.release();        
        qDebug() << "Loading successful";
        return true;
    }
    return false;
}
