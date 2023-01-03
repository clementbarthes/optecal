#include "optecal.h"
#include "ui_optecal.h"
#include "filelist.h"
#include "filelistpage.h"
#include "autoresize.h"
#include "staticreadwritefunctions.h"
#include <QDesktopServices>
#include <QUrl>


OpteCAL::OpteCAL(int argc, char *argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpteCAL)
{
    ui->setupUi(this);

    softwareVersion = QString("2.0");
    licenseValidated = true;

    // If no settings file is loaded, rootFolder is the folder hosting the exe file.
    rootFolder = QDir(QDir::currentPath());

    loadRawImages = new QFileDialog(this);
    loadImages = new QFileDialog(this);
    cam1Display = new autoResize();
    ui->currentImgDisplay->allowZoom = true;
    scaleDisplay = new autoResize();

    roiShapes = new drawShape();

    measureTool = new drawShape();

    originAndAxesLayer = new drawOrigin();

    subsetList = new subsetsMap();

    seedLayer = new drawSeedPoint();

    dispFbk = new displacements();
    
    virtualTools = new virtualMeasurementTools();

    cam1Calibration = new calibration();

    correlationFiles = new fileList(fileList::correlationFiles, rootFolder);
    calibrationFiles = new fileList(fileList::calibrationFiles, rootFolder);
    rawFiles = new fileList(fileList::rawFiles, rootFolder);


    
    calibrationFilePage = new fileListCalibrationPage(loadImages,ui->listFilesCalWidget,
                                                      cam1Display,calibrationFiles, cam1Calibration);

    rawFilePage = new fileListPage(loadRawImages,ui->rawFilesWidget,
                                   cam1Display,rawFiles);

    rawModuleInstance = new rawModule(rawFiles, rawFilePage, &rootFolder, ui->currentImgDisplay, ui->rawFilesWidget);
    
    correlationFilePage = new fileListCorrelationPage(loadImages, ui->listFilesWidget,
                                                      cam1Display,correlationFiles,
                                                      roiShapes, seedLayer,
                                                      originAndAxesLayer,
                                                      virtualTools);
    
    calibrationModuleInstance = new calibrationModule(cam1Calibration,
                                                      cam1Display, ui->currentImgDisplay,
                                                      ui->cropFactorEdit,ui->aEdit,ui->bEdit,ui->cEdit);

    roiModuleInstance = new roiModule(ui->currentImgDisplay, ui->plusPolyButton,
                                      ui->minusPolyButton ,ui->plusCircleButton,
                                      ui->minusCircleButton, ui->pixelLineEdit,
                                      ui->unitLineEdit, measureTool, ui->measureButton,
                                      ui->pixelEURatioLabel,cam1Calibration,
                                      roiShapes, cam1Display, correlationFiles,
                                      rawFiles, ui->listFilesWidget);
    
    runAnalysisInstance = new runAnalysisModule(ui->currentImgDisplay,subsetList, cam1Display,
                                                seedLayer,correlationFiles, roiShapes, dispFbk,
                                                ui->subsetSizeText,ui->subsetSizeSlider,
                                                ui->subsetSpacingText,ui->subsetSpacingSlider,
                                                ui->setSeedButton,ui->corrRejectionLineEdit,
                                                ui->listFilesWidget);
    
    displacementsModuleInstance = new displacementsModule(ui->currentImgDisplay, cam1Display, scaleDisplay,
                                                          correlationFiles,dispFbk, roiShapes, originAndAxesLayer,
                                                          cam1Calibration, ui->lowerBoundText,
                                                          ui->upperBoundText,ui->clippingValText,
                                                          ui->amplificationEdit, ui->backgroundEdit);

    postProcessingModuleInstance = new postProcessingModule(ui->virtualStrainGaugeList,ui->extensometerList,
                                                            ui->addStrainGaugeButton,ui->addExtensometerButton,
                                                            ui->currentImgDisplay,cam1Display, dispFbk,
                                                            correlationFiles, virtualTools, originAndAxesLayer,
                                                            &licenseValidated);

    exportModuleInstance = new exportModule(correlationFiles, originAndAxesLayer, cam1Calibration,
                                            dispFbk,&rootFolder, ui->listFilesWidget, &licenseValidated);

    ui->modulesToolBox->widget(0)->setVisible(false);
    ui->loadFilesToolBox->widget(1)->setVisible(false);
    ui->modulesToolBox->removeItem(0);
    ui->loadFilesToolBox->removeItem(1);

    ui->amplifiedMotionBox->setVisible(false);
    ui->modulesToolBox->setStyleSheet("icon-size: 30px");
    ui->modulesToolBox->setCurrentIndex(1);
    ui->modulesToolBox->setCurrentIndex(0);
    ui->loadFilesToolBox->setCurrentIndex(1);
    ui->rawGroupBox->setVisible(false);
    ui->calibrationGroupBox->setVisible(false);
    ui->logoLabel->setVisible(false);
    ui->loadFilesToolBox->setStyleSheet("icon-size: 30px");
    ui->corrRejectionLineEdit->setValidator(new QDoubleValidator(0.0,999.0, 5, ui->corrRejectionLineEdit));
    ui->amplificationEdit->setValidator(new QIntValidator ( 1, 1000, this));
    ui->backgroundEdit->setValidator(new QIntValidator ( 0, 100, this));
    connect(ui->currentImgDisplay,SIGNAL(updateSize(float,float)),this,SLOT(zoomEvent(float,float)));
    connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), this, SLOT(panEvent()));
    /// Connections for the raw files page
    connect(ui->loadRawImage,SIGNAL(clicked()),rawFilePage,SLOT(on_loadImage_clicked()));
    connect(ui->sortRawFilesComboBox,SIGNAL(currentIndexChanged(int)),rawFilePage,SLOT(on_sortFilesComboBox_currentIndexChanged(int)));
    connect(ui->rawFilesWidget,SIGNAL(currentRowChanged(int)),rawFilePage,SLOT(on_listFilesWidget_currentRowChanged(int)));
    connect(ui->rawFilesWidget,SIGNAL(customContextMenuRequested(QPoint)),rawFilePage,SLOT(on_listFilesWidget_customContextMenuRequested(QPoint)));
    connect(rawFilePage,SIGNAL(correctThumbnailDistortion()),this,SLOT(correctLensDistortion()));


    /// Connections for the correlation files page
    connect(ui->loadImage,SIGNAL(clicked()),correlationFilePage,SLOT(on_loadImage_clicked()));
    connect(ui->listFilesWidget,SIGNAL(currentRowChanged(int)),correlationFilePage,SLOT(on_listFilesWidget_currentRowChanged(int)));
    connect(ui->sortFilesComboBox,SIGNAL(currentIndexChanged(int)),correlationFilePage,SLOT(on_sortFilesComboBox_currentIndexChanged(int)));
    connect(ui->modulesToolBox,SIGNAL(currentChanged(int)),correlationFilePage,SLOT(on_modulesToolBoxIndex(int)));
    connect(ui->listFilesWidget,SIGNAL(customContextMenuRequested(QPoint)),correlationFilePage,SLOT(on_listFilesWidget_customContextMenuRequested(QPoint)));
    connect(correlationFilePage,SIGNAL(enablePlusShapes(bool)),ui->plusPolyButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enablePlusShapes(bool)),ui->plusCircleButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enableMinusShapes(bool)),ui->minusPolyButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enableMinusShapes(bool)),ui->minusCircleButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enablePlusShapes(bool)),ui->measureButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enablePlusShapes(bool)),ui->addStrainGaugeButton,SLOT(setEnabled(bool)));
    connect(correlationFilePage,SIGNAL(enablePlusShapes(bool)),ui->addExtensometerButton,SLOT(setEnabled(bool)));
    connect(ui->pauseButton,SIGNAL(clicked()),correlationFilePage,SLOT(pause_Button()));
    connect(ui->playButton,SIGNAL(clicked()),correlationFilePage,SLOT(play_Button()));
    connect(cam1Display,SIGNAL(newCorrelationFilePath(QString)),this,SLOT(updateCorrelationFilesFolder(QString)));
    //connect(this,SIGNAL(listOfMultipleFiles(QModelIndexList)),correlationFilePage,SLOT(multipleFrameSelection(QModelIndexList)));

    /// Connections for the RAW module
    //connect(this,SIGNAL(listOfMultipleFiles(QModelIndexList)),rawModuleInstance,SLOT(multipleFrameSelection(QModelIndexList)));
    connect(ui->convertSelectedButton,SIGNAL(clicked()),rawModuleInstance,SLOT(multipleFrame()));
    connect(ui->convertAllButton,SIGNAL(clicked()),rawModuleInstance,SLOT(allFrames()));
    connect(ui->turnCWButton,SIGNAL(clicked()),rawModuleInstance,SLOT(clockwiseButton()));
    connect(ui->turnCCWButton,SIGNAL(clicked()),rawModuleInstance,SLOT(counterClockwiseButton()));

    /// Connections for the calibration module
    connect(ui->makerCombo,SIGNAL(currentIndexChanged(int)),calibrationModuleInstance,SLOT(cameraMakerChanged(int)));
    connect(ui->modelCombo,SIGNAL(currentIndexChanged(int)),calibrationModuleInstance,SLOT(cameraModelChanged(int)));
    connect(ui->lensMakerCombo,SIGNAL(currentIndexChanged(int)),calibrationModuleInstance,SLOT(lensMakerChanged(int)));
    connect(ui->lensCombo,SIGNAL(activated(int)),calibrationModuleInstance,SLOT(lensModelChanged(int)));
    connect(ui->focalLengthCombo,SIGNAL(currentIndexChanged(int)),calibrationModuleInstance,SLOT(focalLengthChanged(int)));
    connect(calibrationModuleInstance,SIGNAL(cropFactor(QString)),ui->cropFactorEdit,SLOT(setText(QString)));
    connect(ui->cropFactorEdit,SIGNAL(editingFinished()),calibrationModuleInstance,SLOT(cropFactorEdited()));
    connect(ui->aEdit,SIGNAL(editingFinished()),calibrationModuleInstance,SLOT(aCalEdited()));
    connect(ui->bEdit,SIGNAL(editingFinished()),calibrationModuleInstance,SLOT(bCalEdited()));
    connect(ui->cEdit,SIGNAL(editingFinished()),calibrationModuleInstance,SLOT(cCalEdited()));
    connect(calibrationModuleInstance,SIGNAL(calA(QString)),ui->aEdit,SLOT(setText(QString)));
    connect(calibrationModuleInstance,SIGNAL(calB(QString)),ui->bEdit,SLOT(setText(QString)));
    connect(calibrationModuleInstance,SIGNAL(calC(QString)),ui->cEdit,SLOT(setText(QString)));
    connect(ui->enableCalibrationCheck,SIGNAL(toggled(bool)),calibrationModuleInstance,SLOT(enableLensCorrection(bool)));


    /// Connections for the ROI module
    connect(ui->plusPolyButton,SIGNAL(clicked()),roiModuleInstance,SLOT(plusPoly()));
    connect(ui->minusPolyButton,SIGNAL(clicked()),roiModuleInstance,SLOT(minusPoly()));
    connect(ui->plusCircleButton,SIGNAL(clicked()),roiModuleInstance,SLOT(plusCircle()));
    connect(ui->minusCircleButton,SIGNAL(clicked()),roiModuleInstance,SLOT(minusCircle()));
    connect(ui->pixelLineEdit,SIGNAL(editingFinished()),roiModuleInstance,SLOT(pixelLineEdited()));
    connect(ui->unitLineEdit,SIGNAL(editingFinished()),roiModuleInstance,SLOT(unitsLineEdited()));
    connect(ui->unitComboBox,SIGNAL(currentIndexChanged(int)),roiModuleInstance,SLOT(unitChanged(int)));
    connect(ui->applyScaleButton,SIGNAL(clicked()),roiModuleInstance,SLOT(applyScale()));
    connect(ui->measureButton,SIGNAL(clicked()),roiModuleInstance,SLOT(measureTool()));
    connect(correlationFilePage,SIGNAL(updateDisplay()),this,SLOT(resizeFunctions()));

    /// Connections for the Run analysis module
    connect(ui->subsetSizeText,SIGNAL(editingFinished()),runAnalysisInstance,SLOT(on_subsetSizeText_editingFinished()));
    connect(ui->subsetSizeSlider,SIGNAL(valueChanged(int)),runAnalysisInstance,SLOT(on_subsetSizeSlider_valueChanged(int)));
    connect(ui->subsetSpacingText,SIGNAL(editingFinished()),runAnalysisInstance,SLOT(on_subsetSpacingText_editingFinished()));
    connect(ui->subsetSpacingSlider,SIGNAL(valueChanged(int)),runAnalysisInstance,SLOT(on_subsetSpacingSlider_valueChanged(int)));
    connect(ui->splineComboBox,SIGNAL(currentIndexChanged(int)),runAnalysisInstance,SLOT(splineOrder(int)));
    connect(ui->searchRegionSpinBox,SIGNAL(valueChanged(int)),runAnalysisInstance,SLOT(searchRegionBox(int)));
    connect(ui->setSeedButton,SIGNAL(clicked()),runAnalysisInstance,SLOT(on_setSeedButton_clicked()));
    connect(ui->analyzeCurrentFrameButton,SIGNAL(clicked()),runAnalysisInstance,SLOT(multipleFrame()));
    connect(ui->analyseAllFramesButton,SIGNAL(clicked()),runAnalysisInstance,SLOT(analyzeAllFrames()));
    connect(ui->highStrainCheckBox,SIGNAL(clicked(bool)),runAnalysisInstance,SLOT(highStrainEnable(bool)));
    //connect(ui->intenseSearchCheckBox,SIGNAL(clicked(bool)),runAnalysisInstance,SLOT(intenseSearchEnable(bool)));
    connect(ui->guiResponsiveCheckBox,SIGNAL(clicked(bool)),runAnalysisInstance,SLOT(allCPUCheck(bool)));
    //connect(this,SIGNAL(listOfMultipleFiles(QModelIndexList)),runAnalysisInstance,SLOT(multipleFrameSelection(QModelIndexList)));
    connect(ui->corrRejectionLineEdit,SIGNAL(editingFinished()),runAnalysisInstance,SLOT(corrCoefRejection_Edited()));

    /// Connections for the dislay results module
    connect(ui->lowerBoundSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(lowerBoundSliderChanged(int)));
    connect(ui->upperBoundSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(upperBoundSliderChanged(int)));
    connect(ui->lowerBoundSlider,SIGNAL(sliderMoved(int)),displacementsModuleInstance,SLOT(lowerBoundSliderMovedByUser(int)));
    connect(ui->upperBoundSlider,SIGNAL(sliderMoved (int)),displacementsModuleInstance,SLOT(upperBoundSliderMovedByUser(int)));
    connect(ui->amplificationSlider,SIGNAL(sliderMoved(int)),displacementsModuleInstance,SLOT(amplificationMovedByUser(int)));
    connect(ui->amplificationSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(amplificationSliderChanged(int)));
    connect(ui->backgroundSlider,SIGNAL(sliderMoved(int)),displacementsModuleInstance,SLOT(backgroundMovedByUser(int)));
    connect(ui->dispComboBox,SIGNAL(activated(int)),displacementsModuleInstance,SLOT(dispComboBoxChanged(int)));
    connect(ui->filterSlider,SIGNAL(sliderMoved(int)),displacementsModuleInstance,SLOT(medianFilterChanged(int)));
    connect(ui->gaussianFilterSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(gaussianFilterChanged(int)));
    connect(ui->correlClipSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(clippingChanged(int)));
    connect(ui->lowerBoundText,SIGNAL(editingFinished()),displacementsModuleInstance,SLOT(lowerBoundEdited()));
    connect(ui->upperBoundText,SIGNAL(editingFinished()),displacementsModuleInstance,SLOT(upperBoundEdited()));
    connect(ui->amplificationEdit,SIGNAL(editingFinished()),displacementsModuleInstance,SLOT(amplificationEdited()));
    connect(ui->backgroundEdit,SIGNAL(editingFinished()),displacementsModuleInstance,SLOT(backgroundEdited()));
    connect(ui->clippingValText,SIGNAL(editingFinished()),displacementsModuleInstance,SLOT(clippingValEdited()));
    connect(ui->scaleComboBox,SIGNAL(activated(int)),displacementsModuleInstance,SLOT(scaleAuto(int)));
    connect(displacementsModuleInstance,SIGNAL(editLowerBoundText(QString)),ui->lowerBoundText,SLOT(setText(QString)));
    connect(displacementsModuleInstance,SIGNAL(editUpperBoundText(QString)),ui->upperBoundText,SLOT(setText(QString)));
    connect(displacementsModuleInstance,SIGNAL(setScaleComboBox(int)),ui->scaleComboBox,SLOT(setCurrentIndex(int)));
    connect(displacementsModuleInstance,SIGNAL(setLowerBoundSlider(int)),ui->lowerBoundSlider,SLOT(setValue(int)));
    connect(displacementsModuleInstance,SIGNAL(setUpperBoundSlider(int)),ui->upperBoundSlider,SLOT(setValue(int)));
    connect(displacementsModuleInstance,SIGNAL(setCorrCoefSlider(int)),ui->correlClipSlider,SLOT(setValue(int)));
    connect(displacementsModuleInstance,SIGNAL(setAmplificationSlider(int)),ui->amplificationSlider,SLOT(setValue(int)));
    connect(displacementsModuleInstance,SIGNAL(setBackgroundSlider(int)),ui->backgroundSlider,SLOT(setValue(int)));
    connect(ui->cartesianPolarComboBox,SIGNAL(currentIndexChanged(int)),displacementsModuleInstance,SLOT(onCartPolarCoord(int)));
    connect(ui->flipXYCheckBox,SIGNAL(clicked(bool)),displacementsModuleInstance,SLOT(onFlipXY(bool)));
    connect(ui->showAxesCheckBox,SIGNAL(clicked(bool)),displacementsModuleInstance,SLOT(onShowAxes(bool)));
    connect(ui->unitsDisplayComboBox,SIGNAL(currentIndexChanged(int)),displacementsModuleInstance,SLOT(unitsChanged(int)));
    connect(displacementsModuleInstance,SIGNAL(setUnitsComboBox(int)),ui->unitsDisplayComboBox,SLOT(setCurrentIndex(int)));
    connect(ui->colormapSlider,SIGNAL(valueChanged(int)),displacementsModuleInstance,SLOT(colormapSlider(int)));
    connect(ui->referenceRadio,SIGNAL(toggled(bool)),displacementsModuleInstance,SLOT(referenceRadio(bool)));
    connect(ui->greenAlmansiRadio,SIGNAL(toggled(bool)),displacementsModuleInstance,SLOT(spatialRadio(bool)));
    connect(displacementsModuleInstance,SIGNAL(loadRefImage(int)),correlationFilePage,SLOT(on_listFilesWidget_currentRowChanged(int)));
    connect(displacementsModuleInstance,SIGNAL(amplifiedMotionBox(bool)),this,SLOT(amplifiedMotion(bool)));

    /// Connections for the post-processing tools
    connect(ui->addStrainGaugeButton,SIGNAL(clicked()),postProcessingModuleInstance,SLOT(addStrainGaugeClicked()));
    connect(ui->addExtensometerButton,SIGNAL(clicked()),postProcessingModuleInstance,SLOT(addExtensometerClicked()));
    connect(ui->ppExportButton,SIGNAL(clicked()),postProcessingModuleInstance,SLOT(exportButton()));
    connect(ui->virtualStrainGaugeList,SIGNAL(currentRowChanged(int)),postProcessingModuleInstance,SLOT(strainGaugeListRowChanged(int)));
    connect(ui->virtualStrainGaugeList,SIGNAL(customContextMenuRequested(QPoint)),postProcessingModuleInstance,SLOT(on_customContextMenuRequested(QPoint)));
    connect(ui->extensometerList,SIGNAL(currentRowChanged(int)),postProcessingModuleInstance,SLOT(extensometerListRowChanged(int)));
    connect(ui->extensometerList,SIGNAL(customContextMenuRequested(QPoint)),postProcessingModuleInstance,SLOT(on_customContextExtensometer(QPoint)));

    /// Connections for the export module
    connect(ui->xCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setXExportCheck(bool)));
    connect(ui->yCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setYExportCheck(bool)));
    connect(ui->uCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setUExportCheck(bool)));
    connect(ui->vCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setVExportCheck(bool)));
    connect(ui->rotationCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setRotationExportCheck(bool)));
    connect(ui->exxCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setExxExportCheck(bool)));
    connect(ui->eyyCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setEyyExportCheck(bool)));
    connect(ui->exyCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setExyExportCheck(bool)));
    connect(ui->pStrain1Check,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setE1ExportCheck(bool)));
    connect(ui->pStrain2Check,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setE2ExportCheck(bool)));
    connect(ui->pDirection1Check,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setDir1ExportCheck(bool)));
    connect(ui->pDirection2Check,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setDir2ExportCheck(bool)));
    connect(ui->vmStrainCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setVMExportCheck(bool)));
    connect(ui->TrescaStrainCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setTrescaExportCheck(bool)));
    connect(ui->corrCoefCheck,SIGNAL(toggled(bool)),exportModuleInstance,SLOT(setCorrCoefExportCheck(bool)));
    connect(ui->exportCurrentButton,SIGNAL(clicked()),exportModuleInstance,SLOT(singleFrameExport()));
    connect(ui->exportAllButton,SIGNAL(clicked()),exportModuleInstance,SLOT(allFramesExport()));
    connect(ui->exportTypeComboBox,SIGNAL(currentIndexChanged(int)),exportModuleInstance,SLOT(setExportType(int)));
    connect(ui->exportFrameRateSpinBox,SIGNAL(valueChanged(double)),exportModuleInstance,SLOT(fpsSpinBox(double)));
    connect(ui->videoTypeComboBox,SIGNAL(currentIndexChanged(int)),exportModuleInstance,SLOT(videoFormat(int)));
    connect(ui->videoExportButton,SIGNAL(clicked()),exportModuleInstance,SLOT(exportVideoButton()));
    //connect(this,SIGNAL(listOfMultipleFiles(QModelIndexList)),exportModuleInstance,SLOT(multipleFrameSelection(QModelIndexList)));



    correlationFiles->setListDisplay(ui->listFilesWidget);

    cam1Calibration->setComboBoxes(ui->makerCombo,ui->modelCombo, ui->lensMakerCombo,
                                   ui->lensCombo, ui->focalLengthCombo);
    rawFiles->setListDisplay(ui->rawFilesWidget);
    cam1Display->setDisplayBox(ui->currentImgDisplay);
    scaleDisplay->setDisplayBox(ui->scaleLabel);
    imageResizeCoef = cam1Display->getResizeCoef();
    subsetList->setSubsetSize(ui->subsetSizeSlider->value());
    subsetList->setSubsetSpacing(ui->subsetSpacingSlider->value());
    seedLayer->setSubsetMap(subsetList);
    runAnalysisInstance->searchRegionBox(ui->searchRegionSpinBox->value());
    originAndAxesLayer->setDisplayFrame(cam1Display);
    virtualTools->setDisplayFrame(cam1Display);
    virtualTools->setRootPath(rootFolder);
    virtualTools->setCalibPointer(cam1Calibration);

    // QTimer is used to wait the end of the resizing before displaying computer intensive layers
    resizeInProgress = new QTimer(this);
    connect(resizeInProgress, SIGNAL(timeout()), this, SLOT(displayColormap()));
    resizeInProgress->setSingleShot(true);

    // QTimer is used to wait the end of the resizing before correcting lens distortion in Raw page
    resizeInProgressCorrection = new QTimer(this);
    connect(resizeInProgressCorrection, SIGNAL(timeout()), this, SLOT(correctLensDistortion()));
    resizeInProgressCorrection->setSingleShot(true);

    QScrollBar* horizontalScroll = ui->scrollArea->horizontalScrollBar();
    connect(horizontalScroll,SIGNAL(rangeChanged(int,int)),this,SLOT(zoomingIn(int,int)));
    QScrollBar* verticalScroll = ui->scrollArea->verticalScrollBar();
    connect(verticalScroll,SIGNAL(rangeChanged(int,int)),this,SLOT(zoomingIn(int,int)));

    //    ui->label_9->setText("argv = " + QString::fromUtf8(argv[1]) +
    //            "  argc = " + QString::number(argc));
    if(argc == 2){
        settingsFilePath =  std::string(argv[1]);
        rootFolder = QFileInfo(QString::fromStdString(settingsFilePath)).absoluteDir();

        loadSettingsFile();
    }

    virtualTools->setLabels(ui->e11Label,ui->e12Label,ui->e22Label,
                            ui->elongationLabel,ui->elongationXLabel,ui->elongationYLabel,
                            ui->sgWidthLabel, ui->sgHeightLabel, ui->sgOriginLabel, ui->sgAngleLabel,
                            ui->extPointsLabel, ui->extLengthLabel);

    //    // QTimer is used to wait the end of the resizing before displaying computer intensive layers
    //    zoomingTimer = new QTimer(this);
    //    connect(zoomingTimer, SIGNAL(timeout()), this, SLOT(zoomingIn()));
    //    zoomingTimer->setSingleShot(true);


    cam1Calibration->loadLensFunDatabase();
    calibrationModuleInstance->enableLensCorrection(false);


    rawConverter::aCal = ui->aEdit;
    rawConverter::bCal = ui->bEdit;
    rawConverter::cCal = ui->cEdit;
    rawConverter::cropFactorEdit = ui->cropFactorEdit;
    rawConverter::distortionCheck = ui->enableCalibrationCheck;
    rawConverter::cam1Calibration = cam1Calibration;

}

