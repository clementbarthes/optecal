#include "postprocessingmodule.h"

postProcessingModule::postProcessingModule(QListWidget* strainGaugeList, QListWidget* extensometerList,
                                           QPushButton* addStrainGaugeButton, QPushButton* addExtensometerButton,
                                           QLabelWMouse *imgDisplay, autoResize *cam1Display, displacements *dispFbk,
                                           fileList *correlationFiles, virtualMeasurementTools *virtualTools,
                                           drawOrigin *originAndAxesLayer, bool *licenseValidated)
{
    this->strainGaugeList = strainGaugeList;
    this->extensometerList = extensometerList;
    this->addStrainGaugeButton = addStrainGaugeButton;
    this->addExtensometerButton = addExtensometerButton;
    this->dispFbk = dispFbk;
    this->imgDisplay = imgDisplay;
    this->cam1Display = cam1Display;
    this->correlationFiles = correlationFiles;
    this->virtualTools = virtualTools;
    this->originAndAxesLayer = originAndAxesLayer;
    this->licenseValidated = licenseValidated;
    connect(this->virtualTools->pd,SIGNAL(canceled()),this,SLOT(exportCanceled()));

}

void postProcessingModule::deleteStrainGauge(int idx)
{
    if((idx>=0) && (idx<(int)virtualTools->strainGaugeList.size())){
        strainGaugeList->takeItem(idx);
        virtualTools->deleteStrainGauge(idx);
        virtualTools->currentStrainGauge = 0;

    }
}

void postProcessingModule::deleteExtensometer(int idx)
{
    if((idx>=0) && (idx<(int)virtualTools->extensometerList.size())){
        extensometerList->takeItem(idx);
        virtualTools->deleteExtensometer(idx);
        virtualTools->currentExtensometer = 0;
    }
}


void postProcessingModule::addStrainGaugeClicked()
{
    Mouse_Entered();
    addStrainGaugeButton->setEnabled(false);
//    cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);


    qDebug() << "add Strain Gauge";
    virtualTools->addStrainGauge();

    strainGaugeList->addItem(virtualTools->strainGaugeList.back().name);
    strainGaugeList->setCurrentRow((int)virtualTools->strainGaugeList.size()-1);
    virtualTools->currentStrainGauge = (int)virtualTools->strainGaugeList.size()-1;

}

void postProcessingModule::addExtensometerClicked()
{

    Mouse_Entered();
    addExtensometerButton->setEnabled(false);
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);

    qDebug() << "add extensometer";
    virtualTools->addExtensometer();
    extensometerList->addItem(virtualTools->extensometerList.back().name);
    extensometerList->setCurrentRow((int)virtualTools->extensometerList.size()-1);
    virtualTools->currentExtensometer = (int)virtualTools->extensometerList.size()-1;
}

void postProcessingModule::exportButton()
{
    virtualTools->exportResults(correlationFiles, originAndAxesLayer);

}

void postProcessingModule::strainGaugeListRowChanged(int idx)
{
    virtualTools->currentExtensometer = -1;
    virtualTools->currentStrainGauge = idx;
    extensometerList->setCurrentRow(-1);
    virtualTools->updateDrawing();
    cam1Display->updateResized();
}

void postProcessingModule::extensometerListRowChanged(int idx)
{
    qDebug() << "Break0";
    virtualTools->currentStrainGauge = -1;
    virtualTools->currentExtensometer = idx;

    strainGaugeList->setCurrentRow(-1);
    virtualTools->updateDrawing();
    cam1Display->updateResized();
}

