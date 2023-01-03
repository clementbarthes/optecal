#include "runanalysis.h"
#include "staticreadwritefunctions.h"

runAnalysisModule::runAnalysisModule(QLabelWMouse *imgDisplay, subsetsMap* subsetList,
                                     autoResize *cam1Display, drawSeedPoint *seedLayer,
                                     fileList* cam1Files, drawShape* roiShapes, displacements *dispFbk,
                                     QLineEdit *subsetSizeText, QSlider *subsetSizeSlider,
                                     QLineEdit *subsetSpacingText, QSlider *subsetSpacingSlider,
                                     QPushButton* setSeedButton, QLineEdit*corrRejectionText,
                                     QListWidget *correlationWidgetList)
{
    this->imgDisplay = imgDisplay;
    this->subsetList = subsetList;
    this->cam1Display = cam1Display;
    this->seedLayer = seedLayer;
    this->roiShapes = roiShapes;
    this->cam1Files = cam1Files;
    this->subsetSizeText = subsetSizeText;
    this->subsetSizeSlider = subsetSizeSlider;
    this->subsetSpacingText = subsetSpacingText;
    this->subsetSpacingSlider = subsetSpacingSlider;
    this->setSeedButton = setSeedButton;
    this->corrRejectionText = corrRejectionText;
    this->correlationWidgetList = correlationWidgetList;
    this->dispFbk = dispFbk;
    analysisCanceled = false;
    seedLayer->useAllCPU = false;
    seedLayer->setInterpDegree(5);
    seedLayer->corrRejection = corrRejectionText->text().toDouble()*.01;
    totalSubsetsSolved = 0;
    updatedReferenceIdx = 0;
    referenceUpdated = false;
    pd = new QProgressDialog("Solving...", "Cancel", 0, 100);
    connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));
    pd->close();
}

void runAnalysisModule::on_subsetSizeSlider_valueChanged(int value)
{
    // Always adjust input to make it an odd number
    int oddVvalue = 2*(value/2)+1;
    if(oddVvalue != value)
        subsetSizeSlider->setValue(oddVvalue);

    subsetSizeText->setText(QString("%1").arg(oddVvalue));

    // Always set the maximum spacing as half the subset size
    subsetSpacingSlider->setMaximum(oddVvalue/2);
    seedLayer->subsetSize = oddVvalue;
}

void runAnalysisModule::on_subsetSizeText_editingFinished()
{
    QString arg1 = subsetSizeText->text();
    if(arg1.toInt() < subsetSizeSlider->minimum()){
        //If too low, set to minimum
        subsetSizeText->setText(QString("%1").arg(subsetSizeSlider->minimum()));
    }
    else if(arg1.toInt() > subsetSizeSlider->maximum()){
        //If too high, set to maximum
        subsetSizeText->setText(QString("%1").arg(subsetSizeSlider->maximum()));

    }
    subsetSizeSlider->setValue(arg1.toInt());
}

void runAnalysisModule::on_subsetSpacingText_editingFinished()
{
    QString arg1 = subsetSpacingText->text();
    if(arg1.toInt() < subsetSpacingSlider->minimum()){
        //If too low, set to minimum
        subsetSpacingText->setText(QString("%1").arg(subsetSpacingSlider->minimum()));
    }
    else if(arg1.toInt() > subsetSpacingSlider->maximum()){
        //If too high, set to maximum
        subsetSpacingText->setText(QString("%1").arg(subsetSpacingSlider->maximum()));

    }
    subsetSpacingSlider->setValue(arg1.toInt());
}

void runAnalysisModule::on_subsetSpacingSlider_valueChanged(int value)
{
    subsetSpacingText->setText(QString("%1").arg(value));
    // Update seed location so that they remain on the subset step grid
    seedLayer->subsetSpacing = value;
}

