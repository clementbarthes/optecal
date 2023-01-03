#ifndef FILELISTCORRELATIONPAGE_H
#define FILELISTCORRELATIONPAGE_H
#include <QTimer>

#include "filelistpage.h"
#include "drawshape.h"
#include "drawseedpoint.h"
#include "draworigin.h"
#include "virtualmeasurementtools.h"

class fileListCorrelationPage : public fileListPage
{
    Q_OBJECT

    drawShape* roiShapes;
    drawSeedPoint* seedLayer;
    drawOrigin* originAndAxesLayer;
    virtualMeasurementTools *virtualTools;


    //static const int calibrationModulePage = 0;
    static const int drawRoiPage = 0;
    static const int runAnalysisPage = 1;
    static const int displacementsPage = 2;
    static const int postProcessingPage = 3;
    static const int exportPage = 4;



public:
    fileListCorrelationPage(QFileDialog* loadImages, QListWidget* listFilesWidget,
                            autoResize* cam1Display, fileList* imageFiles,
                            drawShape* roiShapes, drawSeedPoint* seedLayer,
                            drawOrigin* originAndAxesLayer, virtualMeasurementTools* virtualTools);

    QTimer *playAnimTimer;
    double fps;
    int modulesToolBoxIndex;
    bool refLoaded;
signals:
    void enablePlusShapes(bool val);
    void enableMinusShapes(bool val);
    void updateDisplay();

public slots:
    void on_listFilesWidget_currentRowChanged(int currentRow);
    void on_modulesToolBoxIndex(int index);
    void pause_Button();
    void play_Button();
    void playAnimation();
};

#endif // FILELISTCORRELATIONPAGE_H
