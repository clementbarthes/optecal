#ifndef AUTORESIZE_H
#define AUTORESIZE_H
#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QAbstractButton>
#include <QMessageBox>

#include <math.h>
#include "qlabelwmouse.h"
#include "opencv2/opencv.hpp"

class autoResize: public QObject
{
    Q_OBJECT

    cv::Mat currentImg;
    cv::Mat currentImgDisplayed;
    QLabelWMouse* imageDisplayBox;
    float imgRatio;
public:
    cv::Mat uncorrectedDisplayedImage;
    autoResize();
    ~autoResize();
    void setDisplayBox(QLabelWMouse *imgBox);
    void setCurrentImg(QString FilePath);
    void setCurrentImgMat(cv::Mat currentImgInput);
    void update();
    void updateResized();
    cv::Mat* getCurrentImg();
    cv::Mat* getCurrentResizedImg();
    float getResizeCoef();
    float getImgRatio();
    void clear();
    void clearLabel();
signals:
    void newCorrelationFilePath(QString);
};

#endif // AUTORESIZE_H
