#include "exportmodule.h"

exportModule::exportModule(fileList *correlationFiles, drawOrigin* originAndAxesLayer,
                                         calibration * cam1Calibration, displacements* dispFbk, QDir* rootPath,
                           QListWidget *listWidget, bool *licenseValidated)
{
    this->correlationFiles = correlationFiles;
    this->originAndAxesLayer = originAndAxesLayer;
    this->dispFbk = dispFbk;
    this->rootPath = rootPath;
    this->cam1Calibration = cam1Calibration;
    this->listWidget = listWidget;
    this->licenseValidated = licenseValidated;
    exportIdx = 0x00;
    exportType = 0;
    pd = new QProgressDialog("Exporting...", "Cancel", 0, 13);
    connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));
    pd->close();
    fpsExport = 5;
    videoRes = 2;
    dispExportArray[0] = displacements::getX;
    dispExportArray[1] = displacements::getY;
    dispExportArray[2] = displacements::getU;
    dispExportArray[3] = displacements::getV;
    dispExportArray[4] = displacements::getExx;
    dispExportArray[5] = displacements::getEyy;
    dispExportArray[6] = displacements::getExy;
    dispExportArray[7] = displacements::getCorr;
    dispExportArray[8] = displacements::getPS1;
    dispExportArray[9] = displacements::getPS2;
    dispExportArray[10] = displacements::getPD1;
    dispExportArray[11] = displacements::getPD2;
    dispExportArray[12] = displacements::getVM;
    dispExportArray[13] = displacements::getTresca;
    dispExportArray[14] = displacements::getRot;

}


