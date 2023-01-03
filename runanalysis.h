#ifndef RUNANALYSIS_H
#define RUNANALYSIS_H

#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QListWidget>
#include <QList>
#include <QListWidgetItem>
#include <QDebug>
#include <QThreadPool>
#include <QtTest/QtTest>
#include <QMessageBox>
#include <QProgressDialog>
#include <QMenu>
#include <QSpinBox>


#include "drawshape.h"
#include "autoresize.h"
#include "filelist.h"
#include "qlabelwmouse.h"
#include "subsetsmap.h"
#include "drawseedpoint.h"
#include "interpcoef.h"
#include "nloptimizer.h"
#include "displacements.h"
#include "templatematch.h"

class runAnalysisModule : public QObject
{
    Q_OBJECT
    void displacementDisplay();
    cv::Matx23d computeInitialGuess(cv::Mat *imageToProcess, cv::Point2i &seedPoint);
    std::vector<nlOptimizer::subsetProperties> currentSubsetList;

public:

    runAnalysisModule(QLabelWMouse* imgDisplay, subsetsMap *subsetList,
                      autoResize* cam1Display, drawSeedPoint* seedLayer,
                      fileList *cam1Files, drawShape *roiShapes, displacements* dispFbk,
                      QLineEdit* subsetSizeText, QSlider* subsetSizeSlider,
                      QLineEdit* subsetSpacingText, QSlider* subsetSpacingSlider,
                      QPushButton* setSeedButton, QLineEdit *corrRejectionText,
                      QListWidget *correlationWidgetList);

    QLabelWMouse* imgDisplay;
    subsetsMap* subsetList;
    autoResize* cam1Display;
    drawSeedPoint* seedLayer;
    fileList* cam1Files;
    drawShape* roiShapes;
    QLineEdit* subsetSizeText;
    QSlider* subsetSizeSlider;
    QLineEdit* subsetSpacingText;
    QSlider* subsetSpacingSlider;
    QPushButton* setSeedButton;
    QLineEdit *corrRejectionText;
    QListWidget* correlationWidgetList;
    displacements* dispFbk;
    double imageResizeCoef;

    QTimer* timerInstance;
    QProgressDialog* pd;
    char* cancelled;
    int totalSubsetsSolved;
    std::vector<int> selectedFrames;
    bool analysisCanceled;

    bool referenceUpdated;
    int updatedReferenceIdx;

    static const int analysisCanceledFlag = 0;
    static const int analysisSuccess = 1;
    static const int refUpdateRequired = 2;

    void cancelLastSeed();
signals:
    void progressBarUpdate(int);

public slots:

    void on_subsetSizeSlider_valueChanged(int value);

    void on_subsetSizeText_editingFinished();

    void on_subsetSpacingText_editingFinished();

    void on_subsetSpacingSlider_valueChanged(int value);

    void on_setSeedButton_clicked();

    void quitDrawing();

    void Key_Pressed();

    void Mouse_current_pos();

    void Mouse_Pressed();

    void Mouse_Entered();

    int singleFrameAnalysis();

    void multipleFrameSelection(QModelIndexList val);

    void analyzeAllFrames();

    void cancel();

    void multipleFrame();

    void splineOrder(int val);

    void searchRegionBox(int val);

    void highStrainEnable(bool val);

    void intenseSearchEnable(bool val);

    void corrCoefRejection_Edited();

    void mouseRightClick(QPoint pos);

    void allCPUCheck(bool val);

    void stackSolutions();
};

#endif // RUNANALYSIS_H
