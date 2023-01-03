#ifndef SUBSETSMAP_H
#define SUBSETSMAP_H
#include "QDebug"
#include "opencv2/opencv.hpp"
#include "nloptimizer.h"
#include "stdlib.h"
class subsetsMap
{
    cv::Mat* roiMask;

    int subsetSpacing;
    int subsetSize;
    int subsetHalf;
    bool solvePoorConvergenceContainer;


public:

    std::vector<nlOptimizer::subsetProperties> subsetList;

    subsetsMap();
    ~subsetsMap();
    void setRoiMask(cv::Mat* loadRoiMask);
    void setSubsetSize(int newSize);
    int getSubsetSize();
    int getSubsetHalf();

    void setSubsetSpacing(int newSpacing);
    int getSubsetSpacing();
    void allocateNextBatch(std::vector<nlOptimizer::subsetProperties> &currentSubsetList);
    void setPoorConvergenceContainer(bool val);
    bool getPoorConvergenceContainer();
};

#endif // SUBSETSMAP_H
