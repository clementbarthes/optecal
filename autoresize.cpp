#include "autoresize.h"


// Resizes the displayed image while keeping the ratio constant
autoResize::autoResize()
{
}

autoResize::~autoResize()
{
    currentImg.release();
    currentImgDisplayed.release();
}

void autoResize::setDisplayBox(QLabelWMouse* imgBox){
    imageDisplayBox = imgBox;
}

void autoResize::setCurrentImg(QString FilePath){

    QFile File(FilePath);
    if(File.exists()){
        // Open all image files in 8-bits B&W then convert image to color in order to display the ROI in red
        cv::cvtColor(cv::imread(FilePath.toStdString(),0),currentImg, cv::COLOR_GRAY2RGB);
        imgRatio = (float)(currentImg.size().width)/(float)(currentImg.size().height);
        qDebug() << "Image Ratio: " << imgRatio << imageDisplayBox->height() << imageDisplayBox->width();
        if ((imageDisplayBox->height() < 100 )|| (imageDisplayBox->width() < 100)){
            imageDisplayBox->setFixedHeight(500);
            imageDisplayBox->setFixedWidth(imgRatio*500);
        }

    } else {
        QMessageBox fileNotFound;
        fileNotFound.setText("Image file not found. Do you want to specify the new folder location?");
        fileNotFound.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        fileNotFound.setDefaultButton(QMessageBox::No);
        fileNotFound.setModal(true);
        if(fileNotFound.exec() == QMessageBox::Yes){
            QString folderPath = QFileDialog::getExistingDirectory(0, tr("Choose a directory"),
                                                                   QString(), QFileDialog::ShowDirsOnly);
            if (!folderPath.isEmpty())
                emit newCorrelationFilePath(folderPath);
        }
    }
}

void autoResize::setCurrentImgMat(cv::Mat currentImgInput)

{
    currentImg = currentImgInput;
    imgRatio = (float)(currentImg.size().width)/(float)(currentImg.size().height);
    imageDisplayBox->setFixedHeight(500);
    imageDisplayBox->setFixedWidth(imgRatio*500);
}

void autoResize::update(){
    if (!currentImg.empty()){
        imageDisplayBox->resize(imageDisplayBox->height()*imgRatio,imageDisplayBox->height());
        imageDisplayBox->imgRatio = imgRatio;
        qDebug() << imageDisplayBox->width() << "x" << imageDisplayBox->height();
        cv::resize(currentImg,currentImgDisplayed,cv::Size(imageDisplayBox->width(),imageDisplayBox->height()));
        // Add the watermark if demo version
        QImage qCurrentImg((uchar*)currentImgDisplayed.data, currentImgDisplayed.cols,
                           currentImgDisplayed.rows, (int)currentImgDisplayed.step, QImage::Format_RGB888);
        imageDisplayBox->setPixmap(QPixmap::fromImage(qCurrentImg));
    }
}

void autoResize::updateResized(){
    if (!currentImgDisplayed.empty()){
        QImage qCurrentImg((uchar*)currentImgDisplayed.data, currentImgDisplayed.cols,
                           currentImgDisplayed.rows, (int)currentImgDisplayed.step, QImage::Format_RGB888);
        imageDisplayBox->setPixmap(QPixmap::fromImage(qCurrentImg));
    }
}

cv::Mat* autoResize::getCurrentImg(){
    return &currentImg;
}


cv::Mat *autoResize::getCurrentResizedImg()
{
    return &currentImgDisplayed;
}

float autoResize::getResizeCoef(){
    return (float)currentImg.size().height/(float)imageDisplayBox->height();
}

float autoResize::getImgRatio(){
    return imgRatio;
}

void autoResize::clear(){
    currentImg =cv::Mat::zeros(1,1,currentImg.type());
    currentImgDisplayed = cv::Mat::zeros(1,1,currentImg.type());
    imgRatio = 1.;
}

void autoResize::clearLabel()
{
    imageDisplayBox->clear();
}


