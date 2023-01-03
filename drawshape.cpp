#include "drawshape.h"


drawShape::drawShape()
{
    drawingInProgress = false;
    updatePointInProgress = false;
}

drawShape::~drawShape()
{
    previousImage.release();
    roiMask.release();
    listOfShapes.clear();

}

void drawShape::setImage(cv::Mat* image, float imgResizeCoef){
    previousImage = image->clone();
    imageToDraw = image;
    roiMask = cv::Mat::zeros(imageToDraw->rows,
                             imageToDraw->cols,imageToDraw->type());
    this->imgResizeCoef = imgResizeCoef;
}

void drawShape::initShape(int Type)
{
    drawingInProgress = true;
    shape initShape;
    initShape.drawType = Type;
    initShape.listOfPoints.push_back(cv::Point2i(0,0));
    initShape.radius = 0;
    listOfShapes.push_back(initShape);
}


void drawShape::setPoint(cv::Point2i newPoint){
    if ((listOfShapes.last().drawType == drawShape::plusCircle ||
         listOfShapes.last().drawType == drawShape::minusCircle)  &&
            listOfShapes.last().listOfPoints.size() == 2){
        drawingInProgress = false;
        listOfShapes.last().listOfPoints.pop_back();
    } else if(listOfShapes.last().drawType == drawShape::lineOnly
              && listOfShapes.last().listOfPoints.size() == 2){
        drawingInProgress = false;
    } else {
        listOfShapes.last().listOfPoints.push_back(newPoint);
        qDebug() << "x:" << newPoint.x << "  y: " << newPoint.y;
    }
    drawShape::updateDrawing();
}

void drawShape::updatePoint(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    if(drawingInProgress){
        listOfShapes.last().listOfPoints.back() = pointUpdate;
    }else{
        // If currentPointNo =-1, then update radius, else update point
        if(currentPointNo < 0){
            listOfShapes[currentShapeNo].radius = cv::norm(pointUpdate - listOfShapes[currentShapeNo].listOfPoints[0]);
            qDebug() << "Radius: " << listOfShapes[currentShapeNo].radius;
        }else {
            listOfShapes[currentShapeNo].listOfPoints[currentPointNo] = pointUpdate;
            qDebug() << "x:" << pointUpdate.x << "  y: " << pointUpdate.y;
        }
    }
}

void drawShape::deletePoint(){
    listOfShapes[currentShapeNo].listOfPoints.erase(listOfShapes[currentShapeNo].listOfPoints.begin() + currentPointNo);
    if(listOfShapes[currentShapeNo].listOfPoints.size() < 3)
        listOfShapes.erase(listOfShapes.begin()+currentShapeNo);
}

void drawShape::deleteShape(){
    listOfShapes.erase(listOfShapes.begin()+currentShapeNo);
}

