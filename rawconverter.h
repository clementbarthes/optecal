#ifndef RAWCONVERTER_H
#define RAWCONVERTER_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QDebug>
#include <QRunnable>
#include <QThread>
#include <QObject>
#include <QtTest/QtTest>
#include <qendian.h>
#include <QTemporaryFile>
#include <QLineEdit>
#include <QFileDialog>
#include <QCheckBox>
#define NOMINMAX
#include <libraw/libraw.h>

#include "calibration.h"
#include "filelist.h"


#define TOFF(ptr) ((char *)(&(ptr)) - (char *)th)


class rawConverter: public QThread
{
    Q_OBJECT

    QString filePath;
    std::string savePath;
    char outfn[1024];
    char* fileName;
    bool distortionCorrection;
    fileList *rawFiles;
public:
    static QLineEdit *aCal, *bCal, *cCal, *cropFactorEdit;
    static QCheckBox *distortionCheck;
    static calibration *cam1Calibration;
    static cv::Mat remapX, remapY;

    rawConverter(QString filePath);

    cv::Mat convertRawFile();
    cv::Mat getThumbnail(fileList *rawFiles);

    void setSavePath(std::string savePath);

    static int rotationIndex; // 0: 0 degrees, 1: 90 degrees, 2 180 degrees, 3: 270 degrees

    void run();
private:
    void correctDistortion(cv::Mat &image);

    void tiff_set(ushort *ntag, ushort tag, ushort type, int count, int val);
    void write_tiff(int width, int height, unsigned short *bitmap, const char *fn);
    void tiff_head(int width, int height, tiff_hdr *th);

signals:
    void finished();
    void newFilePath(QString);
};

#endif // RAWCONVERTER_H