OpteCAL::~OpteCAL()
{


    delete loadRawImages;
    delete loadImages;
    delete calibrationFiles;
    delete rawFiles;
    delete cam1Display;
    delete scaleDisplay;
    delete roiShapes;
    delete measureTool;
    delete seedLayer;
    delete originAndAxesLayer;
    delete subsetList;
    delete dispFbk;
    delete correlationFiles;
    delete virtualTools;
    delete cam1Calibration;
    delete ui;
    delete calibrationModuleInstance;
    delete roiModuleInstance;
    delete runAnalysisInstance;
    delete displacementsModuleInstance;
    delete exportModuleInstance;
    delete correlationFilePage;
    delete rawFilePage;
}

void OpteCAL::resizeEvent(QResizeEvent*)
{
}

void OpteCAL::zoomEvent(float x, float y)
{
    zoomX = x;
    zoomY = y;
    zoomingIn(0,0);
    resizeFunctions();

}
void OpteCAL::zoomingIn(int , int )
{
    QScrollBar* horizontalScroll = ui->scrollArea->horizontalScrollBar();
    horizontalScroll->setValue(zoomX*horizontalScroll->maximum());
    QScrollBar* verticalScroll = ui->scrollArea->verticalScrollBar();
    verticalScroll->setValue(zoomY*verticalScroll->maximum());
}
void OpteCAL::panEvent()
{
    if(ui->currentImgDisplay->middleClickHeld){
        float magF = -1.;
        float scrollX = ((float)ui->currentImgDisplay->x-(float)ui->currentImgDisplay->xStatic)/(float)ui->currentImgDisplay->width();
        float scrollY = ((float)ui->currentImgDisplay->y-(float)ui->currentImgDisplay->yStatic)/(float)ui->currentImgDisplay->height();
        QScrollBar* horizontalScroll = ui->scrollArea->horizontalScrollBar();
        horizontalScroll->setValue((magF*scrollX)*horizontalScroll->maximum()+horizontalScroll->value());
        QScrollBar* verticalScroll = ui->scrollArea->verticalScrollBar();
        verticalScroll->setValue((magF*scrollY)*verticalScroll->maximum()+verticalScroll->value());
        ui->currentImgDisplay->xStatic = ui->currentImgDisplay->x;
        ui->currentImgDisplay->yStatic = ui->currentImgDisplay->y;
    }
}