void runAnalysisModule::on_setSeedButton_clicked()
{
    if(cam1Display->getCurrentResizedImg()->empty()){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No image selected");
        noFileErrorMessage.exec();
        return;
    }
    setSeedButton->setDown(true);
    seedLayer->setSeedExist(true);
    seedLayer->setSeedPoint();
    imageResizeCoef = cam1Display->getResizeCoef();
    seedLayer->setRefImage(cam1Display->getCurrentResizedImg(),imageResizeCoef,
                           cam1Display->getCurrentImg());
    seedLayer->updateDrawing();
    imgDisplay->grabKeyboard();
    imgDisplay->setCursor(Qt::CrossCursor);
    seedLayer->drawingSeedPoint = true;

}

void runAnalysisModule::Mouse_current_pos()
{
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    if(seedLayer->drawingSeedPoint){
        seedLayer->updateSeedPoint(&currentPoint);
        // Check if seed is within ROI
//        if(seedLayer->seedInRoi(roiShapes->getROIMask())){
//            seedLayer->setSeedExist(true);
//        }else {
//            seedLayer->setSeedExist(false);
//        }
        seedLayer->updateDrawing();
        cam1Display->updateResized();
    } else {
        if (imgDisplay->leftClickHeld){
            seedLayer->updateCurrentSeedPoint(&currentPoint);
            seedLayer->updateDrawing();
            cam1Display->updateResized();
            return;
        }
        if(seedLayer->isMouseNearPoint(&currentPoint)){
            imgDisplay->setCursor(Qt::OpenHandCursor);
        } else {
            imgDisplay->setCursor(Qt::ArrowCursor);
        }
    }
}

void runAnalysisModule::Mouse_Pressed()
{
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);

    if(seedLayer->seedInRoi(roiShapes->getROIMask())){
        runAnalysisModule::quitDrawing();
    }
    if (seedLayer->isMouseNearPoint(&currentPoint)){
        qDebug() << "Grabbed Point";
        imgDisplay->setCursor(Qt::ClosedHandCursor);
        seedLayer->updateCurrentSeedPoint(&currentPoint);
        seedLayer->updateDrawing();
        cam1Display->updateResized();
    }
}

void runAnalysisModule::Mouse_Entered(){
    imageResizeCoef = cam1Display->getResizeCoef();
    cam1Display->updateResized();
}

void runAnalysisModule::mouseRightClick(QPoint pos)
{
    QPoint globalPos = imgDisplay->mapToGlobal(pos);
    cv::Point2i currentPoint((imgDisplay->x)*imageResizeCoef,
                             (imgDisplay->y)*imageResizeCoef);
    if (seedLayer->isMouseNearPoint(&currentPoint)){
        QMenu fileManageMenu;
        fileManageMenu.addAction("Delete seed")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem)
        {
            qDebug() << "Delete seed";
            seedLayer->deleteCurrentSeedPoint();
            //seedLayer->updateDrawing();
            cam1Display->updateResized();
        }
    }
}

void runAnalysisModule::allCPUCheck(bool val)
{
    seedLayer->useAllCPU = val;
}

void runAnalysisModule::stackSolutions()
{
//    currentSubsetList[].warp = (*subsetsToBeSolvedIter)->getWarp();
//               currentSubsetList[].corrCoef = (*subsetsToBeSolvedIter)->getCorrCoef();
//               currentSubsetList[].converged = (*subsetsToBeSolvedIter)->getConvergence();
//    qDebug() << "Stacked";
}

void runAnalysisModule::quitDrawing()
{
    seedLayer->drawingSeedPoint = false;
    setSeedButton->setDown(false);
    imgDisplay->releaseKeyboard();
    imgDisplay->setCursor(Qt::ArrowCursor);
}

void runAnalysisModule::Key_Pressed()
{
    if((seedLayer->drawingSeedPoint==true) && (imgDisplay->key == Qt::Key_Escape))
    {
        cancelLastSeed();
        cam1Display->updateResized();
    }
}

void runAnalysisModule::cancelLastSeed(){
    if(seedLayer->drawingSeedPoint){
        imgDisplay->releaseKeyboard();
        seedLayer->deleteLastSeedPoint();
        seedLayer->drawingSeedPoint=false;
        setSeedButton->setDown(false);
        imgDisplay->releaseKeyboard();
        imgDisplay->setCursor(Qt::ArrowCursor);
    }
}

