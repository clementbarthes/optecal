#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QtWidgets/QMessageBox>
#include <QApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <QFile>
#include <QString>
#include <QComboBox>
#include <QXmlStreamReader>


#include <iostream>
#include <string>

#include "filelist.h"
class calibration
{
private:
   std::vector<std::vector<cv::Point3f> > m_objectPoints;
   std::vector<std::vector<cv::Point2f> > m_imagePoints;

   QComboBox *cameraMakerWidget, *cameraWidget, *lensMakerWidget,
   *lensWidget, *focalLengthWidget;

   fileList *calibrationFiles;

   //Square Length
   float m_squareLength;

   //output Matrices
   cv::Mat m_cameraMatrix; //intrinsic
   cv::Mat m_distCoeffs;

   //flag to specify how calibration is done
   int m_flag;


   //used in image undistortion
   cv::Mat m_map1,m_map2;


   bool m_mustInitUndistort;
   bool m_found;





public:
    calibration();

    struct camera {
        QString name;
        double cropFactor;
        bool operator==(const camera& rhs) const
        {
            return name == rhs.name;
        }
    };

    struct lensProperties{
        double focalLength;
        double a;
        double b;
        double c;
    };

    struct lensLabResult{
        double cropFactor;
        std::vector<lensProperties> lensProps;
    };

    struct lens{
        QString name;
        std::vector<lensLabResult> lensLab;
        bool operator==(const lens& rhs) const
        {
            return name == rhs.name;
        }
    };


    struct maker {
        QString name;
        std::vector<camera> cameraList;
        std::vector<lens> lensList;
        bool operator==(const maker& rhs) const
        {
            return name == rhs.name;
        }
    };

    std::vector<maker> cameraMakerList;
    std::vector<maker> lensMakerList;

    void parseMakerLists();
    void parseCameraList(int makerIdx);
    void parseLensList(int makerIdx);
    void parseFocalLengthList(int modelIdx);

    double pxLine;
    double unitLine;
    double mmPerPixel;
    double ratioDisplayed;
    int unitFlag;

    static const int mmUnit = 0;
    static const int cmUnit = 1;
    static const int mUnit = 2;
    static const int inUnit = 3;
    static const int ftUnit = 4;

private:
    // Returns maker index if it exists in makerList. Returns -1 otherwise
    int makerExists(QString name, std::vector<maker> &makerList);
    int cameraExists(QString name, int makerIdx);
    int lensExists(QString name, int makerIdx);

    lensProperties  getLensDistortion( QXmlStreamReader &xmlStream);

public:

    int getBestLensLab();

    void parseCalibrationElement(std::vector<maker> &makerList, QXmlStreamReader &xmlStream, bool cameraLensBar);

    void loadLensFunDatabase();

    void remap(const cv::Mat &image, cv::Mat &undistorted);

    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);

    void setComboBoxes(QComboBox *cameraMakerWidget, QComboBox *cameraWidget,
                       QComboBox *lensMakerWidget, QComboBox *lensWidget,
                       QComboBox *focalLengthWidget);
    void enableComboBoxes(bool val);

    int getCameraMakerIdx();
    int getCameraIdx();
    int getLensMakerIdx();
    int getLensIdx();
    int getFocalLengthIdx();

    bool isCameraCustom();
    bool isLensCustom();

    void setCameraCustom(double val);
    void setLensCustom(double aVal, double bVal, double cVal);

    struct {
        bool operator()(maker a, maker b)
        {
            return a.name <= b.name;
        }
    } compareNames;

    struct {
        bool operator()(camera a, camera b)
        {
            return a.name <= b.name;
        }
    } compareCameraNames;

    struct {
        bool operator()(lens a, lens b)
        {
            return a.name <= b.name;
        }
    } compareLensNames;

    struct {
        bool operator()(QString a, QString b)
        {
            return a.size() <= b.size();
        }
    } compareLength;

};

#endif // CALIBRATION_H
