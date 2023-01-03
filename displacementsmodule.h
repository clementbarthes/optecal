#ifndef DISPLACEMENTSMODULE_H
#define DISPLACEMENTSMODULE_H
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QElapsedTimer>

#include "math.h"

#include "qlabelwmouse.h"
#include "displacements.h"
#include "calibration.h"
#include "autoresize.h"
#include "filelist.h"
#include "drawshape.h"
#include "draworigin.h"



class displacementsModule: public QObject
{
    Q_OBJECT
    QLabelWMouse* currentImgDisplay;
    displacements* dispFbk;
    QLineEdit* lowerBoundText;
    QLineEdit* upperBoundText;
    QLineEdit* clippingValText;
    QLineEdit *amplificationText;
    QLineEdit *backgroundText;
    autoResize* cam1Display;
    autoResize* scaleDisplay;
    drawOrigin* originAndAxesLayer;
    calibration *cam1Calibration;
    fileList* cam1Files;
    QLabel *lowBoundLabel;
    drawShape* roiShapes;
    int minSliderBar;
    int maxSliderBar;
    int dataIdx;  // 0: U, 1: V, 2: Rotation 3: Exx, 4: Eyy, 5: Exy, 6: Correl. coef.
    // 7: X, 8: Y, 9: PS1, 10: PS2, 11: PD1, 12:PD2
    //13: VM, 14: Tresca, 15: Mask, 16: Amplified motion
    int scaleVal; // 0: manual scale, 1: auto

    double upperBound;
    double lowerBound;

    // Current index value of the displayed image
    int currentImIndex;

    //Coef between full scale and displayed image
    float imageResizeCoef;    

    // Display matrices
    cv::Mat prevIm;
    cv::Mat* currentIm;
    cv::Mat correlCoefMat;
    cv::Mat results;

    //col 0: min bound, col 1: max bound
    double lowUpBounds[15][2];

    // Number of values on the slider scales
    static const int sliderNumberVal = 500;

    void drawScale(double minVal, double maxVal, int dataIdx);

    cv::Mat computeColorMap();


    bool openSolutionFile(int val, displacements* dispSol);
public:
    bool solutionLoaded;

    displacementsModule(QLabelWMouse *currentImgDisplay, autoResize *cam1Display,
                        autoResize *scaleDisplay, fileList *cam1Files,
                        displacements *dispFbk, drawShape *roiShapes,
                        drawOrigin *originAndAxesLayer, calibration *cam1Calibration,
                        QLineEdit *lowerBoundText, QLineEdit *upperBoundText, QLineEdit *clippingValText,
                        QLineEdit *amplificationText, QLineEdit *backgroundText);

    void displacementDisplay();
    void loadFormatAndDisplay();
    int getDataIdx();

private:
    double convertToUnits(double val);
    double convertToPixels(double val);
public slots:
    void loadSolFromFile(int val);
    void lowerBoundSliderChanged(int val);
    void upperBoundSliderChanged(int val);
    void lowerBoundSliderMovedByUser(int val);
    void upperBoundSliderMovedByUser(int val);
    void amplificationMovedByUser(int val);
    void backgroundMovedByUser(int val);
    void dispComboBoxChanged(int val);
    void medianFilterChanged(int val);
    void gaussianFilterChanged(int val);
    void clippingChanged(int val);
    void lowerBoundEdited();
    void upperBoundEdited();
    void amplificationEdited();
    void backgroundEdited();
    void clippingValEdited();
    void scaleAuto(int val);
    void onShowAxes(bool val);

    void Mouse_current_pos();
    void Mouse_Entered();
    void Mouse_Pressed();
    void setCursorStyle(int isNear);
    void onFlipXY(bool val);
    void unitsChanged(int val);
    void onCartPolarCoord(int val);
    void colormapSlider(int val);
    void referenceRadio(bool val);
    void spatialRadio(bool val);
signals:
    void editLowerBoundText(QString val);
    void editUpperBoundText(QString val);
    void editAmplificationText(QString val);
    void editBackgroundText(QString val);
    void setLowerBoundSlider(int val);
    void setUpperBoundSlider(int val);
    void setAmplificationSlider(int val);
    void setBackgroundSlider(int val);
    void setCorrCoefSlider(int val);
    void setScaleComboBox(int val);
    void setUnitsComboBox(int val);
    void loadRefImage(int idx);
    void amplifiedMotionBox(bool val);

};

#endif // DISPLACEMENTSMODULE_H
