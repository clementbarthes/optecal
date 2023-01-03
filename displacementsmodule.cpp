#include "displacementsmodule.h"


displacementsModule::displacementsModule(QLabelWMouse *currentImgDisplay, autoResize *cam1Display,
                                         autoResize* scaleDisplay, fileList *cam1Files,
                                         displacements *dispFbk, drawShape* roiShapes,
                                         drawOrigin* originAndAxesLayer, calibration *cam1Calibration,
                                         QLineEdit* lowerBoundText, QLineEdit* upperBoundText, QLineEdit* clippingValText,
                                         QLineEdit *amplificationText, QLineEdit *backgroundText)
{
    this->currentImgDisplay = currentImgDisplay;
    this->dispFbk = dispFbk;
    this->cam1Display = cam1Display;
    this->cam1Files = cam1Files;
    this->scaleDisplay = scaleDisplay;
    this->roiShapes = roiShapes;
    this->originAndAxesLayer = originAndAxesLayer;

    this->lowerBoundText = lowerBoundText;
    this->upperBoundText = upperBoundText;
    this->amplificationText = amplificationText;
    this->backgroundText = backgroundText;
    this->clippingValText = clippingValText;
    this->cam1Calibration = cam1Calibration;

    minSliderBar = 0;
    maxSliderBar = 500;
    dataIdx = 0;
    scaleVal = 1;
    originAndAxesLayer->colormapCoef = 0.8f;
    solutionLoaded = false;
}



void displacementsModule::loadFormatAndDisplay(){
    if (!solutionLoaded) return;
    // Reset the current image display
    QElapsedTimer timer;
    timer.start();
    //cam1Display->setCurrentImg(cam1Files->getCurrentImgPath());
    cam1Display->update();
    qDebug() << "Setting current image on display: " << timer.elapsed() << "milliseconds";
    // Get current image
    currentIm = cam1Display->getCurrentResizedImg();
    (*currentIm).copyTo(prevIm);
    imageResizeCoef = cam1Display->getResizeCoef();
    timer.start();

//    if (dataIdx == displacements::getAmplified){
//        return;
//    }

    dispFbk->createResizedSolution(*currentIm);
    qDebug() << "Create resized solution: " << timer.elapsed() << "milliseconds";
    timer.start();
    dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
    qDebug() << "Compute mask and limits: " << timer.elapsed() << "milliseconds";
    if(originAndAxesLayer->autoScaleOn[dataIdx]){
        emit setScaleComboBox(1);
        emit editUpperBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][1])));
        emit editLowerBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][0])));
        emit setLowerBoundSlider(0);
        emit setUpperBoundSlider(sliderNumberVal);
    } else {
        emit setScaleComboBox(0);
        emit editUpperBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][1])));
        emit editLowerBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        // Set the LOWER BOUND slider bar
        int sliderVal = std::max(0,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                         originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][0] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        emit setLowerBoundSlider(sliderVal);
        // Set  the UPPER BOUND slider bar
        sliderVal = std::min(sliderNumberVal,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                                   originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][1] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        emit setUpperBoundSlider(sliderVal);
    }

    timer.start();
    displacementDisplay();
    qDebug() << "Display displacement: " << timer.elapsed() << "milliseconds";
    qDebug() <<"Loaded and resized";
}

int displacementsModule::getDataIdx()
{
    return dataIdx;
}

double displacementsModule::convertToUnits(double val)
{
    double unitScaleFactor;
    switch (originAndAxesLayer->unitDisplayFlag) {
    case drawOrigin::pixelUnit:
        unitScaleFactor = 1.;
        break;
    case drawOrigin::mmUnit:
        unitScaleFactor = cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::cmUnit:
        unitScaleFactor = .01*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::mUnit:
        unitScaleFactor = .001*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::inUnit:
        unitScaleFactor = 0.0393701*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::ftUnit:
        unitScaleFactor = 0.00328084*cam1Calibration->mmPerPixel;
        break;
    default:
        unitScaleFactor = 1.;
        break;
    }

    if (((dataIdx == displacements::getU) || (dataIdx == displacements::getV) ||(dataIdx == displacements::getX)) ||
            ((dataIdx == displacements::getY) && (originAndAxesLayer->polarCartFlag == drawOrigin::cartesianCoord))){
        return unitScaleFactor*val;
    } else{
        return val;
    }
}

