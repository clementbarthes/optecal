#include "roimodule.h"




roiModule::roiModule(QLabelWMouse *imgDisplay,
                     QPushButton *plusPolyButton,
                     QPushButton *minusPolyButton,
                     QPushButton *plusCircleButton,
                     QPushButton *minusCircleButton,
                     QLineEdit *pixelsText,
                     QLineEdit *unitText,
                     drawShape *measureToolShape,
                     QPushButton *measureButton,
                     QLabel* pixelEURatioLabel,
                     calibration *cam1Calibration,
                     drawShape* roiShapes,
                     autoResize* cam1Display,
                     fileList* correlationFiles,
                     fileList* rawFiles,
                     QListWidget *fileListWidget)
{

    this->imgDisplay = imgDisplay;
    this->plusPolyButton = plusPolyButton;
    this->minusPolyButton = minusPolyButton;
    this->plusCircleButton = plusCircleButton;
    this->minusCircleButton = minusCircleButton;
    this->pixelsText = pixelsText;
    this->unitText = unitText;
    this->measureToolShape = measureToolShape;
    this->measureButton = measureButton;
    this->pixelEURatioLabel = pixelEURatioLabel;
    this->cam1Calibration = cam1Calibration;
    this->roiShapes = roiShapes;
    this->cam1Display = cam1Display;
    this->rawFiles = rawFiles;
    this->correlationFiles = correlationFiles;
    this->fileListWidget = fileListWidget;
}

void roiModule::plusPoly()
{
    plusPolyButton->setDown(true);
    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    roiShapes->initShape(drawShape::plusPoly);


}

void roiModule::minusPoly()
{
    minusPolyButton->setDown(true);
    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    roiShapes->initShape(drawShape::minusPoly);
}

void roiModule::plusCircle(){
    plusCircleButton->setDown(true);
    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    roiShapes->initShape(drawShape::plusCircle);

}

void roiModule::minusCircle()
{
    plusCircleButton->setDown(true);
    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    roiShapes->initShape(drawShape::minusCircle);
}


void roiModule::pixelLineEdited()
{
    qDebug() << "Pixel line edited";
    cam1Calibration->pxLine = pixelsText->text().toDouble();
}

void roiModule::unitsLineEdited()
{
    qDebug() << "Unit line edited";
    cam1Calibration->unitLine = unitText->text().toDouble();
}

void roiModule::unitChanged(int val)
{
    qDebug() << "Unit changed: " << val;
    cam1Calibration->unitFlag = val;
}

void roiModule::applyScale()
{
    switch (cam1Calibration->unitFlag) {
    case calibration::mmUnit:
        cam1Calibration->mmPerPixel = cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;
    case calibration::cmUnit:
        cam1Calibration->mmPerPixel = 10.*cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;
    case calibration::mUnit:
        cam1Calibration->mmPerPixel = 1000.*cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;
    case calibration::inUnit:
        cam1Calibration->mmPerPixel = 25.399986*cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;
    case calibration::ftUnit:
        cam1Calibration->mmPerPixel = 304.79999*cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;

    default:
        cam1Calibration->mmPerPixel = cam1Calibration->unitLine/cam1Calibration->pxLine;
        break;
    }
    cam1Calibration->ratioDisplayed = cam1Calibration->pxLine/cam1Calibration->unitLine;
    displayScale();

}

void roiModule::displayScale(){
    QString unitLabel;
    switch (cam1Calibration->unitFlag) {
    case calibration::mmUnit:
        unitLabel = "mm";
        break;
    case calibration::cmUnit:
        unitLabel = "cm";
        break;
    case calibration::mUnit:
        unitLabel = "m";
        break;
    case calibration::inUnit:
        unitLabel = "in";
        break;
    case calibration::ftUnit:
        unitLabel = "ft";
        break;

    default:
        unitLabel = "mm";
        break;
    }
    pixelEURatioLabel->setText("pixel/" + unitLabel + " ratio =" + QString::number(cam1Calibration->ratioDisplayed));


}