bool exportModule::exportResults(int imageIdx, QDir folderPath)
{
    MATFile *pmat;
    mxArray *pa1;
    int status;
    QString outputMatFile;

    pd->setVisible(true);
    pd->setValue(0);
    qApp->processEvents();

    displacements dispSol;

    // Get image
    cv::Mat image;
    if(originAndAxesLayer->deformedConfiguration)
        image = correlationFiles->getImage8bits(imageIdx);
    else
        image = correlationFiles->getImage8bits(correlationFiles->getRefImageIdx());

    cv::cvtColor(image,image,cv::COLOR_GRAY2RGB);

    if(displacements::openSolutionFile(imageIdx, correlationFiles,&dispSol)){
        //  Get processing parameters for the results
        dispSol = *dispFbk;
        dispSol.createResizedSolution(image);
        QString outputName, extension;
        switch(exportType){
        case tiffImage:
            extension = ".tiff";
            break;
        case bmpImage:
            extension = ".bmp";
            break;
        case jpgImage:
            extension = ".jpg";
            break;
        case matlabFile:
            extension = ".mat";
            outputMatFile = correlationFiles->getFileNames(imageIdx) + extension;

            pmat = matOpen(QDir(folderPath).absoluteFilePath(outputMatFile).toUtf8(), "w");
            if (pmat == NULL) {
                QMessageBox noFileErrorMessage;
                noFileErrorMessage.setText(
                            "Cannot write mat file in chosen folder.");
                noFileErrorMessage.exec();
                return false;
            }
            break;
        case csvFile:
            extension = ".csv";
            break;
        }


        int long exportArray[] = {xExport, yExport, uExport, vExport, exxExport, eyyExport, exyExport, corrCoefExport,
                                  e1Export, e2Export, dir1Export, dir2Export, vmExport, trescaExport, rotExport};

        char fileNameArray[15][50];
        char matVarNameArray[15][50];
        if(originAndAxesLayer->polarCartFlag == drawOrigin::cartesianCoord){
            strcpy_s(fileNameArray[0],"_X");strcpy_s(fileNameArray[1],"_Y");strcpy_s(fileNameArray[2],"_dispU");strcpy_s(fileNameArray[3],"_dispV");
            strcpy_s(fileNameArray[4],"_Exx");strcpy_s(fileNameArray[5],"_Eyy");strcpy_s(fileNameArray[6],"_Exy");strcpy_s(fileNameArray[7],"_Corr");
            strcpy_s(matVarNameArray[0],"X");strcpy_s(matVarNameArray[1],"Y");strcpy_s(matVarNameArray[2],"U");strcpy_s(matVarNameArray[3],"V");
            strcpy_s(matVarNameArray[4],"Exx");strcpy_s(matVarNameArray[5],"Eyy");strcpy_s(matVarNameArray[6],"Exy");strcpy_s(matVarNameArray[7],"Corr_Coef");
        } else {
            strcpy_s(fileNameArray[0],"_R");strcpy_s(fileNameArray[1],"_Theta");strcpy_s(fileNameArray[2],"_dispUr");strcpy_s(fileNameArray[3],"_dispUt");
            strcpy_s(fileNameArray[4],"_Err");strcpy_s(fileNameArray[5],"_Ett");strcpy_s(fileNameArray[6],"_Ert");strcpy_s(fileNameArray[7],"_Corr");
            strcpy_s(matVarNameArray[0],"R");strcpy_s(matVarNameArray[1],"Theta");strcpy_s(matVarNameArray[2],"Ur");strcpy_s(matVarNameArray[3],"Ut");
            strcpy_s(matVarNameArray[4],"Err");strcpy_s(matVarNameArray[5],"Ett");strcpy_s(matVarNameArray[6],"Ert");strcpy_s(matVarNameArray[7],"Corr_Coef");
        }
        strcpy_s(fileNameArray[8],"_e1");strcpy_s(fileNameArray[9],"_e2");strcpy_s(fileNameArray[10],"_dir1");strcpy_s(fileNameArray[11],"_dir2");
        strcpy_s(fileNameArray[12],"_VonMises");strcpy_s(fileNameArray[13],"_Tresca");strcpy_s(fileNameArray[14],"_Rotation");
        strcpy_s(matVarNameArray[8],"e1");strcpy_s(matVarNameArray[9],"e2");strcpy_s(matVarNameArray[10],"dir1");strcpy_s(matVarNameArray[11],"dir2");
        strcpy_s(matVarNameArray[12],"VonMises");strcpy_s(matVarNameArray[13],"Tresca");strcpy_s(matVarNameArray[14],"Rotation");


        // Count the number of exports
        int nExports = 0;
        for (int j=0;  j<15; ++j){
            if (exportIdx & exportArray[j]){
                nExports += 1;
                qDebug() << nExports;
            }
        }
        pd->setMaximum(nExports);
        int counter = 0;
        for (int j=0;  j<15; ++j){
            if(exportCanceled)
                return false;

            if (exportIdx & exportArray[j]){
                qDebug() <<" Export array index" << j;
                qDebug() << "Export array value" << exportIdx << exportArray[j];
                if (exportType == tiffImage || exportType == bmpImage || exportType == jpgImage){

                    cv::Mat imageWcolorBar;
                    imageWcolorBar = createSolImageWColorBar(image,j,dispSol);
                    outputName = correlationFiles->getFileNames(imageIdx) + fileNameArray[j] + extension;
                    cv::imwrite(QDir(folderPath).absoluteFilePath(outputName).toStdString(),imageWcolorBar);
                    qDebug() << "Image created: " << QDir(folderPath).absoluteFilePath(outputName);
                } else {
                    dispSol.computeMaskAndLimits(dispExportArray[j],originAndAxesLayer);
                    outputName = correlationFiles->getFileNames(imageIdx) + fileNameArray[j] + extension;
                    // Convert mask from int to double
                    cv::Mat maskDouble;
                    dispSol.maskDisplay.convertTo(maskDouble,CV_64F);
                    // If mask value is negative, make it zero, else make it 1
                    //  Apply the slope and offset for the colormap
                    for ( cv::Mat_<double>::iterator maskDoubleIter = maskDouble.begin<double>(); maskDoubleIter != maskDouble.end<double>(); ++maskDoubleIter)
                    {
                        *maskDoubleIter = *maskDoubleIter > 0. ? 1.:0.;
                    }

                    cv::Mat outputMat = cv::Mat::zeros(dispSol.results.rows,dispSol.results.cols,CV_64F);
                    outputMat = dispSol.results.mul(maskDouble);
                    // Scale to chosen units
                    outputMat = convertToUnits(dispExportArray[j])*outputMat;

                    if(exportType == csvFile){
                        std::ofstream outputFile;
                        outputFile.open (QDir(folderPath).absoluteFilePath(outputName).toStdString());
                        outputFile << cv::format(outputMat,cv::Formatter::FMT_CSV);
                        outputFile.close();
                    } else if (exportType == matlabFile){
                        pa1 = mxCreateDoubleMatrix(outputMat.cols,outputMat.rows,mxREAL);

                        memcpy((void *)(mxGetPr(pa1)), (void *)outputMat.data, outputMat.rows*outputMat.cols*sizeof(double));
                        status = matPutVariable(pmat, matVarNameArray[j], pa1);
                        mxDestroyArray(pa1);
                        qDebug() <<"Status: "<< status;
                    }
                }
            }
            pd->setValue(counter);
            qApp->processEvents();
            counter+= 1;
        }
    }

    if (exportType == matlabFile){
        if(matClose(pmat) != 0) {
            QMessageBox noFileErrorMessage;
            noFileErrorMessage.setText(
                        "Error writing MAT file");
            noFileErrorMessage.exec();
            return false;
        }


    }
    return true;
}

