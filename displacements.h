#ifndef DISPLACEMENTS_H
#define DISPLACEMENTS_H

#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QtAlgorithms>

#include <stdlib.h>
#include <math.h>
#include "opencv2/opencv.hpp"

#include "filelist.h"
#include "autoresize.h"
#include "draworigin.h"
#include "drawshape.h"
#include "calibration.h"
#include "subsetsmap.h"
#include "nloptimizer.h"

class displacements
{
    std::vector<cv::Point2i> subsetPts;
    // Results stored in matrix format, each value (or pixel) corresponds to a subset value
    cv::Mat correlCoef;
    cv::Mat dispU;
    cv::Mat dispV;
    cv::Mat rotation;
    cv::Mat coordX;
    cv::Mat coordY;
    cv::Mat Exx;
    cv::Mat Eyy;
    cv::Mat Exy;
    cv::Mat exx;
    cv::Mat eyy;
    cv::Mat exy;
    cv::Mat mask;
    cv::Mat warp00,warp01,warp02,warp10,warp11,warp12;

    // User-defined displacements and strains
    cv::Mat dispUUser;
    cv::Mat dispVUser;
    cv::Mat E11User; // Exx if cartesian, Err if polar
    cv::Mat E22User; // Eyy if cartesian, Ett if polar
    cv::Mat E12User; // Exy if cartesian, Ert if polar
    cv::Mat EP1User; // Principal strain 1
    cv::Mat EP2User; // Principal strain 2
    cv::Mat ED1User; // Principal dir. 1
    cv::Mat ED2User; // Principal dir. 2
    cv::Mat EVM; // Von-Mises strain
    cv::Mat ETresca; // Tresca strain

    cv::Mat xRemap, yRemap;
    cv::Mat coordXUser;
    cv::Mat coordYUser;
    cv::Mat rotationOutput;

    fileList *imageFiles;


public:

    int subsetSize;
    int subsetSpacing;
    int medianFilterValue;
    int gaussianFilterValue;

    // Results resized to display resolution
    cv::Mat xResized;
    cv::Mat yResized;
    cv::Mat uResized;
    cv::Mat vResized;
    cv::Mat exxResized;
    cv::Mat eyyResized;
    cv::Mat exyResized;
    cv::Mat corrCoefResized;
    cv::Mat maskResized;
    cv::Mat maskDisplay; // (Same than maskResized, but adjusted based on the user defined clipping coefficient)
    cv::Mat maskDisplayRemap;
    cv::Mat resultsRemap;
    // Post-processed result matrix
    cv::Mat results;

    // Clipping correlation coefficient
    double correlClipVal;
    // Current index value of the displayed image
    int currentImIndex;

    //col 0: min value, col 1: max value
    double autoBounds[15][2];

    static const int getU = 0;
    static const int getV = 1;
    static const int getRot = 2;
    static const int getExx = 3;
    static const int getEyy = 4;
    static const int getExy = 5;
    static const int getPS1 = 6;
    static const int getPS2 = 7;
    static const int getPD1 = 8;
    static const int getPD2 = 9;
    static const int getVM = 10;
    static const int getTresca = 11;
    static const int getCorr = 12;
    static const int getX = 13;
    static const int getY = 14;
    static const int getAmplified = 15;
    static const int getMask = 16;



    //


    displacements();
    ~displacements();

    // Copy constructor, only copies the processing infos (auto/manual scale, min max etc...)
    displacements& operator=( const displacements& other );
    // Compute the displacements and strain fields from the results of the correlation (warp parameters->disp and strain parameters)
    void addSolution(int subsetSpacing, cv::Mat* currentImage,std::vector<nlOptimizer::subsetProperties> solution);

    // Returns the solution in a matrix form, with one value per subset
    cv::Mat getResults(int solFlag);

    // Returns the warp at a given location
    cv::Matx23d getWarp(int row, int col);

    // Get the correlation coef. at a given collection
    double getCorrCoef(int row, int col);

    // Returns the location of the subset points
    std::vector<cv::Point2i> getResultsPts();

    // Returns the coordinate (X or Y) of each subset based on the user defined coordinate system, resized to the displayed image size
    cv::Mat computeUserCoords(drawOrigin &originAndAxesLayer, int getCoordFlag);
    // Returns the displacements (U or V) of each subset based on the user defined coordinate system, resized to the displayed image size
    cv::Mat computeUserDisplacements(drawOrigin &originAndAxesLayer, int getDispFlag);
    // Returns the rotation of each subset
    cv::Mat computeRotation(drawOrigin &originAndAxesLayer);
    // Returns the strain (Exx,Eyy or Exy) of each subset based on the user defined coordinate system, resized to the displayed image size
    cv::Mat computeUserStrains(drawOrigin &originAndAxesLayer, int getStrainFlag);
    // Returns the principal strains, resized to the displayed image size
    cv::Mat computePrincipalStrains(drawOrigin &originAndAxesLayer, int getStrainFlag);
    // Returns Tresca or Von-Mises strain, resized to the displayed image size
    cv::Mat computeTrescaVMStrains(int getStrainFlag);

    // Updates the resized solution members (xResized, yResized etc..) such that the solution matrix is of the size of the displayed image
    void createResizedSolution(cv::Mat currentIm);

    // Updates the displayed solution matrix with a custom mask based on user defined Correl. coef. clipping value. Also computes the min and max
    // values of the solution for the auto-scale
    void computeMaskAndLimits(int dataIdx, drawOrigin *originAndAxesLayer);

    // Remap the results matrix
    void remapResultsAndMask(float mapAmplification, drawOrigin *originAndAxesLayer);

    // Builds a color map based on the solution defined with computeMaskAndLimits
    cv::Mat computeColorMap(int dataIdx, float imageResizeCoef, drawOrigin *originAndAxesLayer);

    // Returns an image with the colorbar
    cv::Mat drawScale(int dataIdx, drawOrigin *originAndAxesLayer, calibration *cam1Calibration);


    // Returns true if displacements is empty
    bool isEmpty();

    // Serialization functions
    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);


    // Opens a solution file associated with an image and updates the displacements object
    static bool openSolutionFile(int val, fileList *correlationFiles ,displacements *dispSol);



    void clear();

private:
    void buildStrains();
    void extendEdges(cv::Mat &image);
};

#endif // DISPLACEMENTS_H