void roiModule::measureTool()
{
    correlationFiles->setCurrentImgIdx(correlationFiles->getRefImageIdx());
    cam1Display->update();
    fileListWidget->setCurrentRow(correlationFiles->getRefImageIdx());
    if(cam1Display->getCurrentResizedImg()->empty()){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No image file loaded");
        noFileErrorMessage.exec();
        return;
    }
    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());

    measureToolShape->clearShapes();

    qDebug() << "Measuring...";
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    measureToolShape->initShape(drawShape::lineOnly);
    measureButton->setEnabled(false);
}

void roiModule::releaseMeasureTool()
{
    measureButton->setEnabled(true);
    imgDisplay->releaseKeyboard();
}



void roiModule::Mouse_current_pos()
{
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    int isNear;

    if(roiShapes->drawingInProgress){
        roiShapes->updatePoint(&currentPoint);
        roiShapes->updateWLines();
        measureToolShape->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
        measureToolShape->updateWLines();

        cam1Display->updateResized();
    } else if((roiShapes->updatePointInProgress ||
               (isNear = roiShapes->isMouseNearPoint(&currentPoint))>0)
              && imgDisplay->leftClickHeld){
        roiShapes->updatePointInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        roiShapes->updatePoint(&currentPoint);
        roiShapes->updateWLines();
        measureToolShape->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
        measureToolShape->updateWLines();

        cam1Display->updateResized();
    } else if(measureToolShape->drawingInProgress){
        measureToolShape->updatePoint(&currentPoint);
        measureToolShape->updateWLines();
        cam1Calibration->pxLine = measureToolShape->getLength();
        pixelsText->setText(QString::number(cam1Calibration->pxLine));

        cam1Display->updateResized();
    } else if((measureToolShape->updatePointInProgress ||
               (isNear = measureToolShape->isMouseNearPoint(&currentPoint))>0)
              && imgDisplay->leftClickHeld){
        measureToolShape->updatePointInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        measureToolShape->updatePoint(&currentPoint);
        measureToolShape->updateWLines();
        cam1Calibration->pxLine = measureToolShape->getLength();
        pixelsText->setText(QString::number(cam1Calibration->pxLine));
        cam1Display->updateResized();
    } else{
        if((isNear = measureToolShape->isMouseNearPoint(&currentPoint))>0){
            imgDisplay->setCursor(Qt::OpenHandCursor);
        } else if((isNear = roiShapes->isMouseNearPoint(&currentPoint))>0){
            imgDisplay->setCursor(Qt::OpenHandCursor);
        } else {
            imgDisplay->setCursor(Qt::ArrowCursor);
        }
        roiShapes->updatePointInProgress = false;

        measureToolShape->updatePointInProgress = false;
    }
}

void roiModule::Mouse_Entered(){
    imageResizeCoef = cam1Display->getResizeCoef();
}

void roiModule::Mouse_Pressed()
{
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    if(roiShapes->drawingInProgress){
        roiShapes->setPoint(currentPoint);
        // If roiShapes sets drawingInProgress to false, then call
        // releaseDrawingButtons
        if(!roiShapes->drawingInProgress) releaseDrawingButtons();
    }else if (roiShapes->isMouseNearPoint(&currentPoint)){
        qDebug() << "Grabbed Point";
        imgDisplay->setCursor(Qt::ClosedHandCursor);
    }


    if(measureToolShape->drawingInProgress){
        measureToolShape->setPoint(currentPoint);
        // If measureToolShape sets drawingInProgress to false, then call
        // releaseDrawingButtons
        if(!measureToolShape->drawingInProgress)
            releaseMeasureTool();
    }else if (measureToolShape->isMouseNearPoint(&currentPoint)){
        qDebug() << "Grabbed Point";
        imgDisplay->setCursor(Qt::ClosedHandCursor);
    }
}

void roiModule::Mouse_DoubleClick()
{
    if(roiShapes->drawingInProgress){
        roiShapes->acceptShape();
        // Double-click creates 2 extra points, so reject one:
        roiShapes->rejectLastPoint();
        releaseDrawingButtons();
    } else if(roiShapes->updatePointInProgress){
        roiShapes->acceptShape();
    }

}