cv::Mat exportModule::createSolImageWColorBar(cv::Mat& image, int exportType, displacements& dispSol)
{
    cv::Mat colorMap, colorBar, imageOut;


    originAndAxesLayer->setImageResizeCoef(1.);
    dispSol.computeMaskAndLimits(dispExportArray[exportType],originAndAxesLayer);
    colorMap = dispSol.computeColorMap(dispExportArray[exportType],1.,originAndAxesLayer);


    image.copyTo(imageOut);
    cv::Mat mask8;
    dispSol.maskDisplay.convertTo(mask8,CV_8UC1);
    float backgroundCoef =
            (1.3-originAndAxesLayer->colormapCoef) <= 1. ?
                (1.3-originAndAxesLayer->colormapCoef) : 1.;
    cv::add(backgroundCoef*image,originAndAxesLayer->colormapCoef*colorMap,imageOut,mask8);
    originAndAxesLayer->setImage(&imageOut,1.);
    originAndAxesLayer->updateDrawing();

    // Get color bar
    colorBar = dispSol.drawScale(dispExportArray[exportType],originAndAxesLayer, cam1Calibration);
    float imgRatio = (float)(colorBar.cols)/(float)(colorBar.rows);
    cv::resize(colorBar,colorBar,cv::Size(imageOut.rows*imgRatio,imageOut.rows));

    cv::Mat imageWcolorBar = cv::Mat::zeros(imageOut.rows,imageOut.cols+1.2*colorBar.cols, imageOut.type());
    imageWcolorBar.setTo(cv::Scalar(255,255,255));
    cv::Rect colorBarRoi(imageWcolorBar.cols-colorBar.cols, 0, colorBar.cols, colorBar.rows);

    colorBar.copyTo(imageWcolorBar(colorBarRoi));
    imageOut.copyTo(imageWcolorBar(cv::Rect(0,0,image.cols,image.rows)));


    // Convert output to BGR
    cv::cvtColor(imageWcolorBar,imageWcolorBar, cv::COLOR_RGB2BGR );
    return imageWcolorBar;
}


void exportModule::singleFrameExport()