void drawShape::getShapes(){
    roiMask = cv::Mat::zeros(imageToDraw->rows,
                             imageToDraw->cols,imageToDraw->type());
    for(QList<shape>::iterator i=listOfShapes.begin(); i!=listOfShapes.end();++i){
        switch(i->drawType){
        case plusPoly:
            if(i->listOfPoints.size()>=3){
                //Rescale the vector of points to fit the current displayed size
                std::vector<cv::Point2i> listOfPointsScaled(i->listOfPoints);
                for(std::vector<cv::Point2i>::iterator ptsIter = listOfPointsScaled.begin();
                    ptsIter != listOfPointsScaled.end(); ++ptsIter){
                    *ptsIter = (1./imgResizeCoef)*(*ptsIter);
                }
                const cv::Point* pts = (const cv::Point*) cv::Mat(listOfPointsScaled).data;
                int npts = cv::Mat(listOfPointsScaled).rows;
                if (roiMask.type()==CV_8UC3){
                    cv::fillPoly(roiMask,&pts,&npts,1,CV_RGB(0,0,255),8);
                }else {
                    cv::fillPoly(roiMask,&pts,&npts,1,1,8);
                }
            }
            break;
        case minusPoly:
            if(i->listOfPoints.size()>=3){
                //Rescale the vector of points to fit the current displayed size
                std::vector<cv::Point2i> listOfPointsScaled(i->listOfPoints);
                for(std::vector<cv::Point2i>::iterator ptsIter = listOfPointsScaled.begin();
                    ptsIter != listOfPointsScaled.end(); ++ptsIter){
                    *ptsIter = (1./imgResizeCoef)*(*ptsIter);
                }
                const cv::Point* pts = (const cv::Point*) cv::Mat(listOfPointsScaled).data;
                int npts = cv::Mat(listOfPointsScaled).rows;
                if (roiMask.type()==CV_8UC3){
                    cv::fillPoly(roiMask,&pts,&npts,1,CV_RGB(0,0,0),8);
                } else {
                    cv::fillPoly(roiMask,&pts,&npts,1,0,8);
                }
            }
            break;
        case plusCircle:
            // If drawingInProgress = true, the circle is being created for the
            // first time, hence the radius must be computed
            if(drawingInProgress && i->listOfPoints.size() > 1){
                i->radius = cv::norm(i->listOfPoints[1]-i->listOfPoints[0]);
            }
            if (roiMask.type()==CV_8UC3){
                cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),
                        (int)i->radius/imgResizeCoef ,CV_RGB(0,0,255),-1);
            } else {
                cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),
                        (int)i->radius/imgResizeCoef ,1,-1);
            }
            break;
        case minusCircle:
            // If drawingInProgress = true, the circle is being created for the
            // first time, hence the radius must be computed
            if(drawingInProgress && i->listOfPoints.size() > 1){
                i->radius = cv::norm(i->listOfPoints[1]-i->listOfPoints[0]);
            }
            if (roiMask.type()==CV_8UC3){
                cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),
                        (int)i->radius/imgResizeCoef ,CV_RGB(0,0,0),-1);
            } else {
                cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),
                        (int)i->radius/imgResizeCoef ,0,-1);
            }
            break;
        }
    }
}

void drawShape::updateDrawing()
{
    drawShape::getShapes();
    cv::add(previousImage,roiMask,*imageToDraw);

}

void drawShape::updateWLines(){
    std::vector<cv::Point2i>::iterator prevPoint;
    bool onlyOnePoint;
    drawShape::getShapes();
    for(QList<shape>::iterator i=listOfShapes.begin(); i!=listOfShapes.end();++i){
        if(i->drawType == plusPoly || i->drawType == minusPoly){
            onlyOnePoint = true;
            for(std::vector<cv::Point2i>::iterator j=i->listOfPoints.begin();
                j!=i->listOfPoints.end();++j){
                cv::circle(roiMask,(*j)*(1./imgResizeCoef),2,CV_RGB(255,255,255),-1);
                if(!onlyOnePoint){
                    cv::line(roiMask,(*prevPoint)*(1./imgResizeCoef),
                             (*j)*(1./imgResizeCoef),
                             CV_RGB(255,255,255),1);
                    if((j+1) == i->listOfPoints.end() && !onlyOnePoint) {
                        cv::line(roiMask,(*j)*(1./imgResizeCoef),
                                 (*i->listOfPoints.begin())*(1./imgResizeCoef),
                                 CV_RGB(255,255,255),1);
                    }
                }
                prevPoint = j;
                onlyOnePoint = false;
            }
        } else if (i->drawType == lineOnly){
            if (i->listOfPoints.size() == 2 ){
                drawArrow(roiMask,
                          (i->listOfPoints[0])*(1./imgResizeCoef),
                        (i->listOfPoints[1])*(1./imgResizeCoef),
                          CV_RGB(255,255,255));
            }
        } else{
            // Center Point
            cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),2,CV_RGB(255,255,255),-1);
            cv::circle(roiMask,i->listOfPoints[0]*(1./imgResizeCoef),(int)i->radius/imgResizeCoef ,CV_RGB(255,255,255),1);
        }
    }
    cv::add(previousImage,roiMask,*imageToDraw);
}


