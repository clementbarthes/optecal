#ifndef CALIBRATIONMODULE_H
#define CALIBRATIONMODULE_H


#include <QObject>
#include <QDebug>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "qlabelwmouse.h"
#include "calibration.h"
#include "autoresize.h"

class calibrationModule : public QObject
{
    Q_OBJECT

    calibration* cam1Calibration;

    QLineEdit* pixelsText;
    QLineEdit* unitText;
    QLineEdit *cropFactorEdit, *aCal, *bCal, *cCal;

    autoResize* cam1Display;
    QLabelWMouse* imgDisplay;
    QLabel* pixelEURatioLabel;
    bool lensCorrectionOn;

    float imageResizeCoef;




private:


public:
    explicit calibrationModule(calibration *cam1Calibration,
                                autoResize *cam1Display, QLabelWMouse *imgDisplay,
                               QLineEdit *cropFactorEdit, QLineEdit *aCal, QLineEdit *bCal, QLineEdit *cCal);


signals:
    void scaleFactorLabel(QString);
    void cropFactor(QString);
    void calA(QString);
    void calB(QString);
    void calC(QString);

public slots:

    void updateDistortionCorrection();
    void cameraMakerChanged(int val);
    void cameraModelChanged(int val);
    void lensMakerChanged(int val);
    void lensModelChanged(int val);
    void focalLengthChanged(int val);

    void cropFactorEdited();
    void aCalEdited();
    void bCalEdited();
    void cCalEdited();
    void enableLensCorrection(bool val);


    void Mouse_current_pos();
    void Mouse_Entered();
    void Mouse_Pressed();
    void Key_Pressed();


};

#endif // CALIBRATIONMODULE_H