int runAnalysisModule::singleFrameAnalysis(){

    if(!cam1Files->getNoFiles()){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No image file loaded");
        noFileErrorMessage.exec();
        qDebug() << "Break0";
        return analysisCanceledFlag;
    }
    if(!roiShapes->isRoiDefined()){
        QMessageBox noRoiErrorMessage;
        noRoiErrorMessage.setText(
                    "No ROI defined");
        noRoiErrorMessage.exec();
        qDebug() << "Break1";
        return analysisCanceledFlag;
    }
    if(!seedLayer->getSeedExist()){
        QMessageBox noSeedErrorMessage;
        noSeedErrorMessage.setText(
                    "Seed mut be set before running the analysis");
        noSeedErrorMessage.exec();
        qDebug() << "Break2";
        return analysisCanceledFlag;
    }
    if(cam1Files->getRefImageIdx()==cam1Files->getCurrentImgIdx()){
        QMessageBox referenceImgError;
        referenceImgError.setText(
                    "Analysis cannot be performed on the reference image");
        referenceImgError.exec();
        qDebug() << "Break3";
        return analysisCanceledFlag;
    }

    dispFbk = new displacements();
    pd->setVisible(true);
    pd->setValue(0);
    //    pd->update();
    qApp->processEvents();

    nlOptimizer::subsetProperties seedSubset;
    std::vector<nlOptimizer::subsetProperties> poorlyConvergedSubsets;
    std::vector<nlOptimizer::subsetProperties> nonConvergedSubsets;
    cv::Mat imageTestRef = cam1Files->getRefImage();

    // Obtain the ROI of the full res image
    cv::Mat erodedRoi = cv::Mat::zeros(imageTestRef.rows,imageTestRef.cols,CV_8UC3);
    drawShape *erodedRoiShapes = new drawShape(*roiShapes);
    erodedRoiShapes->setImage(&erodedRoi,1.);
    // Create an eroded ROI to layout the subset centers
    // such that the subsets remain within the bounds of the ROI
    int subsetSize = subsetSizeSlider->value();
    erodedRoi = *erodedRoiShapes->getROIMask();
    cv::Mat morphOperator = cv::Mat::ones(subsetSize/2,subsetSize/2,CV_8U);
    cv::erode(erodedRoi,erodedRoi,morphOperator,cv::Point2i(-1,-1),1);
    //Resize the ROI to have one pixel per subset
    cv::resize(erodedRoi,erodedRoi,cv::Size(erodedRoi.cols/subsetSpacingSlider->value(),erodedRoi.rows/subsetSpacingSlider->value()));
    subsetList->setRoiMask(&erodedRoi);
    subsetList->setSubsetSize(subsetSizeSlider->value());
    subsetList->setSubsetSpacing(subsetSpacingSlider->value());

    // Compute the number of subsets
    long long int totalSubsets = cv::sum(erodedRoi)[0];
    totalSubsets /=255;
    pd->setMaximum(totalSubsets);
    int currentImage = cam1Files->getCurrentImgIdx();
    cv::Mat imageTestCurrent = cam1Files->getImage(currentImage);
    std::vector<cv::Point2i> seedVector = seedLayer->getSeed();
    std::vector<cv::Point2i>::iterator seedIter = seedVector.begin();

    displacements* updatedRefSol = new displacements();

    if(referenceUpdated){
        cam1Files->getImage(updatedReferenceIdx).copyTo(imageTestRef);
        // Open solution file of the updated reference file
        if(!displacements::openSolutionFile(updatedReferenceIdx, cam1Files , updatedRefSol)){
            QMessageBox noUpdatedRefImage;
            noUpdatedRefImage.setText(
                        "High strain analysis enabled. \nIn order for Optecal to find the solution of the current image, you need to compute the solution of the previous images with the same analysis parameters.");
            noUpdatedRefImage.exec();
            pd->close();
            return analysisCanceledFlag;
        }
        if(updatedRefSol->subsetSpacing != subsetList->getSubsetSpacing()){
            QMessageBox subsetSizeDifferent;
            subsetSizeDifferent.setText(
                        QString("High strain analysis enabled. \nPrevious solution was computed with a subset spacing of %1 pixels. You can recompute the previous solutions with the current analysis settings or use a subset spacing of %1 pixels.").arg(updatedRefSol->subsetSpacing));
            subsetSizeDifferent.exec();
            return analysisCanceledFlag;
        }
    }

    for(; seedIter != seedVector.end();++seedIter){
        erodedRoi.at<cv::Vec3b>(
                    cv::Point2i((*seedIter).x/subsetList->getSubsetSpacing(),
                                (*seedIter).y/subsetList->getSubsetSpacing()))[0] = 0;
        seedSubset.center = *seedIter;
        if(referenceUpdated) {
            int col = seedSubset.center.x/subsetList->getSubsetSpacing();
            int row = seedSubset.center.y/subsetList->getSubsetSpacing();

            seedSubset.prevWarp = updatedRefSol->getWarp(row,col);
        } else{
            seedSubset.prevWarp = cv::Matx23d::eye();
        }


        seedSubset.warp = computeInitialGuess(&imageTestCurrent,
                                              seedSubset.center);

        //        +cv::Point2i(seedSubset.prevWarp(0,2),seedSubset.prevWarp(1,2))
        seedSubset.converged = nlOptimizer::CONVERGED;
        currentSubsetList.push_back(seedSubset);
    }

    interpCoef coefBuilder;
    coefBuilder.SamplesToCoefficients(&imageTestRef,seedLayer->getInterpDegree());
    coefBuilder.SamplesToCoefficients(&imageTestCurrent,seedLayer->getInterpDegree());

    QThreadPool *threadPool = QThreadPool::globalInstance();

    cv::Mat imageTestRefThread = imageTestRef.clone();
    cv::Mat imageTestCurrentThread = imageTestCurrent.clone();
    int idealNThreads = QThread::idealThreadCount();
    if(seedLayer->useAllCPU)
        threadPool->setMaxThreadCount(idealNThreads);
    else{
        int nThreads = idealNThreads >= 2 ? idealNThreads-1 : idealNThreads;
        threadPool->setMaxThreadCount(nThreads);
    }

    int nSubsets = (int)currentSubsetList.size();
    std::vector<nlOptimizer*> subsetsToBeSolved;
    int nMax = 25;
    long long int totalSubsetsSolved = 0;
    //qDebug() << "First subset batch:" << nSubsets;
    while(nSubsets > 0){
        if(analysisCanceled){
            return analysisCanceledFlag;
        }
        qDebug() << "Start stacking subsets";
        for(int subsetIter = 0; subsetIter < nSubsets; ++subsetIter){

            // If the reference image was updated, then prevWarp is updated
            if(referenceUpdated) {
                int col = currentSubsetList[subsetIter].center.x/subsetList->getSubsetSpacing();
                int row = currentSubsetList[subsetIter].center.y/subsetList->getSubsetSpacing();
                currentSubsetList[subsetIter].prevWarp =  updatedRefSol->getWarp(row,col);
                currentSubsetList[subsetIter].prevCorrCoef = 0.;

            } else{
                currentSubsetList[subsetIter].prevWarp = cv::Matx23d::eye();
                currentSubsetList[subsetIter].prevCorrCoef = 0.;
            }
            // Create an object for each subset
            nlOptimizer* currentOptimizer = new nlOptimizer(currentSubsetList[subsetIter],
                                                            subsetSize, seedLayer->getInterpDegree(), 1e-4L, nMax,
                                                            seedLayer->corrRejection,imageTestRefThread,imageTestCurrentThread);
            currentOptimizer->setAutoDelete(false);
            subsetsToBeSolved.push_back(currentOptimizer);
        }
        qDebug() << "Done stacking subsets";
        for( int subsetIter = 0; subsetIter < nSubsets; ++subsetIter ){
            threadPool->start(subsetsToBeSolved[subsetIter]);
            // Wait for all the subsets of the current batch to be solved
        }
        qDebug() << "All threads launched";

        threadPool->waitForDone();
        //qDebug() << "Done Solving";

        // Gather the solution
        std::vector<nlOptimizer::subsetProperties>::iterator currentSubsetListIter =
                currentSubsetList.begin();
        std::vector<nlOptimizer*>::iterator subsetsToBeSolvedIter =
                subsetsToBeSolved.begin();
        for(; currentSubsetListIter != currentSubsetList.end();currentSubsetListIter++, subsetsToBeSolvedIter++){
            currentSubsetListIter->warp = (*subsetsToBeSolvedIter)->getWarp();
            currentSubsetListIter->corrCoef = (*subsetsToBeSolvedIter)->getCorrCoef();
            currentSubsetListIter->converged = (*subsetsToBeSolvedIter)->getConvergence();
            delete (*subsetsToBeSolvedIter);
        }
        threadPool->clear();
        subsetsToBeSolved.clear();
        // Assign new batch.
        subsetList->allocateNextBatch(currentSubsetList);
        nSubsets = (int)currentSubsetList.size();

        totalSubsetsSolved += nSubsets;
        pd->setValue(totalSubsetsSolved);
        qApp->processEvents();
        /// For debugging only
//        for(std::vector<nlOptimizer::subsetProperties>::iterator it = currentSubsetList.begin() ; it != currentSubsetList.end(); ++it){
//            cv::circle(*cam1Display->getCurrentResizedImg(),it->center*(1./imageResizeCoef),3,CV_RGB(0,0,255));
//        }

    }




//    /// Look for unresolved subsets
//    int i = 0;
//    int j = 0;
//    for (cv::Mat_<cv::Vec3b>::iterator erodedRoiIter = erodedRoi.begin<cv::Vec3b>();
//         erodedRoiIter <erodedRoi.end<cv::Vec3b>(); erodedRoiIter++ ){
//        if((*erodedRoiIter)[0]){
//            ///For debugging purposes only
////            cv::circle(*cam1Display->getCurrentResizedImg(),
////                       cv::Point2i(i*subsetSpacingSlider->value(),j*subsetSpacingSlider->value())*(1./imageResizeCoef),4,CV_RGB(0,255,0));
////            cam1Display->updateResized();
////            qApp->processEvents();
//            nlOptimizer::subsetProperties pushSubset;
//            pushSubset.center = cv::Point2i(i*subsetSpacingSlider->value(),j*subsetSpacingSlider->value());
//            pushSubset.prevWarp = cv::Matx23d::eye();
//            pushSubset.corrCoef = 1.;
//            pushSubset.converged = nlOptimizer::NO_CONVERGENCE;
//            nonConvergedSubsets.push_back(pushSubset);
//            //qDebug() << "X: " << i*subsetSpacingSlider->value()<< "Y: " << j*subsetSpacingSlider->value();

//        }
//        if(++i == erodedRoi.cols){
//            j++;
//            i=0;
//        }
//    }


    pd->close();

    qDebug() << "Analysis done";
    cam1Files->setIsSolved(currentImage,true);
    dispFbk->subsetSpacing = subsetList->getSubsetSpacing();
    dispFbk->subsetSize = subsetList->getSubsetSize();
    dispFbk->addSolution(subsetList->getSubsetSpacing(), &imageTestCurrent ,subsetList->subsetList);
    delete updatedRefSol;
    subsetList->subsetList.clear();
    qDebug() << "Saving solution into an .optsln file";
    QFileInfo imgFilePath(cam1Files->getCurrentImgPath());
    std::string solFilePath = imgFilePath.absolutePath().toStdString() + "/"
            + imgFilePath.baseName().toStdString() + ".optsln";
    cv::FileStorage fs(solFilePath, cv::FileStorage::WRITE);
    fs << "Reference_image" << cam1Files->getRefImagePath().toStdString();
    fs << "Solution" << *dispFbk;
    fs.release();
    delete dispFbk;

    //qDebug() << "Number of poorly converged subsets: " << poorlyConvergedSubsets.size();
    //qDebug() << "New solution file:" << solFilePath.c_str();
    poorlyConvergedSubsets.clear();
    currentSubsetList.clear();
    nonConvergedSubsets.clear();
    imageTestRef.release();
    erodedRoi.release();
    delete erodedRoiShapes;
    morphOperator.release();
    imageTestCurrent.release();
    seedVector.clear();
    imageTestRefThread.release();
    imageTestCurrentThread.release();
    return analysisSuccess;

}