void drawShape::acceptShape()
{
    drawingInProgress = false;
    //if Polygon has two points or less, delete it
    if((listOfShapes.last().listOfPoints.size()<=2) ||
            ((listOfShapes.last().listOfPoints.size()<2) &&
                        (listOfShapes.last().drawType == lineOnly))){
        listOfShapes.pop_back();
        drawShape::updateDrawing();
        qDebug() << "Delete last shape";
    }
}

void drawShape::rejectShape()
{
    drawingInProgress = false;
    listOfShapes.pop_back();
    drawShape::updateDrawing();
    qDebug() << "Delete last shape";
}

void drawShape::rejectLastPoint()
{
    drawingInProgress = false;
    listOfShapes.last().listOfPoints.pop_back();
    qDebug() << "Delete last point";
    //if Polygon has two points or less, delete it
    if((listOfShapes.last().listOfPoints.size()<=2) ||
            ((listOfShapes.last().listOfPoints.size()<2) &&
                        (listOfShapes.last().drawType == lineOnly))){
        listOfShapes.pop_back();
        drawShape::updateDrawing();
        qDebug() << "Delete last shape";
    }
    drawShape::updateDrawing();

}

cv::Mat* drawShape::getROIMask()
{
    drawShape::getShapes();
    return &roiMask;
}

int drawShape::isMouseNearPoint(cv::Point2i *currentPoint){
    currentShapeNo = -1;
    currentPointNo = -1;
    int iIndex = 0;
    int distance;
    double epsilon = 5.*imgResizeCoef;
    if(!drawingInProgress){
        for(QList<shape>::iterator i=listOfShapes.begin(); i!=listOfShapes.end();++i,iIndex++){
            int jIndex = 0;

            for(std::vector<cv::Point2i>::iterator j=i->listOfPoints.begin();j!=i->listOfPoints.end();++j,jIndex++){
                if((i->drawType == drawShape::plusPoly) || (i->drawType == drawShape::minusPoly)
                        || (i->drawType == drawShape::lineOnly)){
                    distance = cv::norm(*j - *currentPoint);
                    if(distance<epsilon){

                        currentShapeNo = iIndex;
                        currentPointNo = jIndex;
                        return drawShape::mouseNearPolyVertex;
                    }
                } else {
                    // If shape is a circle, check if the mouse is on the center or the edge of the circle
                    distance = cv::norm(i->listOfPoints[0] - *currentPoint);
                    if(distance<epsilon){
                        currentShapeNo = iIndex;
                        currentPointNo = jIndex;
                        return drawShape::mouseNearCircleCenter;
                    }
                    if ((distance <(i->radius+epsilon)) && (distance >(i->radius-epsilon))){
                        currentShapeNo = iIndex;
                        // Check if cursor is on the left hand side or the right hand side of the center
                        // simply to display a different cursor
                        if ((currentPoint->x < (i->listOfPoints[0].x) && currentPoint->y < (i->listOfPoints[0].y))  ||
                                (currentPoint->x > (i->listOfPoints[0].x) && currentPoint->y > (i->listOfPoints[0].y))){
                            return drawShape::mouseNearCircleEdgeLeft;
                        }else {
                            return drawShape::mouseNearCircleEdgeRight;
                        }
                    }

                }
            }

        }
    }
    return 0;

}

bool drawShape::isRoiDefined()
{
    if(listOfShapes.size()){
        return true;
    } else {
        return false;
    }
}
int drawShape::numberShapes(){
    return listOfShapes.size();
}