void roiModule::Key_Pressed()
{
    if(roiShapes->drawingInProgress==true)
    {
        if((imgDisplay->key == Qt::Key_Return)
                |(imgDisplay->key == Qt::Key_Space)){
            imgDisplay->releaseKeyboard();
            roiShapes->acceptShape();
        } else if(imgDisplay->key == Qt::Key_Escape){
            cancelDrawing();
            cam1Display->updateResized();
        }
    }

    if(measureToolShape->drawingInProgress==true)
    {
        if((imgDisplay->key == Qt::Key_Return)
                |(imgDisplay->key == Qt::Key_Space)){
            imgDisplay->releaseKeyboard();
            measureToolShape->acceptShape();
        } else if(imgDisplay->key == Qt::Key_Escape){
            cancelDrawing();
            cam1Display->updateResized();
        }
    }
}

void roiModule::cancelDrawing(){
    if(roiShapes->drawingInProgress){
        imgDisplay->releaseKeyboard();
        roiShapes->rejectLastPoint();
        releaseDrawingButtons();
        roiShapes->updateWLines();
        measureToolShape->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
        measureToolShape->updateWLines();
    }
    if(measureToolShape->drawingInProgress)
    {
        imgDisplay->releaseKeyboard();
        measureToolShape->rejectLastPoint();
        releaseMeasureTool();
        measureToolShape->updateWLines();
    }
}

void roiModule::roiIsDrawn()
{
    minusPolyButton->setEnabled(true);
    minusCircleButton->setEnabled(true);
    plusCircleButton->setEnabled(true);
    plusPolyButton->setEnabled(true);
    measureButton->setEnabled(true);
}

void roiModule::mouseRightClick(QPoint pos)
{
    QPoint globalPos = imgDisplay->mapToGlobal(pos);
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    if(measureToolShape->isMouseNearPoint(&currentPoint)){
        QMenu fileManageMenu;
        fileManageMenu.addAction("Delete ruler")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem){
            measureToolShape->deleteShape();
            roiShapes->updateWLines();
            measureToolShape->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            measureToolShape->updateWLines();
            cam1Display->updateResized();
        }
    } else if (roiShapes->isMouseNearPoint(&currentPoint)){
        QMenu fileManageMenu;
        if (roiShapes->isMouseNearPoint(&currentPoint) == drawShape::mouseNearPolyVertex)
        fileManageMenu.addAction("Delete point")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        fileManageMenu.addAction("Delete shape")->setIcon(QIcon(":/resources/1415541461_Error.png"));

        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem)
        {
            if(selectedItem->text() == "Delete point"){
                roiShapes->deletePoint();

            } else if (selectedItem->text() == "Delete shape"){
                roiShapes->deleteShape();
            }
            roiShapes->updateWLines();
            measureToolShape->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            measureToolShape->updateWLines();
            cam1Display->updateResized();
        }
    }
}

void roiModule::convertToTiff()
{
    LibRaw RawProcessor;
    qDebug() << "Converting to TIFF";
}

void roiModule::releaseDrawingButtons(){
    plusPolyButton->setDown(false);
    minusPolyButton->setDown(false);
    plusCircleButton->setDown(false);
    minusCircleButton->setDown(false);
    imgDisplay->releaseKeyboard();
}



void roiModule::setCursorStyle(int isNear){

    switch (isNear){
    case drawShape::mouseNearPolyVertex:
        imgDisplay->setCursor(Qt::SizeBDiagCursor);
        break;
    case drawShape::mouseNearCircleCenter:
        imgDisplay->setCursor(Qt::SizeAllCursor);
        break;
    case drawShape::mouseNearCircleEdgeLeft:
        imgDisplay->setCursor(Qt::SizeFDiagCursor);
        break;
    case drawShape::mouseNearCircleEdgeRight:
        imgDisplay->setCursor(Qt::SizeBDiagCursor);
        break;
    }
}