void runAnalysisModule::multipleFrameSelection(QModelIndexList val)
{
    selectedFrames.clear();
    foreach(QModelIndex index, val)
    {
        qDebug() << index;
        selectedFrames.push_back(index.row());

    }
    for (int i = 0 ; i < selectedFrames.size(); ++i){
        if(selectedFrames[i] == cam1Files->getRefImageIdx()){
            selectedFrames.erase(selectedFrames.begin()+ i - 1);
        }
    }
    std::sort( selectedFrames.begin(), selectedFrames.end() );
    selectedFrames.erase( std::unique( selectedFrames.begin(), selectedFrames.end() ), selectedFrames.end() );
}

void runAnalysisModule::multipleFrame(){
    selectedFrames.clear();
    QList<QListWidgetItem*> widgetList = correlationWidgetList->selectedItems();
    qDebug() << "widget list size: " << widgetList.size();
    for(int listIter = 0 ; listIter < correlationWidgetList->count(); ++listIter){
        for (int k = 0; k< widgetList.size(); ++k){
            if(correlationWidgetList->item(listIter)->text() == widgetList[k]->text()){
                selectedFrames.push_back(listIter);
            }
        }
    }



    if(selectedFrames.size() == 0){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No file selected");
        noFileErrorMessage.exec();
        return;
    }
    if(!roiShapes->isRoiDefined()){
        QMessageBox noRoiErrorMessage;
        noRoiErrorMessage.setText(
                    "No ROI defined");
        noRoiErrorMessage.exec();
        return;
    }
    if(!seedLayer->getSeedExist()){
        QMessageBox noSeedErrorMessage;
        noSeedErrorMessage.setText(
                    "Seed mut be set before running the analysis");
        noSeedErrorMessage.exec();
        return;
    }



    referenceUpdated = false;
    int counter = 0;
    for (int j = 0; j < selectedFrames.size(); ++j){
        if(!cam1Files->isRefImage(selectedFrames[j])){
            analysisCanceled = false;
            qDebug() << "Frame: " << selectedFrames[j];
            ++counter;
            QString imageNumberSolved = QString ("Processing image %1/%2").arg (QString::number (counter),QString::number ( selectedFrames.size()));
            cam1Files->setCurrentImgIdx(selectedFrames[j]);
            pd->setLabelText(imageNumberSolved);


            if(seedLayer->highStrainEnabled &&
                    ((cam1Files->getCurrentImgIdx()-1)!= cam1Files->getRefImageIdx())
                    && (cam1Files->getCurrentImgIdx()>0)){
                referenceUpdated = true;
                updatedReferenceIdx = cam1Files->getCurrentImgIdx()-1;
                qDebug() << "Updated reference" << updatedReferenceIdx;
            }
            int frameAnalysisFlag = singleFrameAnalysis();
            if(!frameAnalysisFlag){
                qDebug() << "Analysis failed";
                return;
            }
        }
    }
    pd->close();
}


