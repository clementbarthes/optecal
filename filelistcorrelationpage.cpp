#include "filelistcorrelationpage.h"

fileListCorrelationPage::fileListCorrelationPage(QFileDialog* loadImages, QListWidget* listFilesWidget,
                                                 autoResize* cam1Display, fileList* imageFiles,
                                                 drawShape* roiShapes, drawSeedPoint* seedLayer,
                                                 drawOrigin* originAndAxesLayer, virtualMeasurementTools *virtualTools)
    :fileListPage(loadImages, listFilesWidget,
                  cam1Display, imageFiles)

{
    this->roiShapes = roiShapes;
    this->seedLayer = seedLayer;
    this->originAndAxesLayer = originAndAxesLayer;
    this->virtualTools = virtualTools;
    playAnimTimer = new QTimer(this);
    connect(playAnimTimer, SIGNAL(timeout()), this, SLOT(playAnimation()));
    fps = 2.;
    refLoaded = false;
}


void fileListCorrelationPage::on_listFilesWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0){
        if(((modulesToolBoxIndex == displacementsPage) || (modulesToolBoxIndex == postProcessingPage)
            || (modulesToolBoxIndex == exportPage) )
                && !originAndAxesLayer->deformedConfiguration){
            cam1Display->setCurrentImg(imageFiles->getRefImagePath());
            refLoaded = true;
        }else{
            cam1Display->setCurrentImg(imageFiles->getFilePath(currentRow));
            refLoaded = false;
        }
        imageFiles->setCurrentImgIdx(currentRow);
        if (imageFiles->isRefImage(currentRow)){
            roiShapes->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            emit enablePlusShapes(true);
            emit enableMinusShapes(true);
            if(modulesToolBoxIndex==drawRoiPage){
                roiShapes->updateWLines();
                cam1Display->updateResized();
            }else{
                roiShapes->updateDrawing();
                cam1Display->updateResized();
            }

            qDebug() << "Ref image loaded";
        }
        if(seedLayer->getSeedExist() && (modulesToolBoxIndex == runAnalysisPage)){
            seedLayer->setRefImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef(),cam1Display->getCurrentImg());
            seedLayer->updateDrawing();
            cam1Display->updateResized();
        }

        if (modulesToolBoxIndex == postProcessingPage){
            virtualTools->updateSolutionMap(originAndAxesLayer,
                                            currentRow,
                                            imageFiles);
        }
        if (modulesToolBoxIndex == exportPage){
            qDebug() << "Export page";
            originAndAxesLayer->setImage(cam1Display->getCurrentResizedImg(),cam1Display->getResizeCoef());
            originAndAxesLayer->updateDrawing();
            cam1Display->updateResized();
        }
    }
    emit updateDisplay();
}

void fileListCorrelationPage::on_modulesToolBoxIndex(int index)
{
    modulesToolBoxIndex = index;
}

void fileListCorrelationPage::pause_Button()
{
    playAnimTimer->stop();
}

void fileListCorrelationPage::play_Button()
{
    playAnimTimer->start((int)(1000./fps));
}

void fileListCorrelationPage::playAnimation()
{
    if(imageFiles->getCurrentImgIdx() < (imageFiles->getFileNames().size()-1))
        listFilesWidget->setCurrentRow(imageFiles->getCurrentImgIdx() + 1);
    else
        playAnimTimer->stop();
}