void OpteCAL::amplifiedMotion(bool val)
{
    ui->amplifiedMotionBox->setVisible(val);
    ui->limitGroupBox->setVisible(!val);
    ui->filtersGroupBox->setVisible(!val);
}


void OpteCAL::resizeFunctions(){
    cam1Display->update();
    if((ui->listFilesWidget->currentRow() >= 0) && (ui->loadFilesToolBox->currentIndex() == correlationPage)){
        originAndAxesLayer->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
        if(ui->listFilesWidget->currentRow()==correlationFiles->getRefImageIdx()){
            roiShapes->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            if(ui->modulesToolBox->currentIndex()==drawRoiPage){
                roiModuleInstance->Mouse_Entered();
                roiShapes->updateWLines();
                measureTool->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
                measureTool->updateWLines();
            }else{
                roiShapes->updateDrawing();
            }
        }
        if(ui->modulesToolBox->currentIndex()==runAnalysisPage){
            runAnalysisInstance->Mouse_Entered();
            seedLayer->setRefImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef(),
                                   cam1Display->getCurrentImg());
            seedLayer->updateDrawing();
        }

        cam1Display->updateResized();
        if((ui->modulesToolBox->currentIndex() == displacementsPage ||
            (ui->modulesToolBox->currentIndex() == exportPage)))
        {
            resizeInProgress->start(100);
            originAndAxesLayer->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            displacementsModuleInstance->Mouse_Entered();
        }

        if (ui->modulesToolBox->currentIndex() == postProcessingPage ){

            resizeInProgress->start(100);
            postProcessingModuleInstance->Mouse_Entered();
        }
        if (ui->modulesToolBox->currentIndex() == drawRoiPage){
            calibrationModuleInstance->Mouse_Entered();

        }
    }else if(ui->listFilesCalWidget->currentRow() >= 0 && (ui->loadFilesToolBox->currentIndex() == calibrationPage)){

    }else if((ui->rawFilesWidget->currentRow() >= 0) && (ui->loadFilesToolBox->currentIndex() == rawPage)){
        cam1Display->uncorrectedDisplayedImage = cam1Display->getCurrentResizedImg()->clone();
        resizeInProgressCorrection->start(100);
    }
}

