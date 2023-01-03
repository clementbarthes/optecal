#ifndef OPTECAL_H
#define OPTECAL_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QString>
#include <QCursor>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QProgressDialog>
#include <QScrollBar>
#include <QCloseEvent>
#include <QStandardPaths>
#include <QDesktopServices>

#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "mat.h"


#include "filelist.h"
#include "filelistpage.h"
#include "filelistcalibrationpage.h"
#include "fileListCorrelationPage.h"
#include "autoresize.h"
#include "calibrationmodule.h"
#include "draworigin.h"
#include "rawmodule.h"
#include "drawshape.h"
#include "roimodule.h"
#include "runanalysis.h"
#include "virtualmeasurementtools.h"
#include "postprocessingmodule.h"
#include "displacements.h"
#include "displacementsmodule.h"
#include "exportmodule.h"

using namespace std;

namespace Ui {
class OpteCAL;
}

class OpteCAL : public QMainWindow
{
    Q_OBJECT

    QString softwareVersion;
    QFileDialog* loadRawImages;
    QFileDialog* loadImages;
    fileList* correlationFiles;
    fileList* calibrationFiles;
    fileList* rawFiles;



    autoResize* cam1Display;
    autoResize* scaleDisplay;
    drawShape* roiShapes;
    drawShape* measureTool;
    drawSeedPoint* seedLayer;
    drawOrigin* originAndAxesLayer;
    subsetsMap* subsetList;
    displacements* dispFbk;
    calibration* cam1Calibration;
    virtualMeasurementTools* virtualTools;
    float imageResizeCoef;

    fileListCorrelationPage* correlationFilePage;
    fileListCalibrationPage* calibrationFilePage;
    fileListPage* rawFilePage;
    rawModule* rawModuleInstance;
    calibrationModule* calibrationModuleInstance;
    roiModule* roiModuleInstance;
    runAnalysisModule* runAnalysisInstance;
    displacementsModule* displacementsModuleInstance;
    postProcessingModule* postProcessingModuleInstance;
    exportModule* exportModuleInstance;


    QTimer* resizeInProgress;
    QTimer* resizeInProgressCorrection;
    QTimer* zoomingTimer;
    float zoomX;
    float zoomY;

    QProgressDialog* pd;
    QDir rootFolder;
    cv::String settingsFilePath;
    bool licenseValidated;
    char *installationId ;
    int timeRemaining;

public:
//    static const int calibrationModulePage = 0;
//    static const int drawRoiPage = 1;
//    static const int runAnalysisPage = 2;
//    static const int displacementsPage = 3;
//    static const int postProcessingPage = 4;
//    static const int exportPage = 5;

//    static const int rawPage = 0;
//    static const int calibrationPage = 1;
//    static const int correlationPage = 2;

    // without calibration modules
    static const int calibrationModulePage = -1;
    static const int drawRoiPage = 0;
    static const int runAnalysisPage = 1;
    static const int displacementsPage = 2;
    static const int postProcessingPage = 3;
    static const int exportPage = 4;

    static const int calibrationPage = -1;
    static const int rawPage = 0;
    static const int correlationPage = 1;



    explicit OpteCAL(int argc, char *argv[], QWidget *parent = 0);
    ~OpteCAL();

signals:
    void listOfMultipleFiles(QModelIndexList);

private slots:
    void resizeEvent(QResizeEvent *);
    void ShowContextMenu(const QPoint);
    void on_modulesToolBox_currentChanged(int index);
    bool on_actionSave_Project_triggered();
    void on_actionLoad_Project_triggered();

    void on_cartesianPolarComboBox_currentIndexChanged(int index);

    void displayColormap();
    void correctLensDistortion();
    void zoomEvent(float x, float y);
    void zoomingIn(int, int);
    void panEvent();

    void amplifiedMotion(bool val);


    void on_listFilesWidget_clicked(const QModelIndex);
    void on_listFilesCalWidget_clicked(const QModelIndex);
    void on_rawFilesWidget_clicked(const QModelIndex);

    void on_actionNew_Project_triggered();

    bool on_actionSave_Project_as_triggered();

    void closeEvent(QCloseEvent *event);

    void on_loadFilesToolBox_currentChanged(int index);

    void on_frameRateSpinBox_valueChanged(double arg1);

    void resizeFunctions();

    void on_actionLoad_calibration_images_triggered();

    void on_actionLoad_RAW_files_triggered();

    void on_actionLoad_experiment_images_triggered();

    void updateCorrelationFilesFolder(QString newCorrelFolder);

private:
    Ui::OpteCAL *ui;
    friend class roiModule;
     bool equalFiles(ifstream &in1, ifstream &in2);
     bool currentSettingsSaved();
     void loadSettingsFile();
     void licenseExpiredMsg();
};


#endif // OPTECAL_H
