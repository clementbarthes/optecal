#ifndef EXPORTMODULE_H
#define EXPORTMODULE_H
#include <QObject>
#include <QPushButton>
#include <QDir>
#include <QDebug>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QProgressDialog>
#include <fstream>
#include <QApplication>
#include "opencv2/opencv.hpp"

#include "filelist.h"
#include "autoresize.h"
#include "draworigin.h"
#include "qlabelwmouse.h"
#include "calibration.h"
#include "displacements.h"
#include "mat.h"

class exportModule: public QObject
{
    Q_OBJECT
    fileList *correlationFiles;
    drawOrigin *originAndAxesLayer;
    QDir *rootPath;
    displacements *dispFbk;
    calibration *cam1Calibration;
    
    int long exportIdx;

    int exportType;
    QProgressDialog* pd;

    std::vector<int> selectedFrames;
    bool exportCanceled;
    bool *licenseValidated;


    QListWidget *listWidget;
    bool exportResults(int imageIdx, QDir folderPath);
    double convertToUnits(int dataIdx);
    int fpsExport;
    int videoRes;

    cv::Mat createSolImageWColorBar(cv::Mat &image, int exportType, displacements &dispSol);
public:
    static const int long
    xExport = 0x0001,
    yExport = 0x0002,
    uExport = 0x0004,
    vExport =   0x0008,
    exxExport = 0x0010,
    eyyExport = 0x0020,
    exyExport = 0x0040,
    corrCoefExport  = 0x0080,
    e1Export = 0x0100,
    e2Export = 0x0200,
    dir1Export = 0x0400,
    dir2Export = 0x0800,
    vmExport = 0x1000,
    trescaExport = 0x2000,
    rotExport = 0x4000;
    
    static const int jpgImage = 0,
    bmpImage = 1, tiffImage= 2,
    csvFile = 3, matlabFile = 4;

    int dispExportArray[15];

    exportModule(fileList *correlationFiles, drawOrigin* originAndAxesLayer,
                 calibration *cam1Calibration, displacements *dispFbk,
                 QDir *rootPath, QListWidget *listWidget, bool *licenseValidated);

signals:

public slots:

    void singleFrameExport();
    void allFramesExport();
    void fpsSpinBox(double val);
    void videoFormat(int val);
    void exportVideoButton();
    void setXExportCheck(bool val);
    void setYExportCheck(bool val);
    void setUExportCheck(bool val);
    void setVExportCheck(bool val);
    void setRotationExportCheck(bool val);
    void setExxExportCheck(bool val);
    void setEyyExportCheck(bool  val);
    void setExyExportCheck(bool val);
    void setCorrCoefExportCheck(bool val);
    void setE1ExportCheck(bool val);
    void setE2ExportCheck(bool val);
    void setDir1ExportCheck(bool val);
    void setDir2ExportCheck(bool val);
    void setVMExportCheck(bool val);
    void setTrescaExportCheck(bool val);

    void setExportType(int val);

    void cancel();

    void multipleFrame();
    void multipleFrameSelection(QModelIndexList val);
};

#endif // EXPORTMODULE_H
