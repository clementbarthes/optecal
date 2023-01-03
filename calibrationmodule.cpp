#include "calibrationmodule.h"

calibrationModule::calibrationModule(calibration* cam1Calibration, autoResize* cam1Display,
                                     QLabelWMouse* imgDisplay, QLineEdit *cropFactorEdit, QLineEdit *aCal, QLineEdit *bCal, QLineEdit *cCal)
{
    this->cam1Calibration = cam1Calibration;
    lensCorrectionOn = false;

    this->cropFactorEdit = cropFactorEdit;
    this->aCal = aCal;
    this->bCal = bCal;
    this->cCal = cCal;

    this->cam1Display = cam1Display;
    this->imgDisplay = imgDisplay;


}

void calibrationModule::updateDistortionCorrection()
{
    cv::Mat currentImgResized = cam1Display->uncorrectedDisplayedImage.clone();
    if (!currentImgResized.data){
        return;
    }
    if(lensCorrectionOn){
        cv::Point2i frameCenter(currentImgResized.cols/2,currentImgResized.rows/2);
        float normFactor;
        float a = aCal->text().toFloat();
        float b = bCal->text().toFloat();
        float c = cCal->text().toFloat();
        float cropFactorValue = cropFactorEdit->text().toFloat();
        float lensCalCropFactor = cam1Calibration->lensMakerList[cam1Calibration->getLensMakerIdx()].
                lensList[cam1Calibration->getLensIdx()].lensLab[cam1Calibration->getBestLensLab()].cropFactor;
        if (currentImgResized.cols >= currentImgResized.rows){
            normFactor = 2.*lensCalCropFactor/((float)currentImgResized.rows*cropFactorValue);
        }
        else {
            normFactor = 2.*lensCalCropFactor/((float)currentImgResized.cols*cropFactorValue);
        }
        cv::Mat remapX(currentImgResized.size(),CV_32F);
        cv::Mat remapY(currentImgResized.size(),CV_32F);
        cv::Mat_<float>::iterator remapXIter = remapX.begin<float>();
        cv::Mat_<float>::iterator remapYIter = remapY.begin<float>();
        int iCol = 0;
        int iRow = 0;
        float rSrc, rDest;
        for(; remapXIter != remapX.end<float>(); ++remapXIter, ++remapYIter){
            float angle;
            rSrc = sqrt(pow((float)(iCol-frameCenter.x),2) + pow((float)(iRow-frameCenter.y),2));
            angle = atan2((float)(iRow-frameCenter.y),(float)(iCol-frameCenter.x));
            // Normalize rSrc:
            rSrc *= normFactor;

            // Compute normalied rDest
            rDest = (a*pow(rSrc,3)+b*pow(rSrc,2)+c*rSrc + 1.-a-b-c)*rSrc;
            // De-normalize rDest
            rDest /= normFactor;
            // Compute the remap matrices
            *remapXIter = cos(angle)*rDest + (float)frameCenter.x;
            *remapYIter = sin(angle)*rDest + (float)frameCenter.y;
            ++iCol;
            if(iCol == remapX.cols){
                iCol = 0;
                ++iRow;
            }
        }
        qDebug() << iCol << "," << iRow << "," << currentImgResized.cols << ","<< currentImgResized.rows;
        cv::remap(currentImgResized,currentImgResized,remapX,remapY,cv::INTER_LANCZOS4);
    }
    *cam1Display->getCurrentResizedImg() = currentImgResized;
    cam1Display->updateResized();
}

void calibrationModule::cameraMakerChanged(int val)
{
    cam1Calibration->parseCameraList(val);
}

void calibrationModule::cameraModelChanged(int val)
{
    if (val>= 0){
        emit cropFactor(QString::number(
                            cam1Calibration->cameraMakerList[cam1Calibration->getCameraMakerIdx()].cameraList[val].cropFactor));
        if (!cam1Calibration->lensMakerList.empty() && (cam1Calibration->getLensIdx()>=0) && (cam1Calibration->getFocalLengthIdx() >=0)){
            focalLengthChanged(0);
        }
    }
    //updateDistortionCorrection();
}

void calibrationModule::lensMakerChanged(int val)
{
    cam1Calibration->parseLensList(val);
}

void calibrationModule::lensModelChanged(int val)
{
    cam1Calibration->parseFocalLengthList(val);
}

void calibrationModule::focalLengthChanged(int val)
{
    int bestCal = cam1Calibration->getBestLensLab();
    // Get lens properties
    calibration::lensProperties currentLensProp =
            cam1Calibration->lensMakerList[cam1Calibration->getLensMakerIdx()].
            lensList[cam1Calibration->getLensIdx()].lensLab[bestCal].lensProps[val];
    emit calA(QString::number(currentLensProp.a));
    emit calB(QString::number(currentLensProp.b));
    emit calC(QString::number(currentLensProp.c));
    updateDistortionCorrection();
}

void calibrationModule::cropFactorEdited()
{
    cam1Calibration->setCameraCustom(cropFactorEdit->text().toDouble());
    //updateDistortionCorrection();
}

void calibrationModule::aCalEdited()
{
    cam1Calibration->setLensCustom(aCal->text().toDouble(),
                                   bCal->text().toDouble(),cCal->text().toDouble());
    updateDistortionCorrection();
}

void calibrationModule::bCalEdited()
{
    cam1Calibration->setLensCustom(aCal->text().toDouble(),
                                   bCal->text().toDouble(),cCal->text().toDouble());
    updateDistortionCorrection();
}

void calibrationModule::cCalEdited()
{
    cam1Calibration->setLensCustom(aCal->text().toDouble(),
                                   bCal->text().toDouble(),cCal->text().toDouble());
    updateDistortionCorrection();
}

void calibrationModule::enableLensCorrection(bool val)
{
    cropFactorEdit->setEnabled(val);
    aCal->setEnabled(val);
    bCal->setEnabled(val);
    cCal->setEnabled(val);
    cam1Calibration->enableComboBoxes(val);
    lensCorrectionOn = val;
    updateDistortionCorrection();

}


void calibrationModule::Mouse_current_pos()
{


}

void calibrationModule::Mouse_Entered()
{
}

void calibrationModule::Mouse_Pressed()
{


}

void calibrationModule::Key_Pressed()
{

}




