#include "filelistpage.h"

fileListPage::fileListPage(QFileDialog* loadImages, QListWidget* listFilesWidget,
                           autoResize* cam1Display, fileList* imageFiles)
{
    this->listFilesWidget = listFilesWidget;
    this->loadImages = loadImages;
    this->imageFiles = imageFiles;
    this->cam1Display = cam1Display;
}



void fileListPage::on_loadImage_clicked()
{
    loadImages->setFileMode(QFileDialog::ExistingFiles);
    if (imageFiles->getImageType() == fileList::rawFiles){
        loadImages->setNameFilter(tr("RAW Images (*.cr2 *.dng *.nef *.raf *.arw);;Processed Images (*.bmp *.tif *.tiff *.jpg);;All files (*.*)"));
    } else {
        loadImages->setNameFilter(tr("Images (*.bmp *.tif *.tiff *.jpg)"));
    }
    loadImages->setViewMode(QFileDialog::List);
    if (loadImages->exec()){
        imageFiles->appendList(loadImages->selectedFiles());
        updateListFiles();
        listFilesWidget->setCurrentRow(0);
    }
}

void fileListPage::on_sortFilesComboBox_currentIndexChanged(int index)
{
    imageFiles->sortFiles(index);
    updateListFiles();
}

void fileListPage::on_listFilesWidget_currentRowChanged(int currentRow)
{
    qDebug() << "Current row:" << currentRow;
    if(currentRow >= 0){
        if(imageFiles->getImageType() != fileList::rawFiles){
            cam1Display->setCurrentImg(imageFiles->getFilePath(currentRow));
        } else {
            rawConverter *converterInstance = new rawConverter(imageFiles->getFilePath(currentRow));
            cv::Mat dispImage = converterInstance->getThumbnail(imageFiles);
            delete converterInstance;

            if(dispImage.type()!= CV_8UC3){
                dispImage.convertTo(dispImage,CV_8U,0.00390625);
                cv::cvtColor(dispImage,dispImage, cv::COLOR_GRAY2BGR );
            }
            cam1Display->setCurrentImgMat(dispImage);

        }

        cam1Display->update();
        cam1Display->uncorrectedDisplayedImage = cam1Display->getCurrentResizedImg()->clone();
        emit correctThumbnailDistortion();
        imageFiles->setCurrentImgIdx(currentRow);
    }
}

void fileListPage::updateListFiles(){
    listFilesWidget->clear();
    listFilesWidget->addItems(imageFiles->getFileNames());
    if(imageFiles->getRefImageIdx() >=0){
        listFilesWidget->item(imageFiles->getRefImageIdx())->setIcon(QIcon(":/resources/1415541913_minicons2-93-128.png"));
        QFont boldFont = listFilesWidget->item(imageFiles->getRefImageIdx())->font();
        boldFont.setBold(true);
        listFilesWidget->item(imageFiles->getRefImageIdx())->setFont(boldFont);
    }
}



void fileListPage::on_listFilesWidget_customContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = listFilesWidget->viewport()->mapToGlobal(pos);
    int currentRowSelected = listFilesWidget->currentRow();
    QMenu fileManageMenu;
    selectedFrames.clear();
    QList<QListWidgetItem*> widgetList = listFilesWidget->selectedItems();
    qDebug() << "widget list size: " << widgetList.size();
    for(int listIter = 0 ; listIter < listFilesWidget->count(); ++listIter){
        for (int k = 0; k< widgetList.size(); ++k){
            if(listFilesWidget->item(listIter)->text() == widgetList[k]->text()){
                selectedFrames.push_back(listIter);
            }
        }
    }

    if(listFilesWidget->currentRow()>=0){
        if(imageFiles->getImageType() == fileList::correlationFiles)
        {
            fileManageMenu.addAction("Set as Reference image")->setIcon(QIcon(":/resources/1415541913_minicons2-93-128.png"));
        }
        fileManageMenu.addAction("Delete images")->setIcon(QIcon(":/resources/1413496628_Delete.png"));
        QAction* selectedItem = fileManageMenu.exec(globalPos);
        if (selectedItem)
        {
            if(selectedItem->text() == "Set as Reference image"){
                imageFiles->setRefImage(currentRowSelected);
                updateListFiles();
            } else if (selectedItem->text() == "Delete images"){
                qDebug() << "Delete images: " << currentRowSelected;
                if((int)selectedFrames.size()>=2){
                    std::sort(selectedFrames.rbegin(), selectedFrames.rend());
                    for (int i = 0 ; i < selectedFrames.size(); ++i){
                        qDebug() << "list of deleted files:" << selectedFrames[i];
                        imageFiles->deleteImage(selectedFrames[i]);
                    }
                    selectedFrames.clear();
                } else{
                    imageFiles->deleteImage(currentRowSelected);
                }
                updateListFiles();
                if (imageFiles->getFileNames().empty()){
                    cam1Display->clear();
                    cam1Display->update();
                } else {
                    listFilesWidget->setCurrentRow(0);
                }
            }
        }
    }
}

void fileListPage::multipleFrameSelection(QModelIndexList val)
{
    selectedFrames.clear();
    int j = 0;
    foreach(QModelIndex index, val)
    {
        if(index.row() >=0){
            selectedFrames.push_back(index.row());
            qDebug() << selectedFrames[j];
            ++j;
        }

    }
    std::sort(selectedFrames.begin(),selectedFrames.end());
}