void runAnalysisModule::analyzeAllFrames()
{


    if(!cam1Files->getNoFiles()){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No image file loaded");
        noFileErrorMessage.exec();
        return;
    }
    if(!roiShapes->isRoiDefined()){
        QMessageBox noRoiErrorMessage;
        noRoiErrorMessage.setText(
                    "No ROI defined");
        noRoiErrorMessage.exec();
        return;
    }
    if(!seedLayer->getSeedExist()){
        QMessageBox noSeedErrorMessage;
        noSeedErrorMessage.setText(
                    "Seed mut be set before running the analysis");
        noSeedErrorMessage.exec();
        return;
    }
    updatedReferenceIdx = 0;
    correlationWidgetList->selectAll();
    multipleFrame();
    pd->close();
}

void runAnalysisModule::splineOrder(int val)
{
    switch (val) {
    case 0:
        seedLayer->setInterpDegree(3);
        break;
    case 1:
        seedLayer->setInterpDegree(5);
        break;
    case 2:
        seedLayer->setInterpDegree(7);
        break;
    case 3:
        seedLayer->setInterpDegree(9);
        break;
    default:
        seedLayer->setInterpDegree(3);
        break;
    }
}

void runAnalysisModule::searchRegionBox(int val)
{
    seedLayer->searchBoxWidth = val;
    seedLayer->updateDrawing();
    cam1Display->updateResized();
}

