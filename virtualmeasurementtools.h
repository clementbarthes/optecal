#ifndef VIRTUALMEASUREMENTTOOLS_H
#define VIRTUALMEASUREMENTTOOLS_H

#include <QList>
#include <QDir>
#include <QObject>
#include <QListWidgetItem>
#include <QLabel>
#include <QFileDialog>
#include <fstream>
#include <QApplication>
#include <QProgressDialog>

#include "autoresize.h"
#include "displacements.h"
#include "draworigin.h"
#include "filelist.h"
#include "mat.h"
#include "math.h"
#include "opencv2/opencv.hpp"

class virtualMeasurementTools
{
    autoResize *cam1Display;
    cv::Mat previousImage;
    cv::Mat toolsMask;
    cv::Mat strainGaugeMask;
    cv::Mat* imageToDraw;
    displacements dispSol;
    drawOrigin originAndAxesLayer;
    QDir rootFolder;
    float imgResizeCoef;
    static const int vectorLength = 120;

    QLabel* e11Label;
    QLabel* e12Label;
    QLabel* e22Label;
    QLabel* elongationLabel;
    QLabel* elongationXLabel;
    QLabel* elongationYLabel;
    QLabel *sgWidthLabel, *sgHeightLabel, *sgCenterLabel, *sgAngleLabel;
    QLabel *extPointsLabel, *extLengthLabel;
    QString unitLabel;

    cv::Mat maskDouble;
    cv::Mat dispU, dispV, coordX, coordY;
    cv::Mat Exx, Exy, Eyy;
    calibration* cam1Calibration;

public:

    static const int mouseNearCenter = 1;
    static const int mouseNearVector = 2;
    static const int mouseNearCorner = 3;
    static const int mouseNearExtensometer = 4;

    struct strainGauge{
        QListWidgetItem* name;
        cv::Point2i center;
        int width;
        int height;
        double angle;
    };

    struct extensometer{
        QListWidgetItem* name;
        std::vector<cv::Point2i> points;
    };

    std::vector<strainGauge> strainGaugeList;
    std::vector<extensometer> extensometerList;

    int currentStrainGauge;
    int currentExtensometer;
    double angleSet;

    cv::Point2i pointGrabbed;
    int pointGrabbedIdx;
    bool strainGaugeDrawingCenter;
    bool strainGaugeDrawingWidth;
    bool extensometerDrawingInProgress;

    bool updateCenterInProgress;
    bool updateWidthInProgress;
    bool updateAngleInProgress;
    bool updateExtensometerInProgress;

    bool exportCanceled;
    QProgressDialog* pd;

    virtualMeasurementTools();
    void addStrainGauge();
    void addExtensometer();

    // Set root path
    void setRootPath(QDir rootFolder);
    // Defines the display box
     void setDisplayFrame(autoResize *cam1Display);

    // Defines background image
    void setImage(cv::Mat* image, float imgResizeCoef);

    // Get calibration pointer
    void setCalibPointer(calibration* cam1Calibration);

    // Set labels
    void setLabels(QLabel* e11Label, QLabel* e12Label, QLabel* e22Label,
                   QLabel* elongationLabel, QLabel* elongationXLabel, QLabel* elongationYLabel,
                   QLabel *sgWidthLabel, QLabel *sgHeightLabel, QLabel *sgCenterLabel, QLabel *sgAngleLabel,
                   QLabel *extPointsLabel, QLabel *extLengthLabel);

    // Update the image resize coefficient
    void setImageResizeCoef(float imgResizeCoef);

    // Updates the position of a specified point based on mouse position
    void updateCenter(cv::Point2i *currentPoint);

    void updateWidth(cv::Point2i *currentPoint);

    void updateAngle(cv::Point2i *currentPoint);

    void addExtensometerPoint(cv::Point2i *currentPoint);

    void updateExtensometer(cv::Point2i *currentPoint);

    void updateSolutionMap(drawOrigin* originAndAxesLayer,
                           int currentImg, fileList* correlationFiles);

    // Updates the drawing
    void updateDrawing();

    void deleteStrainGauge(int idx);
    void deleteExtensometer(int idx);

    int isMouseNearPoint(cv::Point2i *currentPoint);

    void setExtensometerPoint();
    void exportResults(fileList *correlationFiles, drawOrigin *originAndAxesLayer);

    void loadDispAndCoords();

    std::vector<double> computeExtensometerResults(extensometer extensometerComputed);
    std::vector<double> computeStrainGaugeResults(strainGauge computedStrainGauge);


    void clear();
    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);


private:
    void drawStrainGauge(int strainGaugeIdx);
    void drawExtensometer(int extensometerIdx);
    void drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color);


    double convertToUnits();
};

#endif // VIRTUALMEASUREMENTTOOLS_H