void OpteCAL::displayColormap()
{
    originAndAxesLayer->setImageResizeCoef(cam1Display->getResizeCoef());
    displacementsModuleInstance->loadSolFromFile(ui->listFilesWidget->currentRow());

    if ((correlationFiles->getFileNames().size() > 0) && (ui->modulesToolBox->currentIndex() == postProcessingPage) ){
        virtualTools->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
        virtualTools->updateDrawing();
    }
    cam1Display->updateResized();
    if (displacementsModuleInstance->getDataIdx() != displacements::getAmplified){
        scaleDisplay->update();
    }
}

void OpteCAL::correctLensDistortion()
{
    qDebug() << "Correcting";
    calibrationModuleInstance->updateDistortionCorrection();
}

void OpteCAL::on_loadFilesToolBox_currentChanged(int index)
{
    ui->modulesToolBox->setVisible(true);
    ui->rawGroupBox->setVisible(false);
    ui->calibrationGroupBox->setVisible(false);
    ui->logoLabel->setVisible(false);
    switch (index) {
    case rawPage:
        ui->scaleLabel->clear();
        ui->modulesToolBox->setVisible(false);
        ui->rawGroupBox->setVisible(true);
        ui->calibrationGroupBox->setVisible(true);
        ui->logoLabel->setVisible(true);
        if(ui->rawFilesWidget->count()>0){

            rawFiles->setCurrentImgIdx(0);
            rawFilePage->on_listFilesWidget_currentRowChanged(0);
        }
        break;
    case calibrationPage:
        ui->scaleLabel->clear();
        ui->modulesToolBox->setCurrentIndex(calibrationModulePage);
        ui->modulesToolBox->setItemEnabled(calibrationModulePage,true);
        ui->modulesToolBox->setItemEnabled(drawRoiPage,false);
        ui->modulesToolBox->setItemEnabled(runAnalysisPage,false);
        ui->modulesToolBox->setItemEnabled(displacementsPage,false);
        ui->modulesToolBox->setItemEnabled(postProcessingPage,false);
        ui->modulesToolBox->setItemEnabled(exportPage,false);
        if(ui->listFilesCalWidget->count()>0){
            calibrationFiles->setCurrentImgIdx(0);
            calibrationFilePage->on_listFilesWidget_currentRowChanged(0);
        }
        break;
    case correlationPage:
        ui->modulesToolBox->setItemEnabled(calibrationModulePage,true);
        ui->modulesToolBox->setItemEnabled(drawRoiPage,true);
        ui->modulesToolBox->setItemEnabled(runAnalysisPage,true);
        ui->modulesToolBox->setItemEnabled(displacementsPage,true);
        ui->modulesToolBox->setItemEnabled(postProcessingPage,true);
        ui->modulesToolBox->setItemEnabled(exportPage,true);
        if(ui->listFilesWidget->count()>0){
            correlationFiles->setCurrentImgIdx(0);
            correlationFilePage->on_listFilesWidget_currentRowChanged(0);
        }
        break;
    default:
        break;
    }
    qApp->processEvents();
    resizeFunctions();

}

