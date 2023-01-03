#include "rawmodule.h"

rawModule::rawModule(fileList* rawFiles, fileListPage* rawFilePage, QDir* rootFolder, QLabelWMouse *displayBox, QListWidget *listWidget)
{
    this->rawFiles = rawFiles;
    this->rootFolder = rootFolder;
    this->rawFilePage = rawFilePage;
    this->displayBox = displayBox;
    this->listWidget = listWidget;

    processedCounter = 0;
    analysisCanceled = false;
    pd = new QProgressDialog("Converting...", "Cancel", 0, 10);
    connect(pd, SIGNAL(canceled()), this, SLOT(cancel()));
    pd->close();
}

void rawModule::multipleFrameSelection(QModelIndexList val)
{
    selectedFrames.clear();
    foreach(QModelIndex index, val)
    {
        qDebug() << index;
        selectedFrames.push_back(index.row());

    }
    for (int i = 0 ; i < selectedFrames.size(); ++i){
        if(selectedFrames[i] == rawFiles->getRefImageIdx()){
            selectedFrames.erase(selectedFrames.begin()+ i - 1);
        }
    }
    std::sort( selectedFrames.begin(), selectedFrames.end() );
    selectedFrames.erase( std::unique( selectedFrames.begin(), selectedFrames.end() ), selectedFrames.end() );
}


void rawModule::multipleFrame(){
    rawConverter::remapX = cv::Mat::zeros(1,1,CV_32F);
    rawConverter::remapY = cv::Mat::zeros(1,1,CV_32F);
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

    folderPath = QFileDialog::getExistingDirectory(0, tr("Choose a directory"),
                                                           rootFolder->absolutePath(), QFileDialog::ShowDirsOnly);

    // Check if files exist
    int existCounter = 0;
    for (int i = 0; i<selectedFrames.size();++i){
        QString imagePath = QDir(folderPath).absolutePath() + QString("/") +
                QFileInfo(rawFiles->getFilePath(selectedFrames[i])).baseName() + ".tif";
        if (QFile::exists(imagePath)){
            ++existCounter;
        }
    }
    if (existCounter){
        QMessageBox::StandardButton overwriteMessage;
        if (existCounter == 1){
            overwriteMessage = QMessageBox::question(0, "Overwrite file?",
                                                     "1 file already exists. Do you want to overwrite it?");
        } else {
            overwriteMessage = QMessageBox::question(0, "Overwrite files?",
                                                     QString::number(existCounter) +
                                                     " files already exist. Do you want to overwrite them?",
                                                     QMessageBox::Yes|QMessageBox::No);
        }
        if (overwriteMessage == QMessageBox::No) {
            return;
        }
    }
    if (folderPath.length() != 0){
        analysisCanceled = false;
        processedCounter = 0;
        processedFrames = selectedFrames;
        pd->setMaximum((int)selectedFrames.size());
//        for (int j = 0; j < (int)selectedFrames.size(); ++j){

//        }

        loadNextThread();

    }
}

void rawModule::allFrames(){
    if(rawFiles->getFileNames().size() == 0){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No file loaded");
        noFileErrorMessage.exec();
        return;
    }

    listWidget->selectAll();
    multipleFrame();
}

void rawModule::clockwiseButton(){
    if(rawFiles->getFileNames().size() == 0){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No file loaded");
        noFileErrorMessage.exec();
        return;
    }
    rawConverter::rotationIndex = rawConverter::rotationIndex == 3 ? 0: rawConverter::rotationIndex+1;
    int width = displayBox->width();
    int height = displayBox->height();
    displayBox->setFixedHeight(width);
    displayBox->setFixedWidth(height);
    rawFilePage->on_listFilesWidget_currentRowChanged(rawFiles->getCurrentImgIdx());

}
void rawModule::counterClockwiseButton(){
    if(rawFiles->getFileNames().size() == 0){
        QMessageBox noFileErrorMessage;
        noFileErrorMessage.setText(
                    "No file loaded");
        noFileErrorMessage.exec();
        return;
    }
    rawConverter::rotationIndex = rawConverter::rotationIndex == 0 ? 3: rawConverter::rotationIndex-1;
    int width = displayBox->width();
    int height = displayBox->height();
    displayBox->setFixedHeight(width);
    displayBox->setFixedWidth(height);
    rawFilePage->on_listFilesWidget_currentRowChanged(rawFiles->getCurrentImgIdx());
}

void rawModule::threadFinished()
{
    if(analysisCanceled)
        return;
    if(processedCounter < processedFrames.size()){
        qDebug() << "Loading next frame";
        loadNextThread();
    } else{
        pd->close();
    }
}

void rawModule::loadNextThread()
{
    rawConverter* converterInstance = new rawConverter(rawFiles->getFilePath(processedFrames[processedCounter]));
    std::string imagePath = (QDir(folderPath).absolutePath() + QString("/") +
            QFileInfo(rawFiles->getFilePath(processedFrames[processedCounter])).baseName() + ".tif").toStdString();
    converterInstance->setSavePath(imagePath);
    connect(converterInstance, SIGNAL(finished()), this, SLOT(threadFinished()));
    connect(converterInstance, SIGNAL(finished()), converterInstance, SLOT(deleteLater()));
    converterInstance->start();
    pd->setValue(++processedCounter);
    qApp->processEvents();

}

void rawModule::cancel(){
    analysisCanceled = true;
}