void runAnalysisModule::highStrainEnable(bool val)
{
    seedLayer->highStrainEnabled = val;
}

void runAnalysisModule::cancel()
{
    analysisCanceled = true;

    pd->close();
}

cv::Matx23d runAnalysisModule::computeInitialGuess(cv::Mat* imageToProcess,
                                                   cv::Point2i& seedPoint){


    int regionOfResearchWidth = seedLayer->searchBoxWidth;
    static templateMatch templateMatchInstance;

    /// Create the template (subset located around seed point)
    cv::Rect subsetRectangle;
    cv::Mat initialSubset;
    subsetRectangle = cv::Rect(seedPoint.x-subsetList->getSubsetHalf(),
                               seedPoint.y-subsetList->getSubsetHalf(),
                               subsetList->getSubsetSize(),
                               subsetList->getSubsetSize());
    if(referenceUpdated){
        qDebug() << "Updated reference template matching: " << updatedReferenceIdx;
        initialSubset = cv::Mat(cam1Files->getImage(updatedReferenceIdx),subsetRectangle);
    } else {
        initialSubset= cv::Mat(cam1Files->getRefImage(),subsetRectangle);
    }

    int topLeftX = seedPoint.x-regionOfResearchWidth/2 > 0 ? seedPoint.x-regionOfResearchWidth/2 : 0;
    int topLeftY = seedPoint.y-regionOfResearchWidth/2 > 0 ? seedPoint.y-regionOfResearchWidth/2 : 0;

    int botRightX = seedPoint.x+regionOfResearchWidth/2 < imageToProcess->cols ? seedPoint.x+regionOfResearchWidth/2 : imageToProcess->cols;
    int botRightY = seedPoint.y+regionOfResearchWidth/2 < imageToProcess->rows ? seedPoint.y+regionOfResearchWidth/2 : imageToProcess->rows;

    cv::Rect regionOfResearchRectangle = cv::Rect(topLeftX,
                                                  topLeftY,
                                                  botRightX-topLeftX,
                                                  botRightY-topLeftY);


    cv::Point newLocation;
    newLocation = templateMatchInstance.matchSeed((*imageToProcess)(regionOfResearchRectangle),initialSubset)+
            cv::Point2i(topLeftX,topLeftY);
    //    qDebug() << newLocation.x << newLocation.y;
    //    qDebug() << seedPoint.x-regionOfResearchWidth/2 << seedPoint.y-regionOfResearchWidth/2;
    //    qDebug() << newLocation2.x << newLocation2.y;
    cv::Matx23d warp = cv::Matx23d::eye();
    warp(0,2) = (newLocation.x-seedPoint.x);
    warp(1,2) = (newLocation.y-seedPoint.y);
    qDebug() << "Initial warp:" <<  warp(0,0) << warp(0,1) << warp(0,2)
             << warp(1,0) << warp(1,1) << warp(1,2);

    //warp(0,2) = 0; warp(1,2) = 0;

    initialSubset.release();
    return warp;
}


void runAnalysisModule::intenseSearchEnable(bool val)
{
    seedLayer->intenseSearch = val;
    qDebug() << "Intense search: " << val;
}

void runAnalysisModule::corrCoefRejection_Edited()
{
    seedLayer->corrRejection = corrRejectionText->text().toDouble()*0.01;
}