void OpteCAL::on_modulesToolBox_currentChanged(int index)
{
    disconnect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()),0,0);
    connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), this, SLOT(panEvent()));
    disconnect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()),0,0);
    disconnect(ui->currentImgDisplay,SIGNAL(Mouse_RightPressed(QPoint)),0,0);
    disconnect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),0,0);
    disconnect(ui->currentImgDisplay,SIGNAL(Mouse_DoubleClick()),0,0);
    disconnect(ui->currentImgDisplay,SIGNAL(Key_Pressed()),0,0);
    disconnect(ui->listFilesWidget,SIGNAL(currentRowChanged(int)),displacementsModuleInstance,SLOT(loadSolFromFile(int)));
    ui->pauseButton->setVisible(false);
    ui->playButton->setVisible(false);
    ui->frameRateLabel->setVisible(false);
    ui->frameRateSpinBox->setVisible(false);
    ui->fpsLabel->setVisible(false);
    correlationFilePage->playAnimTimer->stop();
    runAnalysisInstance->cancelLastSeed();
    roiModuleInstance->cancelDrawing();
        if(ui->deformedRadio->isChecked()){
            originAndAxesLayer->deformedConfiguration = true;
            int currentRow = ui->listFilesWidget->currentRow();
            if (currentRow >= 0)
                cam1Display->setCurrentImg(correlationFiles->getFilePath(currentRow));
        } else {
            originAndAxesLayer->deformedConfiguration = false;
            cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
        }

    switch(index)
    {
    case calibrationModulePage:
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), calibrationModuleInstance, SLOT(Mouse_current_pos()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()), calibrationModuleInstance, SLOT(Mouse_Pressed()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),calibrationModuleInstance,SLOT(Mouse_Entered()));
        connect(ui->currentImgDisplay,SIGNAL(Key_Pressed()),calibrationModuleInstance,SLOT(Key_Pressed()));
        ui->scaleLabel->clear();
        break;
    case drawRoiPage:
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), roiModuleInstance, SLOT(Mouse_current_pos()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()), roiModuleInstance, SLOT(Mouse_Pressed()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_RightPressed(QPoint)),roiModuleInstance,SLOT(mouseRightClick(QPoint)));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),roiModuleInstance,SLOT(Mouse_Entered()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_DoubleClick()),roiModuleInstance,SLOT(Mouse_DoubleClick()));
        connect(ui->currentImgDisplay,SIGNAL(Key_Pressed()),roiModuleInstance,SLOT(Key_Pressed()));
        ui->scaleLabel->clear();
        break;
    case runAnalysisPage:
        qDebug() << "Run analysis page";
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), runAnalysisInstance, SLOT(Mouse_current_pos()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()), runAnalysisInstance, SLOT(Mouse_Pressed()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),runAnalysisInstance,SLOT(Mouse_Entered()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_RightPressed(QPoint)),runAnalysisInstance,SLOT(mouseRightClick(QPoint)));
        connect(ui->currentImgDisplay,SIGNAL(Key_Pressed()),runAnalysisInstance,SLOT(Key_Pressed()));
        ui->scaleLabel->clear();
        break;
    case displacementsPage:

        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), displacementsModuleInstance, SLOT(Mouse_current_pos()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()), displacementsModuleInstance, SLOT(Mouse_Pressed()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),displacementsModuleInstance,SLOT(Mouse_Entered()));
        connect(ui->listFilesWidget,SIGNAL(currentRowChanged(int)),displacementsModuleInstance,SLOT(loadSolFromFile(int)));

        ui->pauseButton->setVisible(true);
        ui->playButton->setVisible(true);
        ui->frameRateLabel->setVisible(true);
        ui->frameRateSpinBox->setVisible(true);
        ui->fpsLabel->setVisible(true);
        break;

    case postProcessingPage:
        ui->sgWidthLabel->setText(QString("Width: NaN"));
        ui->sgHeightLabel->setText(QString("Height: NaN"));
        ui->sgAngleLabel->setText(QString("Angle: NaN"));
        ui->sgOriginLabel->setText(QString("Origin: (NaN,NaN)"));
        ui->e11Label->setText(QString("E11: NaN"));
        ui->e22Label->setText(QString("E22: NaN"));
        ui->e12Label->setText(QString("E12: NaN"));
        ui->extPointsLabel->setText( "Anchor points: (NaN,NaN)\n(NaN,NaN)");
        ui->extLengthLabel->setText("Length: NaN");
        ui->elongationLabel->setText("Elongation: NaN");
        ui->elongationXLabel->setText("X-Projection: NaN");
        ui->elongationYLabel->setText("Y-Projection: NaN");
        cam1Display->setCurrentImg(correlationFiles->getRefImagePath());
        virtualTools->updateSolutionMap(originAndAxesLayer, ui->listFilesWidget->currentRow(),correlationFiles);
        originAndAxesLayer->deformedConfiguration = false;
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pos()), postProcessingModuleInstance, SLOT(Mouse_current_pos()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Pressed()), postProcessingModuleInstance, SLOT(Mouse_Pressed()));
        connect(ui->currentImgDisplay,SIGNAL(Mouse_Entered()),postProcessingModuleInstance,SLOT(Mouse_Entered()));
        connect(ui->currentImgDisplay,SIGNAL(Key_Pressed()),postProcessingModuleInstance,SLOT(Key_Pressed()));

    case exportPage:
        break;
    }
    //    if(!correlationFilePage->refLoaded && !originAndAxesLayer->deformedConfiguration
    //            && (index>=displacementsPage)){

    //        correlationFilePage->modulesToolBoxIndex = index;
    //        if((correlationFiles->getFileNames().size() !=0) &&(correlationFiles->getCurrentImgIdx() >=0)){
    //            correlationFilePage->on_listFilesWidget_currentRowChanged(correlationFiles->getCurrentImgIdx());
    //        }
    //    }
    resizeFunctions();
}


