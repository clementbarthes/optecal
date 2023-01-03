#ifndef ROIMODULE_H
#define ROIMODULE_H
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QMenu>
#include <QListWidget>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifndef WIN32
#include <netinet/in.h>
#else
#include <sys/utime.h>
#include <winsock2.h>
#endif
#include <libraw/libraw.h>


#include "drawshape.h"
#include "autoresize.h"
#include "qlabelwmouse.h"
#include "filelist.h"
#include "calibration.h"



class roiModule: public QObject
{
    Q_OBJECT
    QLabelWMouse* imgDisplay;
    QPushButton* plusPolyButton;
    QPushButton* minusPolyButton;
    QPushButton* plusCircleButton;
    QPushButton* minusCircleButton;
    drawShape* roiShapes;
    autoResize* cam1Display;
    fileList* rawFiles;
    fileList *correlationFiles;

    calibration* cam1Calibration;
    QLineEdit* pixelsText;
    QLineEdit* unitText;
    drawShape* measureToolShape;
    QPushButton* measureButton;
    QLabel* pixelEURatioLabel;
    QListWidget *fileListWidget;

    float imageResizeCoef;

public:
    roiModule(QLabelWMouse* imgDisplay,
              QPushButton* plusPolyButton,
              QPushButton* minusPolyButton,
              QPushButton* plusCircleButton,
              QPushButton* minusCircleButton,
              QLineEdit *pixelsText, QLineEdit *unitText,
              drawShape *measureToolShape,
              QPushButton *measureButton, QLabel *pixelEURatioLabel, calibration *cam1Calibration,
              drawShape* roiShapes,
              autoResize* cam1Display, fileList *correlationFiles,
              fileList* rawFiles, QListWidget *fileListWidget);

public:
    void displayScale();
    void cancelDrawing();
public slots:
    void plusPoly();
    void minusPoly();
    void plusCircle();
    void minusCircle();

    void pixelLineEdited();
    void unitsLineEdited();
    void unitChanged(int val);
    void applyScale();
    void measureTool();

    void Mouse_current_pos();

    void Mouse_Entered();

    void Mouse_Pressed();

    void Mouse_DoubleClick();

    void Key_Pressed();

    void roiIsDrawn();

    void convertToTiff();

    void mouseRightClick(QPoint pos);
private:
    void releaseDrawingButtons();
    void setCursorStyle(int isNear);
    void releaseMeasureTool();
};

#endif // ROIMODULE_H
