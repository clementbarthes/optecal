#include "subsetsmap.h"


subsetsMap::subsetsMap()
{
    solvePoorConvergenceContainer = false;
}

subsetsMap::~subsetsMap()
{
    subsetList.clear();
}

void subsetsMap::allocateNextBatch(std::vector<nlOptimizer::subsetProperties>&currentSubsetList)
{
    nlOptimizer::subsetProperties newSubset;

    /// Append the solution
    subsetList.insert(subsetList.end(), currentSubsetList.begin(), currentSubsetList.end());

    //qDebug()<< "Size of current Subset list:" << currentSubsetList.size() << endl;

    /// Allocate next batch of subsets
    cv::Point2i ptNeighbour[8];
    std::vector<nlOptimizer::subsetProperties> prevSubsetList = currentSubsetList;


    currentSubsetList.clear();



    for(std::vector<nlOptimizer::subsetProperties>::iterator prevPtr=prevSubsetList.begin();
        prevPtr != prevSubsetList.end(); ++prevPtr){
        if((*prevPtr).converged == nlOptimizer::CONVERGED
                || (solvePoorConvergenceContainer  && (*prevPtr).converged == nlOptimizer::POOR_CONVERGENCE))
        {
            roiMask->at<cv::Vec3b>(cv::Point2i((*prevPtr).center.x/subsetSpacing,
                                               (*prevPtr).center.y/subsetSpacing))[0] = 0;
        }
    }
    // Temporary roiMask to avoid picking the same subset twice
    cv::Mat roiMaskTemp;
    roiMask->copyTo(roiMaskTemp);
    for(std::vector<nlOptimizer::subsetProperties>::iterator prevPtr=prevSubsetList.begin();
        prevPtr != prevSubsetList.end(); ++prevPtr){
        if((*prevPtr).converged == nlOptimizer::CONVERGED
                || (solvePoorConvergenceContainer  && (*prevPtr).converged == nlOptimizer::POOR_CONVERGENCE))
        {
            //Define neighbouring points
            // Left point
            ptNeighbour[0].x = (*prevPtr).center.x-subsetSpacing; ptNeighbour[0].y = (*prevPtr).center.y;
            // Top point
            ptNeighbour[1].x = (*prevPtr).center.x; ptNeighbour[1].y = (*prevPtr).center.y-subsetSpacing;
            // Right point
            ptNeighbour[2].x = (*prevPtr).center.x+subsetSpacing; ptNeighbour[2].y = (*prevPtr).center.y;
            // Bottom point
            ptNeighbour[3].x = (*prevPtr).center.x; ptNeighbour[3].y = (*prevPtr).center.y+subsetSpacing;

            //Top Left point
            ptNeighbour[4].x = (*prevPtr).center.x-subsetSpacing; ptNeighbour[4].y = (*prevPtr).center.y-subsetSpacing;
            // Top  right point
            ptNeighbour[5].x = (*prevPtr).center.x+subsetSpacing; ptNeighbour[5].y = (*prevPtr).center.y-subsetSpacing;
            // Bottom right point
            ptNeighbour[6].x = (*prevPtr).center.x+subsetSpacing; ptNeighbour[6].y = (*prevPtr).center.y+subsetSpacing;
            // Bottom left point
            ptNeighbour[7].x = (*prevPtr).center.x-subsetSpacing; ptNeighbour[7].y = (*prevPtr).center.y+subsetSpacing;

            for(int i = 0 ; i<8; ++i){
                //Check if point is within bounds
                cv::Point2i ptNeighbourOverSubsetSpacing = cv::Point2i(ptNeighbour[i].x/subsetSpacing, ptNeighbour[i].y/subsetSpacing);
                if((0 <= ptNeighbourOverSubsetSpacing.x) && (ptNeighbourOverSubsetSpacing.x <= roiMask->cols) &&
                        ( 0<= ptNeighbourOverSubsetSpacing.y) && (ptNeighbourOverSubsetSpacing.y/subsetSpacing <= roiMask->rows)){
                    // Check if point belongs to ROI or if it has been already called
                    if(roiMaskTemp.at<cv::Vec3b>(ptNeighbourOverSubsetSpacing)[0] != 0){
                        // If accepted, remove the point from the ROI
                        roiMaskTemp.at<cv::Vec3b>(ptNeighbourOverSubsetSpacing)[0] = 0;
                        // then use the warp of the parent point as an initial guess
                        newSubset.center = ptNeighbour[i];
                        newSubset.warp = prevPtr->warp;
                        newSubset.converged = nlOptimizer::NO_CONVERGENCE;
                        currentSubsetList.push_back(newSubset);
                    }
                }
            }
        } else {

            qDebug() << "Didn't converge";
        }

    }
    prevSubsetList.clear();
    roiMaskTemp.release();
}


void subsetsMap::setRoiMask(cv::Mat *loadRoiMask)
{
    roiMask = loadRoiMask;
}


void subsetsMap::setSubsetSize(int newSize)
{
    subsetSize = newSize;
    subsetHalf = subsetSize/2;
}

int subsetsMap::getSubsetSize()
{
    return subsetSize;
}

int subsetsMap::getSubsetHalf()
{
    return subsetHalf;
}

void subsetsMap::setSubsetSpacing(int newSpacing)
{
    subsetSpacing = newSpacing;
}

int subsetsMap::getSubsetSpacing()
{
    return subsetSpacing;
}

void subsetsMap::setPoorConvergenceContainer(bool val)
{
    solvePoorConvergenceContainer = val;
}

bool subsetsMap::getPoorConvergenceContainer()
{
    return solvePoorConvergenceContainer;
}