double drawShape::getLength()
{
    if(listOfShapes.last().drawType == lineOnly){
        double length = sqrt(pow((double)listOfShapes.last().listOfPoints[1].x - (double)listOfShapes.last().listOfPoints[0].x,2.)
                + pow((double)listOfShapes.last().listOfPoints[1].y - (double)listOfShapes.last().listOfPoints[0].y,2.));
        qDebug() << "Measured length: " << length;
        return length;
    }
    return 0.;
}

void drawShape::clearShapes()
{
    listOfShapes.clear();
}

void drawShape::clear()
{
    previousImage.release();
    roiMask.release();
    listOfShapes.clear();
    currentShapeNo = 0;
    currentPointNo = 0;
    imgResizeCoef = 1.;
}

void drawShape::drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color)
{
    ///From Mliki Hazar blog (Thanks!!!)
    /// http://mlikihazar.blogspot.com/2013/02/draw-arrow-opencv.html

    cv::Point2i arrowPoint;
    int arrowMagnitude = 14;
    int thickness=2;
    int line_type=8;
    int shift=0;
    //Draw the principal line
    cv::line(image, p, q, color, thickness, line_type, shift);
    const double PI = 3.141592653;
    //compute the angle alpha
    double angle = atan2((double)p.y-q.y, (double)p.x-q.x);

    // Compute the top arrow
    //compute the coordinates of the first segment
    arrowPoint.x = (int) ( q.x +  arrowMagnitude * cos(angle + PI/5));
    arrowPoint.y = (int) ( q.y +  arrowMagnitude * sin(angle + PI/5));
    //Draw the first segment
    cv::line(image, arrowPoint, q, color, thickness, line_type, shift);
    //compute the coordinates of the second segment
    arrowPoint.x = (int) ( q.x +  arrowMagnitude * cos(angle - PI/5));
    arrowPoint.y = (int) ( q.y +  arrowMagnitude * sin(angle - PI/5));
    //Draw the second segment
    cv::line(image, arrowPoint, q, color, thickness, line_type, shift);

    // Compute the bottom arrow
    //compute the coordinates of the first segment
    arrowPoint.x = (int) ( p.x -  arrowMagnitude * cos(angle + PI/5));
    arrowPoint.y = (int) ( p.y - arrowMagnitude * sin(angle + PI/5));
    //Draw the first segment
    cv::line(image, arrowPoint, p, color, thickness, line_type, shift);
    //compute the coordinates of the second segment
    arrowPoint.x = (int) ( p.x -  arrowMagnitude * cos(angle - PI/5));
    arrowPoint.y = (int) ( p.y -  arrowMagnitude * sin(angle - PI/5));
    //Draw the second segment
    cv::line(image, arrowPoint, p, color, thickness, line_type, shift);
}

void drawShape::write(cv::FileStorage& fs) const                        //Write serialization for this class
{

    fs << "{" << "roiShape" << "[";
    for (int i=0; i<listOfShapes.size();++i){
        fs << "{" << "drawType" << listOfShapes[i].drawType
           << "listOfPoints" << listOfShapes[i].listOfPoints
           << "radius" << listOfShapes[i].radius << "}";
    }
    fs << "]" << "}";
}
void drawShape::read(const cv::FileNode& node)                          //Read serialization for this class
{
    shape newShape;
    listOfShapes.clear();
    cv::FileNodeIterator it = node["roiShape"].begin(), it_end = node["roiShape"].end(); // Go through the node
    for (; it != it_end; ++it){
        newShape.drawType = (int)(*it)["drawType"];
        cv::FileNodeIterator ptsIt = (*it)["listOfPoints"].begin(), ptsItEnd = (*it)["listOfPoints"].end();
        for(;ptsIt != ptsItEnd; ++ptsIt){
            cv::Point2i newPoint;
            newPoint.x = (int)*ptsIt;
            ++ptsIt;
            newPoint.y = (int)*ptsIt;
            newShape.listOfPoints.push_back(newPoint);
        }
        newShape.radius = (double)(*it)["radius"];
        listOfShapes.push_back(newShape);
        newShape.listOfPoints.clear();
    }
}

