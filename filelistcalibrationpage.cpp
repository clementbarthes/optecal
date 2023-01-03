#include "filelistcalibrationpage.h"

fileListCalibrationPage::fileListCalibrationPage(QFileDialog *loadImages, QListWidget *listFilesWidget,
                                                 autoResize *cam1Display, fileList *imageFiles,
                                                 calibration *calibrationInstance)
    :fileListPage(loadImages, listFilesWidget,
                  cam1Display, imageFiles)
{
    this->calibrationInstance = calibrationInstance;
}

//void fileListCalibrationPage::on_listFilesWidget_currentRowChanged(int currentRow)
//{
//    qDebug() << "Current cal row:" << currentRow;
//    if(currentRow >= 0){
//        // Find corners
////        cv::Mat imgWithCorners = calibrationInstance->cornersDisplay(imageFiles->getFilePath(currentRow));
////        cam1Display->setCurrentImgMat(imgWithCorners);

////        cam1Display->update();
////        imageFiles->setCurrentImgIdx(currentRow);
//    }
//}
