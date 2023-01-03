#ifndef POSTPROCESSINGMODULE_H
#define POSTPROCESSINGMODULE_H

#include "virtualmeasurementtools.h"
#include "filelist.h"
#include "displacements.h"
#include "qlabelwmouse.h"
#include "draworigin.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QListWidget>
#include <QObject>
#include <QPushButton>
#include <QDebug>

class postProcessingModule : public QObject
{
    Q_OBJECT
    QListWidget* strainGaugeList;
    QListWidget* extensometerList;
    QPushButton* addStrainGaugeButton;
    QPushButton* addExtensometerButton;
    QLabelWMouse* imgDisplay;
    autoResize* cam1Display;
    fileList* correlationFiles;
    displacements* dispFbk;
    virtualMeasurementTools* virtualTools;
    drawOrigin *originAndAxesLayer;
    float imageResizeCoef;
    bool *licenseValidated;



public:


    explicit postProcessingModule(QListWidget* strainGaugeList, QListWidget* extensometerList,
                                  QPushButton* addStrainGauge, QPushButton *addExtensometerButton,
                                  QLabelWMouse *imgDisplay, autoResize* cam1Display, displacements* dispFbk,
                                  fileList* correlationFiles, virtualMeasurementTools* virtualTools,
                                  drawOrigin *originAndAxesLayer, bool *licenseValidated);

    void deleteStrainGauge(int idx);
    void deleteExtensometer(int idx);

signals:

public slots:
    void addStrainGaugeClicked();
    void addExtensometerClicked();
    void exportButton();

    void strainGaugeListRowChanged(int idx);
    void extensometerListRowChanged(int idx);

    void Mouse_current_pos();
    void Mouse_Entered();
    void Mouse_Pressed();
    void Key_Pressed();


    void on_customContextMenuRequested(const QPoint &pos);
    void on_customContextExtensometer(const QPoint &pos);

    void exportCanceled();
};

#endif // POSTPROCESSINGMODULE_H