{
    selectedFrames.clear();
    QList<QListWidgetItem*> widgetListItems = listWidget->selectedItems();
    for(int listIter = 0 ; listIter < listWidget->count(); ++listIter){
        for (int k = 0; k< widgetListItems.size(); ++k){
            if(listWidget->item(listIter)->text() == widgetListItems[k]->text()){
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

    if(exportIdx == 0x0000){
        QMessageBox noExportErrorMessage;
        noExportErrorMessage.setText(
                    "Please select the variables that you want to export");
        noExportErrorMessage.exec();
        return;
    }
    QString folderPath = QFileDialog::getExistingDirectory(0, tr("Choose a directory"),
                                                           rootPath->absolutePath(), QFileDialog::ShowDirsOnly);
    if (folderPath.length() != 0){
        int counter = 0;
        for (int j = 0; j < selectedFrames.size(); ++j){
            if(!correlationFiles->isRefImage(selectedFrames[j])){
                qDebug() << "Frame: " << selectedFrames[j];
                ++counter;
                QString imageNumberSolved = QString ("Exporting solution %1/%2").arg(
                            QString::number (counter),QString::number (selectedFrames.size()));
                correlationFiles->setCurrentImgIdx(selectedFrames[j]);
                pd->setLabelText(imageNumberSolved);
                exportCanceled = false;
                if(!exportResults(selectedFrames[j],folderPath))
                    return;
            }
        }
    }
    pd->close();
}


void exportModule::multipleFrameSelection(QModelIndexList val)
{

    selectedFrames.clear();
    foreach(QModelIndex index, val)
    {
        selectedFrames.push_back(index.row());

    }
    for (int i = 0 ; i < selectedFrames.size(); ++i){
        if(selectedFrames[i] == correlationFiles->getRefImageIdx()){
            selectedFrames.erase(selectedFrames.begin()+ i - 1);
        }
        qDebug() << selectedFrames[i];
    }
}

void exportModule::multipleFrame(){

}

void exportModule::allFramesExport()
{
    listWidget->selectAll();
    singleFrameExport();
}

void exportModule::fpsSpinBox(double val)
{
    fpsExport = (int)val;

    qDebug() << "FPS export: " << fpsExport;
}

void exportModule::videoFormat(int val)
{
    videoRes = val;
}

void exportModule::exportVideoButton()
{
    if(exportIdx == 0x0000){
        QMessageBox noExportErrorMessage;
        noExportErrorMessage.setText(
                    "Please select the variables that you want to export");
        noExportErrorMessage.exec();
        return;
    }
    int long exportArray[] = {xExport, yExport, uExport, vExport, exxExport, eyyExport, exyExport, corrCoefExport,
                              e1Export, e2Export, dir1Export, dir2Export, vmExport, trescaExport, rotExport};
    char fileNameArray[15][50];
    if(originAndAxesLayer->polarCartFlag == drawOrigin::cartesianCoord){
        strcpy_s(fileNameArray[0],"_X");strcpy_s(fileNameArray[1],"_Y");strcpy_s(fileNameArray[2],"_dispU");strcpy_s(fileNameArray[3],"_dispV");
        strcpy_s(fileNameArray[4],"_Exx");strcpy_s(fileNameArray[5],"_Eyy");strcpy_s(fileNameArray[6],"_Exy");strcpy_s(fileNameArray[7],"_Corr");
    } else {
        strcpy_s(fileNameArray[0],"_R");strcpy_s(fileNameArray[1],"_Theta");strcpy_s(fileNameArray[2],"_dispUr");strcpy_s(fileNameArray[3],"_dispUt");
        strcpy_s(fileNameArray[4],"_Err");strcpy_s(fileNameArray[5],"_Ett");strcpy_s(fileNameArray[6],"_Ert");strcpy_s(fileNameArray[7],"_Corr");
    }
    strcpy_s(fileNameArray[8],"_e1");strcpy_s(fileNameArray[9],"_e2");strcpy_s(fileNameArray[10],"_dir1");strcpy_s(fileNameArray[11],"_dir2");
    strcpy_s(fileNameArray[12],"_VonMises");strcpy_s(fileNameArray[13],"_Tresca");


    exportCanceled = false;
    QString folderPath = QFileDialog::getExistingDirectory(0, tr("Choose a directory"),
                                                           rootPath->absolutePath(), QFileDialog::ShowDirsOnly);
    // Count the number of exports
    int nExports = 0;
    for (int j=0;  j<15; ++j){
        if (exportIdx & exportArray[j]){
            nExports += 1;
        }
    }
    if (folderPath.length() != 0){
        int counter = 0;
        pd->setMaximum(correlationFiles->getFileNames().size());
        pd->setVisible(true);
        pd->setValue(0);
        qApp->processEvents();

        for (int j=0;  j<15; ++j){
            if (exportIdx & exportArray[j]){
                ++counter;
                QString videoNumberSolved = QString ("Exporting video file %1/%2").arg (QString::number (counter),QString::number (nExports));
                pd->setLabelText(videoNumberSolved);

                displacements dispSol;

                cv::Mat image;
                cv::Mat currentFrame;
                cv::Size videoSize;

                switch (videoRes) {
                case 0:
                    videoSize = cv::Size(640,480);
                    break;
                case 1:
                    videoSize = cv::Size(1920,1080);
                    break;
                case 2:
                    videoSize = cv::Size(4096,1860);
                    break;
                default:
                    videoSize = cv::Size(4096,1860);
                    break;
                }

                QString outputName = correlationFiles->getFileNames(0) + fileNameArray[j] + ".avi";

                cv::Mat videoFrame = cv::Mat::zeros(videoSize, CV_8UC3);
                float videoRatio = (float)videoSize.width/(float)videoSize.height;
                cv::VideoWriter outputVideo;
                outputVideo.open(QDir(folderPath).absoluteFilePath(outputName).toStdString(),  cv::VideoWriter::fourcc('X','V','I','D'), fpsExport, videoSize, true);
                if(!outputVideo.isOpened()){
                    QMessageBox writeUnableMessage;
                    writeUnableMessage.setText(
                                "Cannot open the video file.");
                    writeUnableMessage.exec();
                    return;
                }

                for(int imgIdx = 0; imgIdx < correlationFiles->getFileNames().size(); ++imgIdx){
                    if(exportCanceled){
                        outputVideo.release();
                        return;
                    }
                    if(originAndAxesLayer->deformedConfiguration)
                        image = correlationFiles->getImage8bits(imgIdx);
                    else
                        image = correlationFiles->getImage8bits(correlationFiles->getRefImageIdx());
                    cv::cvtColor(image,image, cv::COLOR_GRAY2RGB);
                    if(displacements::openSolutionFile(imgIdx, correlationFiles,&dispSol)){
                        //  Get processing parameters for the results
                        dispSol = *dispFbk;
                        dispSol.createResizedSolution(image);
                        currentFrame = createSolImageWColorBar(image, j, dispSol);
                    } else {
                        currentFrame = image;
                    }
                    float currentFrameRatio = (float)currentFrame.size().width/(float)currentFrame.size().height;
                    if(currentFrameRatio > videoRatio){
                        cv::resize(currentFrame,currentFrame,cv::Size(videoSize.width,(1./currentFrameRatio)*videoSize.width));
                        currentFrame.copyTo(videoFrame(cv::Rect(0,videoFrame.rows/2 - currentFrame.rows/2,currentFrame.cols,currentFrame.rows)));
                    } else {

                        cv::resize(currentFrame,currentFrame,cv::Size(currentFrameRatio*videoSize.height,videoSize.height));
                        currentFrame.copyTo(videoFrame(cv::Rect(videoFrame.cols/2 - currentFrame.cols/2,0,currentFrame.cols,currentFrame.rows)));
                    }
                    outputVideo << videoFrame;
                    pd->setValue(imgIdx);
                    qApp->processEvents();
                }
                outputVideo.release();
                qDebug() << "Export video";
            }
        }
    }
    pd->close();
}

    void exportModule::cancel()
    {
        exportCanceled = true;
        pd->close();
    }

    void exportModule::setXExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | xExport;
        } else{
            exportIdx = exportIdx & ~xExport;
        }
        qDebug() << "X export: " << val << exportIdx;
    }

    void exportModule::setYExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | yExport;
        } else{
            exportIdx = exportIdx & ~yExport;
        }
        qDebug() << "Y export: " << val << exportIdx;
    }

    void exportModule::setUExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | uExport;
        } else{
            exportIdx = exportIdx & ~uExport;
        }
        qDebug() << "U export: " << val << exportIdx;
    }

    void exportModule::setVExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | vExport;
        } else{
            exportIdx = exportIdx & ~vExport;
        }
        qDebug() << "V export: " << val << exportIdx;
    }

    void exportModule::setRotationExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | rotExport;
        } else{
            exportIdx = exportIdx & ~rotExport;
        }
        qDebug() << "Rotation export: " << val << exportIdx;
    }

    void exportModule::setExxExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | exxExport;
        } else{
            exportIdx = exportIdx & ~exxExport;
        }
        qDebug() << "Exx export: " << val << exportIdx;
    }

    void exportModule::setEyyExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | eyyExport;
        } else{
            exportIdx = exportIdx & ~eyyExport;
        }
        qDebug() << "Eyy export: " << val << exportIdx;
    }

    void exportModule::setExyExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | exyExport;
        } else{
            exportIdx = exportIdx & ~exyExport;
        }
        qDebug() << "Exy export: " << val << exportIdx;
    }
    void exportModule::setCorrCoefExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | corrCoefExport;
        } else{
            exportIdx = exportIdx & ~corrCoefExport;
        }
        qDebug() << "Correlation Coefficient export: " << val << exportIdx;
    }

    void exportModule::setE1ExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | e1Export;
        } else{
            exportIdx = exportIdx & ~e1Export;
        }
        qDebug() << "E1 export: " << val << exportIdx;
    }

    void exportModule::setE2ExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | e2Export;
        } else{
            exportIdx = exportIdx & ~e2Export;
        }
        qDebug() << "E2 export: " << val << exportIdx;
    }

    void exportModule::setDir1ExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | dir1Export;
        } else{
            exportIdx = exportIdx & ~dir1Export;
        }
        qDebug() << "Dir. 1 export: " << val << exportIdx;
    }

    void exportModule::setDir2ExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | dir2Export;
        } else{
            exportIdx = exportIdx & ~dir2Export;
        }
        qDebug() << "Dir. 2 export: " << val << exportIdx;
    }

    void exportModule::setVMExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | vmExport;
        } else{
            exportIdx = exportIdx & ~vmExport;
        }
        qDebug() << "VM export: " << val << exportIdx;
    }

    void exportModule::setTrescaExportCheck(bool val)
    {
        if(val){
            exportIdx = exportIdx | trescaExport;
        } else{
            exportIdx = exportIdx & ~trescaExport;
        }
        qDebug() << "Tresca export: " << val << exportIdx;
    }

    void exportModule::setExportType(int val)
    {
        exportType = val;
    }

    double exportModule::convertToUnits(int dataIdx)
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
            return unitScaleFactor;
        } else{
            return 1.;
        }
    }

