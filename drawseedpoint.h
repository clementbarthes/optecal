#ifndef DRAWSEEDPOINT_H
#define DRAWSEEDPOINT_H
#include <QDebug>

#include "subsetsmap.h"
#include "opencv2/opencv.hpp"
class drawSeedPoint
{

    subsetsMap * subsetList;
    cv::Mat previousImage;
    cv::Mat* imageToDraw;
    cv::Mat *fullSizeImage;
    cv::Mat seedMask;
    std::vector<cv::Point2i> seedPoint;
    float resizeCoef;
    bool isSeed;
    int currentPointNo;

    int interpDegree;

public:
    bool useAllCPU;
    bool intenseSearch;
    bool drawingSeedPoint;
    int searchBoxWidth;
    bool highStrainEnabled;
    int subsetSize;
    int subsetSpacing;
    double corrRejection;

    drawSeedPoint();
    ~drawSeedPoint();
    void setSubsetMap(subsetsMap * subsetList);
    void setRefImage(cv::Mat *refImage, float resizeCoef, cv::Mat *fullSizeImage);
    void updateSeedPoint(cv::Point2i *currentPoint);
    void updateCurrentSeedPoint(cv::Point2i *currentPoint);
    void setSeedPoint();
    void updateDrawing();
    void setSeedExist(bool seedBool);
    bool getSeedExist();
    bool seedInRoi(cv::Mat *roiMask, int seedPt = -1);
    std::vector<cv::Point2i>  getSeed();
    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);

    void checkSeed(cv::Mat *roiMask);
    void clear();
    int isMouseNearPoint(cv::Point2i *currentPoint);

    void deleteCurrentSeedPoint();

    void setInterpDegree(int val);
    int getInterpDegree();



    void deleteLastSeedPoint();
private:
    void seedShape(cv::Point2i seedPoint);
};

#endif // DRAWSEEDPOINT_H