void OpteCAL::ShowContextMenu(const QPoint) // this is a slot
{
    
}

void OpteCAL::on_cartesianPolarComboBox_currentIndexChanged(int index)
{
    qDebug() << "CartPolar = " << index;
    QStringList list;
    if(index == 0){
        list= QStringList()<<"U"<<"V"<< "Rotation"<<"Exx"<<"Eyy"<<"Exy"
                          << "Principal Strain 1" << "Principal Strain 2"
                          << "Principal Dir. 1" << "Principal Dir. 2"
                          << "Von-Mises Strain" << "Tresca Strain"
                          <<"Cor. Coeff."<< "X" << "Y";
    }else{
        list= QStringList()<<"Ur"<<"Ut"<< "Rotaion" <<"Err"<<"Ett"<<"Ert"
                          << "Principal Strain 1" << "Principal Strain 2"
                          << "Principal Dir. 1" << "Principal Dir. 2"
                          << "Von-Mises Strain" << "Tresca Strain"
                          <<"Cor. Coeff."<< "R" << "Theta";
    }
    for (int i=0; i<list.size(); ++i){
        ui->dispComboBox->setItemText(i,list[i]);
    }
    ui->uCheck->setText(list[0]);
    ui->vCheck->setText(list[1]);
    ui->exxCheck->setText(list[3]);
    ui->eyyCheck->setText(list[4]);
    ui->exyCheck->setText(list[5]);
    ui->xCheck->setText(list[13]);
    ui->yCheck->setText(list[14]);
}



