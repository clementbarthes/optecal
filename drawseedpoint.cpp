#include "drawseedpoint.h"

drawSeedPoint::drawSeedPoint()
{
    interpDegree = 5;
    subsetSize = 45;
    subsetSpacing = 13;
    searchBoxWidth = 500;
    corrRejection = 0.1;
    drawingSeedPoint = false;
    highStrainEnabled = false;
    intenseSearch = false;
}

drawSeedPoint::~drawSeedPoint()
{
    previousImage.release();
    seedMask.release();
    seedPoint.clear();
}

void drawSeedPoint::setSubsetMap(subsetsMap *subsetList)
{
    this->subsetList = subsetList;
    isSeed = false;
    drawingSeedPoint = false;
}

void drawSeedPoint::setRefImage(cv::Mat *refImage, float resizeCoef,
                                cv::Mat *fullSizeImage)
{
    this->resizeCoef = resizeCoef;
    this->fullSizeImage = fullSizeImage;
    previousImage = refImage->clone();
    imageToDraw = refImage;
    seedMask = cv::Mat::zeros(imageToDraw->rows,
                              imageToDraw->cols,imageToDraw->type());
}

void drawSeedPoint::updateSeedPoint(cv::Point2i *currentPoint)
{
    seedPoint.back() =  *currentPoint;
}

void drawSeedPoint::updateCurrentSeedPoint(cv::Point2i *currentPoint){

    seedPoint[currentPointNo] =  *currentPoint;
}

void drawSeedPoint::deleteCurrentSeedPoint(){
    seedPoint.erase(seedPoint.begin()+currentPointNo);
    if(isSeed){
    seedMask = cv::Mat::zeros(imageToDraw->rows,
                              imageToDraw->cols,imageToDraw->type());

    //std::vector<cv::Point2i>::iterator seedIter = seedPoint.begin();
    for(int j=0; j < ((int)seedPoint.size()-1);++j)
    {
        seedShape(seedPoint[j]);
    }
        seedShape(seedPoint.back());
        cv::add(previousImage,seedMask,*imageToDraw);
    }
    if(seedPoint.empty())
        isSeed = false;
}

void drawSeedPoint::deleteLastSeedPoint(){
    seedPoint.pop_back();
    if(isSeed){
    seedMask = cv::Mat::zeros(imageToDraw->rows,
                              imageToDraw->cols,imageToDraw->type());

    //std::vector<cv::Point2i>::iterator seedIter = seedPoint.begin();
    for(int j=0; j < ((int)seedPoint.size()-1);++j)
    {
        seedShape(seedPoint[j]);
    }
        seedShape(seedPoint.back());
        cv::add(previousImage,seedMask,*imageToDraw);
    }
    if(seedPoint.empty())
        isSeed = false;
}

void drawSeedPoint::setInterpDegree(int val)
{
    interpDegree = val;
}

int drawSeedPoint::getInterpDegree()
{
    return interpDegree;
}


void drawSeedPoint::setSeedPoint()
{
    seedPoint.push_back(cv::Point2i(0,0));

}

void drawSeedPoint::updateDrawing()
{


    if(isSeed){
    seedMask = cv::Mat::zeros(imageToDraw->rows,
                              imageToDraw->cols,imageToDraw->type());

    //std::vector<cv::Point2i>::iterator seedIter = seedPoint.begin();
    for(int j=0; j < ((int)seedPoint.size()-1);++j)
    {
        seedShape(seedPoint[j]);
    }

        seedShape(seedPoint.back());
        cv::add(previousImage,seedMask,*imageToDraw);
    }

}

void drawSeedPoint::setSeedExist(bool seedBool)
{
    isSeed = seedBool;
}

bool drawSeedPoint::getSeedExist()
{
    return isSeed;
}

bool drawSeedPoint::seedInRoi(cv::Mat* roiMask, int seedPt)
{
    if(seedPt == -1){
        if(roiMask->at<cv::Vec3b>(seedPoint.back()*(1./resizeCoef))[0] == 0)
            return false;
    }else {
        if(roiMask->at<cv::Vec3b>(seedPoint[seedPt]*(1./resizeCoef))[0] == 0)
            return false;
    }
    return true;
}


void drawSeedPoint::checkSeed(cv::Mat* roiMask)
{

    if(roiMask->at<cv::Vec3b>(seedPoint.back()*(1./resizeCoef))[0] == 0){
        seedPoint.pop_back();
        if(seedPoint.empty()) isSeed = false;
    }
}