double displacementsModule::convertToPixels(double val)
{
    double pixelScaleFactor;
    switch (originAndAxesLayer->unitDisplayFlag) {
    case drawOrigin::pixelUnit:
        pixelScaleFactor = 1.;
        break;
    case drawOrigin::mmUnit:
        pixelScaleFactor = 1./cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::cmUnit:
        pixelScaleFactor = 1./(.01*cam1Calibration->mmPerPixel);
        break;
    case drawOrigin::mUnit:
        pixelScaleFactor = 1./(.001*cam1Calibration->mmPerPixel);
        break;
    case drawOrigin::inUnit:
        pixelScaleFactor = 1./(0.0393701*cam1Calibration->mmPerPixel);
        break;
    case drawOrigin::ftUnit:
        pixelScaleFactor = 1./(0.00328084*cam1Calibration->mmPerPixel);
        break;
    default:
        pixelScaleFactor = 1.;
        break;
    }

    if (((dataIdx == displacements::getU) || (dataIdx == displacements::getV) ||(dataIdx == displacements::getX)) ||
            ((dataIdx == displacements::getY) && (originAndAxesLayer->polarCartFlag == drawOrigin::cartesianCoord))){
        return pixelScaleFactor*val;
    } else{
        return val;
    }
}

    void displacementsModule::displacementDisplay(){

        if (!solutionLoaded) return;
        cv::Mat colorMap = dispFbk->computeColorMap(dataIdx, imageResizeCoef,originAndAxesLayer);

        if (dataIdx == displacements::getAmplified){
            scaleDisplay->clear();
            scaleDisplay->clearLabel();

            cv::Mat mask8;
            dispFbk->maskDisplay.convertTo(mask8,CV_8UC1);
            cv::Mat colorMapBG = colorMap.clone();
            prevIm.convertTo(*currentIm,prevIm.type(),originAndAxesLayer->backgroundAmplifiedMotion);
            //colorMapBG.copyTo(*currentIm)
            colorMap.copyTo(*currentIm, mask8);
        } else {
            cv::Mat scaleMat = dispFbk->drawScale(dataIdx, originAndAxesLayer, cam1Calibration);
            scaleDisplay->setCurrentImgMat(scaleMat);
            scaleDisplay->update();

            prevIm.copyTo(*currentIm);
            cv::Mat mask8;
            dispFbk->maskDisplay.convertTo(mask8,CV_8UC1);
            float backgroundCoef;
                backgroundCoef =
                    (1.3-originAndAxesLayer->colormapCoef) <= 1. ?
                        (1.3-originAndAxesLayer->colormapCoef) : 1.;
                cv::add(backgroundCoef*prevIm,originAndAxesLayer->colormapCoef*colorMap,*currentIm ,mask8);
        }

        if (originAndAxesLayer->axesOn){
            originAndAxesLayer->setImage(currentIm,imageResizeCoef);
            originAndAxesLayer->updateDrawing();
        }

        cam1Display->updateResized();

    }


    void displacementsModule::loadSolFromFile(int val){
        if (val>=0){
            qDebug() << "Current image file index:" << cam1Files->getCurrentImgIdx();
            if ((dispFbk->currentImIndex != val) || !solutionLoaded){
                dispFbk->currentImIndex = val;
                qDebug()<< "LoadSolFromFile: " << val;
                if(!displacements::openSolutionFile(val, cam1Files,dispFbk)){
                    solutionLoaded = false;
                    return;
                }
            }
            solutionLoaded = true;
            loadFormatAndDisplay();

        }
    }


    void displacementsModule::lowerBoundSliderChanged(int val)
    {
        originAndAxesLayer->manualBounds[dataIdx][0] = ((originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                                        originAndAxesLayer->manualMinMaxSlider[dataIdx][0])/(double)(sliderNumberVal)*(double)val +
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0]);
        displacementDisplay();
    }

    void displacementsModule::upperBoundSliderChanged(int val)
    {
        originAndAxesLayer->manualBounds[dataIdx][1] = (originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])/(double)(sliderNumberVal)*(double)val +
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0];

        displacementDisplay();
    }

    void displacementsModule::lowerBoundSliderMovedByUser(int val)
    {


        // If upper bound slider is lower than lower bound slider, then change its value
        if (originAndAxesLayer->manualBounds[dataIdx][1] < originAndAxesLayer->manualBounds[dataIdx][0]){
            emit setUpperBoundSlider(val);
        }
        // If bound value changed, set the combo box to manual
        originAndAxesLayer->autoScaleOn[dataIdx] = false;
        emit setScaleComboBox(0);

    }

    void displacementsModule::upperBoundSliderMovedByUser(int val)
    {

        // If upper bound slider is lower than lower bound slider, then change its value
        if (originAndAxesLayer->manualBounds[dataIdx][1] < originAndAxesLayer->manualBounds[dataIdx][0]){
            emit setLowerBoundSlider(val);
        }
        // If bound value changed, set the combo box to manual
        originAndAxesLayer->autoScaleOn[dataIdx] = false;
        emit setScaleComboBox(0);


    }

    void displacementsModule::amplificationMovedByUser(int val)
    {
        amplificationText->setText(QString::number(val));
        originAndAxesLayer->motionAmplification = (float)val;
        dispFbk->remapResultsAndMask(originAndAxesLayer->motionAmplification,
                                     originAndAxesLayer);
        displacementDisplay();
    }

    void displacementsModule::backgroundMovedByUser(int val)
    {
        backgroundText->setText(QString::number(val));
        originAndAxesLayer->backgroundAmplifiedMotion = float(val)*0.01f;
        dispFbk->remapResultsAndMask(originAndAxesLayer->motionAmplification, originAndAxesLayer);
        displacementDisplay();
    }

    void displacementsModule::lowerBoundEdited()
    {
        double lowerBoundValue = convertToPixels(lowerBoundText->text().toDouble());
        if (lowerBoundValue < upperBoundText->text().toDouble()){
            originAndAxesLayer->manualMinMaxSlider[dataIdx][0] = lowerBoundValue;
        } else { // If the lower bound is greater than the upper bound, display an error message and set it back to its original value
            lowerBoundText->setText(QString("%1").arg(originAndAxesLayer->manualMinMaxSlider[dataIdx][0]));
            QMessageBox lowerBoundTooHigh;
            lowerBoundTooHigh.setText(
                        "The lower bound must be less than the upper bound");
            lowerBoundTooHigh.exec();
            return;
        }

        // Set the LOWER BOUND slider bar
        int sliderVal = std::max(0,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                         originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][0] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        lowerBoundSliderChanged(sliderVal);

        // Set  the UPPER BOUND slider bar
        sliderVal = std::min(sliderNumberVal,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                                   originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][1] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        upperBoundSliderChanged(sliderVal);
        qDebug() << "Lower Bound Edited: " << originAndAxesLayer->manualMinMaxSlider[dataIdx][1] ;
        // If bound value changed, set the combo box to manual
        originAndAxesLayer->autoScaleOn[dataIdx] = false;
        emit setScaleComboBox(0);
    }

    void displacementsModule::upperBoundEdited()
    {
        double upperBoundValue = convertToPixels(upperBoundText->text().toDouble());
        if (upperBoundValue > lowerBoundText->text().toDouble()){
            originAndAxesLayer->manualMinMaxSlider[dataIdx][1] = upperBoundValue;
        } else { // If the upper bound is less than the lower bound, display an error message and set it back to its original value
            upperBoundText->setText(QString("%1").arg(originAndAxesLayer->manualMinMaxSlider[dataIdx][1]));
            QMessageBox upperBoundTooLow;
            upperBoundTooLow.setText(
                        "The upper bound must be greater than the lower bound");
            upperBoundTooLow.exec();
            return;
        }
        // Set the LOWER BOUND slider bar
        int sliderVal = std::max(0,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                         originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][0] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        lowerBoundSliderChanged(sliderVal);
        // Set the UPPER BOUND slider bar
        sliderVal = std::min(sliderNumberVal,(int)((double)(sliderNumberVal)/(originAndAxesLayer->manualMinMaxSlider[dataIdx][1] -
                                                   originAndAxesLayer->manualMinMaxSlider[dataIdx][0])*(originAndAxesLayer->manualBounds[dataIdx][1] -
                originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        upperBoundSliderChanged(sliderVal);

        qDebug() << "Upper Bound Edited: " << originAndAxesLayer->manualMinMaxSlider[dataIdx][1] ;
        // If bound value changed, set the combo box to manual
        originAndAxesLayer->autoScaleOn[dataIdx] = false;
        emit setScaleComboBox(0);
    }

    void displacementsModule::amplificationEdited()
    {
        emit setAmplificationSlider(amplificationText->text().toInt());
//        originAndAxesLayer->motionAmplification = amplificationText->text().toFloat();
//        dispFbk->remapResultsAndMask(originAndAxesLayer->motionAmplification, originAndAxesLayer);
//        displacementDisplay();
    }

    void displacementsModule::backgroundEdited()
    {
        emit setBackgroundSlider(backgroundText->text().toInt());
        originAndAxesLayer->backgroundAmplifiedMotion = backgroundText->text().toFloat()*0.01f;
        dispFbk->remapResultsAndMask(originAndAxesLayer->motionAmplification, originAndAxesLayer);
        displacementDisplay();
    }

    void displacementsModule::clippingValEdited()
    {
        double clippingBoundValue = clippingValText->text().toDouble()/100.;

        if (clippingBoundValue > 0){
            originAndAxesLayer->maxClippingSliderVal = clippingBoundValue;

            // Set  the slider bar
            int sliderVal = std::min(sliderNumberVal,(int)((double)(sliderNumberVal)/originAndAxesLayer->maxClippingSliderVal*dispFbk->correlClipVal));
            emit setCorrCoefSlider(sliderVal);


        } else { // If the upper bound is less than 0, display an error message and set it back to its original value
            clippingValText->setText(QString("%1").arg(originAndAxesLayer->maxClippingSliderVal*100.));
            QMessageBox upperBoundTooLow;
            upperBoundTooLow.setText(
                        "The maximum clipping value must be positive");
            upperBoundTooLow.exec();
            return;
        }
    }


    void displacementsModule:: scaleAuto(int val)
    {

        if (!solutionLoaded) return;
        if (val == 0){
            originAndAxesLayer->autoScaleOn[dataIdx] = false;
            qDebug() << "Auto-scale : " << originAndAxesLayer->autoScaleOn[dataIdx] ;
        }
        else {
            originAndAxesLayer->autoScaleOn[dataIdx] = true;
            emit editUpperBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][1])));
            emit editLowerBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][0])));

            emit setLowerBoundSlider(0);
            emit setUpperBoundSlider(sliderNumberVal);
            qDebug() << "Auto-scale : " << originAndAxesLayer->autoScaleOn[dataIdx] ;

        }

        dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
        displacementDisplay();
    }

    void displacementsModule::onShowAxes(bool val)
    {
        originAndAxesLayer->axesOn = val;
        displacementDisplay();
    }

    void displacementsModule::dispComboBoxChanged(int val){
        dataIdx = val;
        if (dataIdx == displacements::getAmplified){
            emit amplifiedMotionBox(true);
        }else {
            emit amplifiedMotionBox(false);
            if(originAndAxesLayer->autoScaleOn[dataIdx]){
                emit setScaleComboBox(1);
            }else {
                emit setScaleComboBox(0);

            }
        }
        loadFormatAndDisplay();
    }

    void displacementsModule::medianFilterChanged(int val){
        // Scale the filter to the resized window

        dispFbk->medianFilterValue = val;
        displacementDisplay();
    }

    void displacementsModule::gaussianFilterChanged(int val){
        // Scale the filter to the resized window

        dispFbk->gaussianFilterValue = val;
        displacementDisplay();
    }

    void displacementsModule::clippingChanged(int val)
    {
        dispFbk->correlClipVal = ((double)val*(originAndAxesLayer->maxClippingSliderVal)/((double)sliderNumberVal-1.));

        qDebug() << "Auto-scale :" << originAndAxesLayer->autoScaleOn[dataIdx];
        if(solutionLoaded) dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
        if (originAndAxesLayer->autoScaleOn[dataIdx]){
            emit editUpperBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][1])));
            emit editLowerBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][0])));
            emit setLowerBoundSlider(0);
            emit setUpperBoundSlider(sliderNumberVal);
        }
        displacementDisplay();

    }


    void displacementsModule::Mouse_current_pos()
    {
        cv::Point2i currentPoint((currentImgDisplay->x)*imageResizeCoef,
                                 (currentImgDisplay->y)*imageResizeCoef);
        int isNear;
        if(originAndAxesLayer->drawingInProgress){
            originAndAxesLayer->updatePoint(&currentPoint);
            dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
            displacementDisplay();
            cam1Display->updateResized();
        } else if((originAndAxesLayer->updatePointInProgress ||
                   (isNear = originAndAxesLayer->isMouseNearPoint(&currentPoint))>0)
                  && currentImgDisplay->leftClickHeld){
            originAndAxesLayer->updatePointInProgress = true;
            currentImgDisplay->setCursor(Qt::ClosedHandCursor);
            setCursorStyle(isNear);
            originAndAxesLayer->updatePoint(&currentPoint);
            dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
            displacementDisplay();
            cam1Display->updateResized();
        }
        else{
            if((isNear = originAndAxesLayer->isMouseNearPoint(&currentPoint))>0){
                currentImgDisplay->setCursor(Qt::OpenHandCursor);
            } else {
                currentImgDisplay->setCursor(Qt::ArrowCursor);
            }
            originAndAxesLayer->updatePointInProgress = false;
            originAndAxesLayer->setAngle();

        }
    }

    void displacementsModule::Mouse_Entered(){
        imageResizeCoef = cam1Display->getResizeCoef();
    }

    void displacementsModule::Mouse_Pressed()
    {
        cv::Point2i currentPoint((currentImgDisplay->x)*imageResizeCoef,
                                 (currentImgDisplay->y)*imageResizeCoef);
        if(originAndAxesLayer->drawingInProgress){
            originAndAxesLayer->setPoint(currentPoint);
        } else if (originAndAxesLayer->isMouseNearPoint(&currentPoint)>0){
            originAndAxesLayer->pointGrabbed = currentPoint;
            qDebug() << "Grabbed Point";
            currentImgDisplay->setCursor(Qt::ClosedHandCursor);
        }
    }

    void displacementsModule::setCursorStyle(int isNear){

        switch (isNear){
        case drawOrigin::mouseNearEdgeVectorVert:

            break;
        case drawOrigin::mouseNearCircleCenter:
            currentImgDisplay->setCursor(Qt::SizeAllCursor);
            break;
        case drawOrigin::mouseNearCircleEdgeLeft:
            currentImgDisplay->setCursor(Qt::SizeFDiagCursor);
            break;
        case drawOrigin::mouseNearCircleEdgeRight:
            currentImgDisplay->setCursor(Qt::SizeBDiagCursor);
            break;
        }
    }

    void displacementsModule::onFlipXY(bool val)
    {
        if(solutionLoaded){
            if (originAndAxesLayer->flipXY != val) originAndAxesLayer->setFlipXY(val);
            dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
            displacementDisplay();
        }

    }

    void displacementsModule::unitsChanged(int val)
    {

        if((cam1Calibration->mmPerPixel == 0.) && (val !=0)){
            QMessageBox noScaleErrorMessage;
            noScaleErrorMessage.setText(
                        "Scale undefined. To define scale, click on Calibrate and use the scale definition tool ");
            noScaleErrorMessage.exec();
            emit setUnitsComboBox(0);
            return;
        }
        originAndAxesLayer->unitDisplayFlag = val;
        cv::Mat scaleMat = dispFbk->drawScale(dataIdx, originAndAxesLayer, cam1Calibration);
        if(originAndAxesLayer->autoScaleOn){
            emit editUpperBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][1])));
            emit editLowerBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][0])));
        } else {
            emit editUpperBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][1])));
            emit editLowerBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
        }
        scaleDisplay->setCurrentImgMat(scaleMat);
        scaleDisplay->update();
    }

    void displacementsModule::onCartPolarCoord(int val){
        qDebug() << "Solution loaded";
        originAndAxesLayer->setPolarCartesian(val);
        if(solutionLoaded){
            dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
            displacementDisplay();
            if(originAndAxesLayer->autoScaleOn){
                emit editUpperBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][1])));
                emit editLowerBoundText(QString::number(convertToUnits(dispFbk->autoBounds[dataIdx][0])));
            } else {
                emit editUpperBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][1])));
                emit editLowerBoundText(QString::number(convertToUnits(originAndAxesLayer->manualMinMaxSlider[dataIdx][0])));
            }
        }
    }

    void displacementsModule::colormapSlider(int val)
    {
        originAndAxesLayer->colormapCoef = (float)val/100.;
        displacementDisplay();
    }

    void displacementsModule::referenceRadio(bool val)
    {
        originAndAxesLayer->deformedConfiguration = !val;
        if (cam1Files->getFileNames().size()>0){
            emit loadRefImage(cam1Files->getCurrentImgIdx());
            loadFormatAndDisplay();
        }

    }


    void displacementsModule::spatialRadio(bool val)
    {
        originAndAxesLayer->spatialCoordinates = val;
        if (solutionLoaded){
            dispFbk->computeMaskAndLimits(dataIdx, originAndAxesLayer);
            displacementDisplay();
        }
    }