void OpteCAL::on_listFilesWidget_clicked(const QModelIndex)
{
    emit listOfMultipleFiles(ui->listFilesWidget->selectionModel()->selectedIndexes());
}

void OpteCAL::on_listFilesCalWidget_clicked(const QModelIndex)
{
    emit listOfMultipleFiles(ui->listFilesCalWidget->selectionModel()->selectedIndexes());
}

void OpteCAL::on_rawFilesWidget_clicked(const QModelIndex)
{
    emit listOfMultipleFiles(ui->rawFilesWidget->selectionModel()->selectedIndexes());
}


void OpteCAL::on_frameRateSpinBox_valueChanged(double arg1)
{
    static int sign = true;
    if(arg1 <= 1.){
        ui->frameRateSpinBox->setSingleStep(.1);
        ui->frameRateSpinBox->setDecimals(1);
    }else{
        ui->frameRateSpinBox->setSingleStep(1.);

    }
    if(arg1 > 1.){
        ui->frameRateSpinBox->setDecimals(0);
        ui->frameRateSpinBox->setValue(round(arg1));
        sign = true;
    }
    if(!sign && (arg1 == 1.))
        ui->frameRateSpinBox->setSingleStep(1.);
    if (arg1 < 1.)
        sign = false;

    correlationFilePage->fps = arg1;
}


void OpteCAL::closeEvent(QCloseEvent *event)
{
    if (currentSettingsSaved()){
        event->accept();
    }
    else
        event->ignore();
}

void OpteCAL::on_actionLoad_calibration_images_triggered()
{
    ui->loadFilesToolBox->setCurrentIndex(calibrationPage);
    ui->loadImageCal->click();
}

void OpteCAL::on_actionLoad_RAW_files_triggered()
{
    ui->loadFilesToolBox->setCurrentIndex(rawPage);
    ui->loadRawImage->click();
}

void OpteCAL::on_actionLoad_experiment_images_triggered()
{
    ui->loadFilesToolBox->setCurrentIndex(correlationPage);
    ui->loadImage->click();
}

void OpteCAL::updateCorrelationFilesFolder(QString newCorrelFolder)
{
    correlationFiles->updateImageFolder(newCorrelFolder);
}

void OpteCAL::on_actionNew_Project_triggered()
{
    if(!currentSettingsSaved()) return;

    rawFiles->clear();
    calibrationFiles->clear();
    correlationFiles->clear();
    roiShapes->clear();
    seedLayer->clear();
    settingsFilePath.clear();
    ui->currentImgDisplay->clear();
    ui->scaleLabel->clear();
    cam1Display->clear();
    scaleDisplay->clear();
    qDebug() << "Cleared all settings";

}

bool OpteCAL::on_actionSave_Project_as_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QString(),
                                                    tr("OpteCAL settings files (*.opte)"));
    if (fileName.length() != 0){
        settingsFilePath = fileName.toStdString();
        rootFolder =QFileInfo(fileName).absoluteDir();
        cv::FileStorage fs(settingsFilePath, cv::FileStorage::WRITE);
        // Update the rootFolder to get images filePath relative to the settings file
        correlationFiles->updateRootFolder(rootFolder);
        calibrationFiles->updateRootFolder(rootFolder);
        fs << "correlationFiles" << *correlationFiles;
        fs << "calibrationFiles" << *calibrationFiles;
        fs << "rawFiles" << *rawFiles;
        fs << "cam1Calibration" << *cam1Calibration;
        fs << "roiShapes" << *roiShapes;
        fs << "seedLayer" << *seedLayer;
        fs << "originAndAxesLayer" << *originAndAxesLayer;
        fs << "virtualMeasurementTools" << *virtualTools;
        fs.release();
        return true;
    }
    return false;
}
bool OpteCAL::on_actionSave_Project_triggered()
{
    if (!settingsFilePath.empty()){
        cv::FileStorage fs(settingsFilePath, cv::FileStorage::WRITE);
        // Update the rootFolder to get images filePath relative to the settings file
        correlationFiles->updateRootFolder(rootFolder);
        calibrationFiles->updateRootFolder(rootFolder);
        fs << "correlationFiles" << *correlationFiles;
        fs << "calibrationFiles" << *calibrationFiles;
        fs << "rawFiles" << *rawFiles;
        fs << "cam1Calibration" << *cam1Calibration;
        fs << "roiShapes" << *roiShapes;
        fs << "seedLayer" << *seedLayer;
        fs << "originAndAxesLayer" << *originAndAxesLayer;
        fs << "virtualMeasurementTools" << *virtualTools;
        fs.release();
        return true;
    } else {
        return on_actionSave_Project_as_triggered();
    }
}
void OpteCAL::on_actionLoad_Project_triggered()
{
    if(!currentSettingsSaved()) return;
    loadImages->setFileMode(QFileDialog::ExistingFile);
    loadImages->setNameFilter(tr("OpteCAL settings files (*.opte)"));
    loadImages->setViewMode(QFileDialog::List);
    if (loadImages->exec()){
        QStringList settingsFile(loadImages->selectedFiles());
        settingsFilePath = settingsFile.back().toStdString();
        rootFolder = QFileInfo(settingsFile.back()).absoluteDir();
        loadSettingsFile();
    }
}