int drawSeedPoint::isMouseNearPoint(cv::Point2i *currentPoint){
    currentPointNo = -1;
    int distance;
    double epsilon = 5.*resizeCoef;
    if(!drawingSeedPoint){
        int jIndex = 0;
        for(std::vector<cv::Point2i>::iterator j=seedPoint.begin();
            j!=seedPoint.end();++j,jIndex++){
            distance = cv::norm(*j - *currentPoint);
            if(distance<epsilon){
                currentPointNo = jIndex;
                qDebug() << "Near seed: " << currentPointNo;
                return 1;
            }
        }
    }
    return 0;
}

void drawSeedPoint::clear()
{
    previousImage.release();
    seedMask.release();

    seedPoint.clear();
    resizeCoef = 1.;
    isSeed = false;
    drawingSeedPoint = false;
}

std::vector<cv::Point2i> drawSeedPoint::getSeed()
{
    std::vector<cv::Point2i> roundedSeedPoints;
    for(std::vector<cv::Point2i>::iterator it = seedPoint.begin() ; it != seedPoint.end(); ++it){
        // Round the location to the nearest subset step grid
        int xLoc = (int)roundf((float)it->x/(float)subsetList->getSubsetSpacing())*subsetList->getSubsetSpacing();
        int yLoc = (int)roundf((float)it->y/(float)subsetList->getSubsetSpacing())*subsetList->getSubsetSpacing();
        roundedSeedPoints.push_back(cv::Point2i(xLoc,yLoc));
    }
    return roundedSeedPoints;
}

void drawSeedPoint::write(cv::FileStorage& fs) const //Write serialization for this class
{
    fs << "{" << "isSeed" << isSeed
       << "seedPoint" << seedPoint
       << "searchBoxWidth" << searchBoxWidth
       << "highStrainEnabled" << highStrainEnabled
       << "subsetSize" << subsetSize
       << "subsetSpacing" << subsetSpacing
       << "interpDegree" << interpDegree
       << "intenseSearch" << intenseSearch
       << "useAllCPU" << useAllCPU
       << "corrRejection" << corrRejection << "}";
}
void drawSeedPoint::read(const cv::FileNode& node) //Read serialization for this class
{
    isSeed= (int)node["isSeed"];
    seedPoint.clear();
    cv::Point2i newPoint;
    cv::FileNodeIterator ptsIt = node["seedPoint"].begin(), ptsItEnd = node["seedPoint"].end();
    for(;ptsIt != ptsItEnd; ++ptsIt){
        newPoint.x = (int)*ptsIt;
        ++ptsIt;
        newPoint.y = (int)*ptsIt;
        seedPoint.push_back(newPoint);
    }
    searchBoxWidth = node["searchBoxWidth"];
    highStrainEnabled = (int)node["highStrainEnabled"];
    subsetSize = node["subsetSize"];
    subsetSpacing = node["subsetSpacing"];
    interpDegree = node["interpDegree"];
    intenseSearch = (int)node["intenseSearch"];
    useAllCPU = (int)node["useAllCPU"];
    corrRejection = (double)node["corrRejection"];
}

void drawSeedPoint::seedShape(cv::Point2i seedPoint){
    cv::circle(seedMask,(seedPoint)*(1./resizeCoef),5,CV_RGB(255,255,255),-1);
    int topLeftX = seedPoint.x-searchBoxWidth/2 > 0 ? seedPoint.x-searchBoxWidth/2 : 0;
    int topLeftY = seedPoint.y-searchBoxWidth/2 > 0 ? seedPoint.y-searchBoxWidth/2 : 0;

    int botRightX = seedPoint.x+searchBoxWidth/2 < fullSizeImage->cols ? seedPoint.x+searchBoxWidth/2 : fullSizeImage->cols;
    int botRightY = seedPoint.y+searchBoxWidth/2 < fullSizeImage->rows ? seedPoint.y+searchBoxWidth/2 : fullSizeImage->rows;
    cv::Rect rectToDraw = cv::Rect(topLeftX*(1./resizeCoef), topLeftY*(1./resizeCoef),
                                   (botRightX-topLeftX)*(1./resizeCoef), (botRightY-topLeftY)*(1./resizeCoef));
    cv::rectangle(seedMask,rectToDraw,CV_RGB(255,255,255),1);
}