void postProcessingModule::Mouse_current_pos()
{
    int isNear;
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    if(virtualTools->strainGaugeDrawingCenter){
        virtualTools->updateCenter(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if (virtualTools->strainGaugeDrawingWidth){
        virtualTools->updateWidth(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if(virtualTools->extensometerDrawingInProgress){
        virtualTools->addExtensometerPoint(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if((virtualTools->updateCenterInProgress ||
               (virtualTools->isMouseNearPoint(&currentPoint)
               == virtualMeasurementTools::mouseNearCenter))
              && imgDisplay->leftClickHeld){
        virtualTools->updateCenterInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        virtualTools->updateCenter(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if((virtualTools->updateWidthInProgress ||
               (virtualTools->isMouseNearPoint(&currentPoint)
               == virtualMeasurementTools::mouseNearCorner))
              && imgDisplay->leftClickHeld){
        virtualTools->updateWidthInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        virtualTools->updateWidth(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if((virtualTools->updateAngleInProgress ||
               (virtualTools->isMouseNearPoint(&currentPoint)
               == virtualMeasurementTools::mouseNearVector))
              && imgDisplay->leftClickHeld){
        virtualTools->updateAngleInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        virtualTools->updateAngle(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else if((virtualTools->updateExtensometerInProgress ||
               (virtualTools->isMouseNearPoint(&currentPoint)
               == virtualMeasurementTools::mouseNearExtensometer))
              && imgDisplay->leftClickHeld){
        virtualTools->updateExtensometerInProgress = true;
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        virtualTools->updateExtensometer(&currentPoint);
        virtualTools->updateDrawing();
        cam1Display->updateResized();
    } else{
        if((isNear = virtualTools->isMouseNearPoint(&currentPoint))>0){
            imgDisplay->setCursor(Qt::OpenHandCursor);
        } else {
            imgDisplay->setCursor(Qt::ArrowCursor);
        }
        virtualTools->updateCenterInProgress = false;
        virtualTools->updateWidthInProgress = false;
        virtualTools->updateAngleInProgress = false;
        virtualTools->updateExtensometerInProgress = false;
    }
}

void postProcessingModule::Mouse_Entered()
{
    imageResizeCoef = cam1Display->getResizeCoef();
}

void postProcessingModule::Mouse_Pressed()
{
    if(virtualTools->strainGaugeDrawingWidth){
        virtualTools->strainGaugeDrawingWidth = false;
        imgDisplay->releaseKeyboard();
        imgDisplay->setCursor(Qt::ArrowCursor);
        addStrainGaugeButton->setEnabled(true);
    }
    if(virtualTools->strainGaugeDrawingCenter){
        virtualTools->strainGaugeDrawingCenter = false;
        virtualTools->strainGaugeDrawingWidth = true;
    }
    if(virtualTools->extensometerDrawingInProgress){
        virtualTools->setExtensometerPoint();
        if(!virtualTools->extensometerDrawingInProgress){
            imgDisplay->releaseKeyboard();
            imgDisplay->setCursor(Qt::ArrowCursor);
            addExtensometerButton->setEnabled(true);
        }
    }
}

void postProcessingModule::Key_Pressed()
{

    if((imgDisplay->key == Qt::Key_Return)
            |(imgDisplay->key == Qt::Key_Space)){
        Mouse_Pressed();
    } else if(imgDisplay->key == Qt::Key_Escape){
        imgDisplay->releaseKeyboard();
        if(virtualTools->strainGaugeDrawingCenter || virtualTools->strainGaugeDrawingWidth)
        {
            addStrainGaugeButton->setEnabled(true);
            deleteStrainGauge(virtualTools->currentStrainGauge);
            virtualTools->strainGaugeDrawingCenter = false;
            virtualTools->strainGaugeDrawingWidth = false;
            virtualTools->updateDrawing();
            cam1Display->updateResized();
        } else if(virtualTools->extensometerDrawingInProgress){
            addExtensometerButton->setEnabled(true);
            deleteExtensometer(virtualTools->currentExtensometer);
            virtualTools->extensometerDrawingInProgress = false;
            virtualTools->updateDrawing();
            cam1Display->updateResized();
        }
    }
}


void postProcessingModule::on_customContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = strainGaugeList->viewport()->mapToGlobal(pos);
    int currentRowSelected = strainGaugeList->currentRow();
    QMenu fileManageMenu;
    if(strainGaugeList->currentRow()>=0){
        fileManageMenu.addAction("Delete strain gauge")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem)
        {
            if(selectedItem->text() == "Delete strain gauge"){
                deleteStrainGauge(currentRowSelected);
            }
        }
    }
}

void postProcessingModule::on_customContextExtensometer(const QPoint &pos)
{
    QPoint globalPos = extensometerList->viewport()->mapToGlobal(pos);
    int currentRowSelected = extensometerList->currentRow();
    QMenu fileManageMenu;
    if(extensometerList->currentRow()>=0){
        fileManageMenu.addAction("Delete extensometer")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem)
        {
            if(selectedItem->text() == "Delete extensometer"){
                deleteExtensometer(currentRowSelected);
            }
        }
    }
}

void postProcessingModule::exportCanceled()
{
    virtualTools->exportCanceled = true;
    virtualTools->pd->close();
}