void OpteCAL::loadSettingsFile()
{
    cv::FileStorage fs;
    fs.open(settingsFilePath, cv::FileStorage::READ);
    qDebug() << "Root path:" << rootFolder;

    // Update the rootFolder to get images settingsFilePath relative to the settings file
    rawFiles->updateRootFolder(rootFolder);
    correlationFiles->updateRootFolder(rootFolder);
    correlationFiles->clear();
    rawFiles->clear();
    roiShapes->clear();
    seedLayer->clear();
    virtualTools->clear();
    fs["correlationFiles"] >> *correlationFiles;
    fs["calibrationFiles"] >> *calibrationFiles;
    fs["rawFiles"] >> *rawFiles;
    fs["cam1Calibration"] >> *cam1Calibration;
    fs["roiShapes"] >> *roiShapes;
    fs["seedLayer"] >> *seedLayer;
    fs["originAndAxesLayer"] >> *originAndAxesLayer;
    fs["virtualMeasurementTools"] >> *virtualTools;


    ui->sortFilesComboBox->setCurrentIndex(correlationFiles->sortFlag);
    ui->sortFilesCalComboBox->setCurrentIndex(calibrationFiles->sortFlag);
    ui->sortRawFilesComboBox->setCurrentIndex(rawFiles->sortFlag);
    correlationFilePage->updateListFiles();
    calibrationFilePage->updateListFiles();
    rawFilePage->updateListFiles();
    ui->flipXYCheckBox->setChecked(originAndAxesLayer->flipXY);
    ui->showAxesCheckBox->setChecked(originAndAxesLayer->axesOn);
    ui->cartesianPolarComboBox->setCurrentIndex(originAndAxesLayer->polarCartFlag);
    ui->listFilesWidget->setCurrentRow(0);
    ui->unitLineEdit->setText(QString::number(cam1Calibration->unitLine));
    ui->pixelLineEdit->setText(QString::number(cam1Calibration->pxLine));
    ui->unitComboBox->setCurrentIndex(cam1Calibration->unitFlag);
    ui->guiResponsiveCheckBox->setChecked(seedLayer->useAllCPU);
    ui->colormapSlider->setValue((int)(originAndAxesLayer->colormapCoef*100.));
    ui->deformedRadio->setChecked(originAndAxesLayer->deformedConfiguration);
    ui->referenceRadio->setChecked(!originAndAxesLayer->deformedConfiguration);
    ui->greenAlmansiRadio->setChecked(originAndAxesLayer->spatialCoordinates);
    ui->greenLagrangeRadio->setChecked(!originAndAxesLayer->spatialCoordinates);
    ui->subsetSizeSlider->setValue(seedLayer->subsetSize);
    ui->subsetSpacingSlider->setValue(seedLayer->subsetSpacing);
    switch(seedLayer->getInterpDegree()){
    case 3:
        ui->splineComboBox->setCurrentIndex(0);
        break;
    case 5:
        ui->splineComboBox->setCurrentIndex(1);
        break;
    case 7:
        ui->splineComboBox->setCurrentIndex(2);
        break;
    case 9:
        ui->splineComboBox->setCurrentIndex(3);
        break;
    default:
        ui->splineComboBox->setCurrentIndex(1);
        break;
    }
    ui->searchRegionSpinBox->blockSignals(true);
    ui->searchRegionSpinBox->setValue(seedLayer->searchBoxWidth);
    ui->searchRegionSpinBox->blockSignals(false);
    ui->highStrainCheckBox->setChecked(seedLayer->highStrainEnabled);
    ui->corrRejectionLineEdit->setText(QString::number(100*seedLayer->corrRejection));

    ui->unitsDisplayComboBox->blockSignals(true);
    ui->unitsDisplayComboBox->setCurrentIndex(originAndAxesLayer->unitDisplayFlag);
    ui->unitsDisplayComboBox->blockSignals(false);
    roiModuleInstance->displayScale();
    ui->virtualStrainGaugeList->clear();
    if(virtualTools->strainGaugeList.size()!=0){
        for(std::vector<virtualMeasurementTools::strainGauge>::iterator sgIter = virtualTools->strainGaugeList.begin();
            sgIter!=virtualTools->strainGaugeList.end(); ++sgIter){
            ui->virtualStrainGaugeList->addItem(sgIter->name);
        }
    }
    ui->extensometerList->clear();
    if(virtualTools->extensometerList.size()!=0){
        for(std::vector<virtualMeasurementTools::extensometer>::iterator extIter = virtualTools->extensometerList.begin();
            extIter!=virtualTools->extensometerList.end(); ++extIter){
            ui->extensometerList->addItem(extIter->name);
        }
    }
    resizeFunctions();
}

bool OpteCAL::equalFiles(ifstream& in1, ifstream& in2) // From jww on stackoverflow.com
{
    ifstream::pos_type size1, size2;

    size1 = in1.seekg(0, ifstream::end).tellg();
    in1.seekg(0, ifstream::beg);

    size2 = in2.seekg(0, ifstream::end).tellg();
    in2.seekg(0, ifstream::beg);

    if(size1 != size2)
        return false;

    static const size_t BLOCKSIZE = 4096;
    size_t remaining = size1;

    while(remaining)
    {
        char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
        size_t size = min(BLOCKSIZE, remaining);

        in1.read(buffer1, size);
        in2.read(buffer2, size);

        if(0 != memcmp(buffer1, buffer2, size))
            return false;

        remaining -= size;
    }

    return true;
}


bool OpteCAL::currentSettingsSaved(){
    // Check if the current settings are saved
    if (!settingsFilePath.empty()){
        // Save a temporary settings file
        std::string tempSettings = rootFolder.absolutePath().toStdString() + "/autoSave.opte";
        cv::FileStorage fs(tempSettings, cv::FileStorage::WRITE);
        // Update the rootFolder to get images filePath relative to the settings file
        correlationFiles->updateRootFolder(rootFolder);
        calibrationFiles->updateRootFolder(rootFolder);
        fs << "correlationFiles" << *correlationFiles;
        fs << "calibrationFiles" << *calibrationFiles;
        fs << "rawFiles" << *rawFiles;
        fs << "cam1Calibration" << *cam1Calibration;
        fs << "roiShapes" << *roiShapes;
        fs << "seedLayer" << *seedLayer;
        fs << "originAndAxesLayer" << *originAndAxesLayer;
        fs << "virtualMeasurementTools" << *virtualTools;
        fs.release();

        // Compare the temporary settings file with the current saved file
        std::ifstream in1(tempSettings, ios::binary);
        std::ifstream in2(settingsFilePath, ios::binary);
        if(!equalFiles(in1,in2)){
            QMessageBox saveFileBox;
            saveFileBox.setText("The document has been modified.");
            saveFileBox.setInformativeText("Do you want to save your changes?");
            saveFileBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            saveFileBox.setDefaultButton(QMessageBox::Save);
            int ret = saveFileBox.exec();
            switch (ret) {
            case QMessageBox::Save:
                in1.close();
                in2.close();
                return on_actionSave_Project_triggered();
                break;
            case QMessageBox::Discard:
                in1.close();
                in2.close();
                return true;
                break;
            case QMessageBox::Cancel:
                in1.close();
                in2.close();
                return false;
                break;
            }
        }
    }
    return true;



}


