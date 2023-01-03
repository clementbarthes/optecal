#include "draworigin.h"

drawOrigin::drawOrigin()
{
    drawingInProgress = false;
    polarCartFlag = cartesianCoord;
    flipXY = false;
    //circleShape.center
    circleShape.radius = 0.;
    circleShape.angle = 0.;
    circleShape.center = cv::Point2i(0,0);
    maxClippingSliderVal = 0.1;
    angleSet = 0.;
    unitDisplayFlag = 0;
    axesOn = true;
    deformedConfiguration = true;
    spatialCoordinates = true;
    for (int j=0; j<15; ++j){
        autoScaleOn[j] = true;
    }
    motionAmplification = 5.f;
    backgroundAmplifiedMotion = 0.3f;
}

drawOrigin::~drawOrigin()
{
    previousImage.release();
    originMask.release();
}
void drawOrigin::setDisplayFrame(autoResize* cam1Display)
{
    this->cam1Display = cam1Display;
}

void drawOrigin::setImage(cv::Mat* image, float imgResizeCoef){
    previousImage = image->clone();
    imageToDraw = image;
    originMask = cv::Mat::zeros(imageToDraw->rows,
                                imageToDraw->cols,imageToDraw->type());
    this->imgResizeCoef = imgResizeCoef;
}

void drawOrigin::setImageResizeCoef(float imgResizeCoef){
    this->imgResizeCoef = imgResizeCoef;
}

float drawOrigin::getImageResizeCoef(){
    return imgResizeCoef;
}

void drawOrigin::initShape()
{
    drawingInProgress = true;
    circleShape.angle = 0.;
    circleShape.center = cv::Point2i(0,0);
}

void drawOrigin::updatePoint(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;
    if(drawingInProgress){
        circleShape.center = pointUpdate;
    }else{
        // If updatedPoint =1, then update radius
        if(updatedPoint == 1){

            circleShape.radius = cv::norm(pointUpdate - circleShape.center);
            qDebug() << "Radius: " << circleShape.radius;

            // If updatedPoint =2, then update angle
        } else if(updatedPoint == 2){
            const double PI = 3.141592653;
            double angleUpdate;
            angleUpdate = atan2((double)(pointUpdate.y-circleShape.center.y),(double)(pointUpdate.x-circleShape.center.x))
                    - atan2((double)(pointGrabbed.y-circleShape.center.y),(double)(pointGrabbed.x-circleShape.center.x));
            if(flipXY) angleUpdate = - angleUpdate;
            circleShape.angle = angleUpdate + angleSet;
            circleShape.angle = fmod(circleShape.angle,2*PI);
            qDebug() << "Angle = " << circleShape.angle*180./PI << "degrees";

        }else {
            circleShape.center = pointUpdate;
            qDebug() << "x:" << pointUpdate.x << "  y: " << pointUpdate.y;
        }
    }
}

void drawOrigin::setPoint(cv::Point2i newPoint){
    drawingInProgress = false;
    qDebug() << "x:" << newPoint.x << "  y: " << newPoint.y;
    angleSet = circleShape.angle;
    updateDrawing();
}

void drawOrigin::setAngle()
{
    angleSet = circleShape.angle;
}

double drawOrigin::getAngle()
{
    return circleShape.angle;
}

cv::Point2i drawOrigin::getOrigin()
{
    return circleShape.center;
}

void drawOrigin::updateDrawing()
{
    originMask = cv::Mat::zeros(imageToDraw->rows,
                                imageToDraw->cols,imageToDraw->type());
    cv::Point2i origin = circleShape.center*(1./imgResizeCoef);
    // If Origin is at (0,0) display it at (2,2) to make it visible
    origin = origin == cv::Point2i(0,0) ? cv::Point2i(2,2) : origin;


    double vectorLength = 100.;
    cv::Point2i xLabelLoc;
    cv::Point2i yLabelLoc;
    if(flipXY){
        yVector = cv::Point2i(vectorLength*cos(circleShape.angle),-vectorLength*sin(circleShape.angle));
        yLabelLoc = cv::Point2i(vectorLength*cos(circleShape.angle)+9,-vectorLength*sin(circleShape.angle)+30);
        xVector = cv::Point2i(vectorLength*sin(circleShape.angle),vectorLength*cos(circleShape.angle));
        xLabelLoc = cv::Point2i(vectorLength*sin(circleShape.angle)+10,vectorLength*cos(circleShape.angle)+10);
    } else{
        xVector = cv::Point2i(vectorLength*cos(circleShape.angle),vectorLength*sin(circleShape.angle));
        xLabelLoc = cv::Point2i(vectorLength*cos(circleShape.angle)+7,vectorLength*sin(circleShape.angle)+30);
        yVector = cv::Point2i(-vectorLength*sin(circleShape.angle),vectorLength*cos(circleShape.angle));
        yLabelLoc = cv::Point2i(-vectorLength*sin(circleShape.angle)+10,vectorLength*cos(circleShape.angle)+10);
    }
    cv::circle(originMask,origin,3,CV_RGB(255,255,255),-1);
    drawArrow(originMask,origin,origin + xVector,CV_RGB(255,255,255));
    drawArrow(originMask,origin,origin + yVector,CV_RGB(255,255,255));
    putText(originMask, "X",origin+xLabelLoc,
            cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255,255,255), 2, cv::LINE_AA);
    putText(originMask, "Y",origin+yLabelLoc,
            cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255,255,255), 2, cv::LINE_AA);
    if(polarCartFlag == polarCoord){
        if (circleShape.radius < 50.){
            cv::circle(originMask,circleShape.center*(1./imgResizeCoef),
                       50 ,CV_RGB(255,255,255),1);
        } else{
            cv::circle(originMask,circleShape.center*(1./imgResizeCoef),
                       (int)circleShape.radius/imgResizeCoef ,CV_RGB(255,255,255),1);
        }
    }
    cv::add(previousImage,originMask,*imageToDraw);
}


void drawOrigin::drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color)
{
    ///From Mliki Hazar blog (Thanks!!!)
    /// http://mlikihazar.blogspot.com/2013/02/draw-arrow-opencv.html

    int arrowMagnitude = 14;
    int thickness=2;
    int line_type=8;
    int shift=0;
    //Draw the principal line
    cv::line(image, p, q, color, thickness, line_type, shift);
    const double PI = 3.141592653;
    //compute the angle alpha
    double angle = atan2((double)p.y-q.y, (double)p.x-q.x);
    //compute the coordinates of the first segment
    p.x = (int) ( q.x +  arrowMagnitude * cos(angle + PI/5));
    p.y = (int) ( q.y +  arrowMagnitude * sin(angle + PI/5));
    //Draw the first segment
    cv::line(image, p, q, color, thickness, line_type, shift);
    //compute the coordinates of the second segment
    p.x = (int) ( q.x +  arrowMagnitude * cos(angle - PI/5));
    p.y = (int) ( q.y +  arrowMagnitude * sin(angle - PI/5));
    //Draw the second segment
    cv::line(image, p, q, color, thickness, line_type, shift);
}

int drawOrigin::isMouseNearPoint(cv::Point2i *currentPoint){
    updatedPoint = -1;
    int distance;
    int distanceToX;
    int distanceToY;
    double epsilon = 15.*imgResizeCoef;
    if(!drawingInProgress){
        // If shape is a circle, check if the mouse is on the center or the edge of the circle
        distance = cv::norm(circleShape.center - *currentPoint);
        distanceToX = cv::norm(circleShape.center+xVector*imgResizeCoef - *currentPoint);
        distanceToY = cv::norm(circleShape.center+yVector*imgResizeCoef - *currentPoint);
        if(distance<epsilon){
            updatedPoint = 0;
            return drawOrigin::mouseNearCircleCenter;
        }
        bool nearCircle;
        if (circleShape.radius < 50){
            nearCircle = (distance <(50*imgResizeCoef+epsilon)) && (distance >(50*imgResizeCoef-epsilon));
        } else {
            nearCircle = (distance <(circleShape.radius+epsilon)) && (distance >(circleShape.radius-epsilon));
        }

        if (polarCartFlag == polarCoord  && nearCircle){
            updatedPoint = 1;
            // Check if cursor is on the left hand side or the right hand side of the center
            // simply to display a different cursor
            if ((currentPoint->x < (circleShape.center.x) && currentPoint->y < (circleShape.center.y))  ||
                    (currentPoint->x > (circleShape.center.x) && currentPoint->y > (circleShape.center.y))){
                return drawOrigin::mouseNearCircleEdgeLeft;
            }else {
                return drawOrigin::mouseNearCircleEdgeRight;
            }
        }
        if((distanceToX<epsilon) || (distanceToY<epsilon))
        {
            updatedPoint = 2;
            return drawOrigin::mouseNearEdgeVectorVert;
        }

    }

    return 0;

}

void drawOrigin::clearShape()
{
    circleShape.radius = 50;
    circleShape.angle = 0.;
    circleShape.center = cv::Point2i(0,0);
}


void drawOrigin::setFlipXY(bool check)
{
    flipXY = check;
    circleShape.angle = -circleShape.angle;
    setAngle();
    updateDrawing();
    cam1Display->updateResized();
    qDebug() << "Flip X-Y" << check;
}


void drawOrigin::setPolarCartesian(int val)
{
    polarCartFlag = val;
    //    updateDrawing();
    //    cam1Display->updateResized();
    qDebug() << "Polar cartesian flag: " << val;
}



void drawOrigin::write(cv::FileStorage& fs) const //Write serialization for this class
{

    //    struct shape {
    //        cv::Point2i center;
    //        double radius;
    //        double angle;
    //    } circleShape;

    //    cv::Point2i xVector;
    //    cv::Point2i yVector;

    fs << "{"
       <<  "minMaxManualVals" << "[";
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            if((i==0) && autoScaleOn[j])
                fs << 0.;
            else if((i==1) && autoScaleOn[j])
                fs << 1.;
            else
                fs << manualBounds[j][i];
        }
    }

    fs <<"]"
      <<  "manualMinMaxSlider" << "[";
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            if((i==0) && autoScaleOn[j])
                fs << 0.;
            else if((i==1) && autoScaleOn[j])
                fs << 1.;
            else
                fs << manualMinMaxSlider[j][i];
        }
    }

    fs <<"]"
      <<  "autoScaleOn" << "[";
    for(int i=0; i< 15 ; ++i){
        fs << autoScaleOn[i];
    }
    fs <<"]"
    << "circleShape" ;
    fs << "{" << "center" << circleShape.center
       << "radius" << circleShape.radius
       << "angle" << circleShape.angle << "}";
    fs << "xVector" << xVector << "yVector" << yVector
       << "polarCartFlag" << polarCartFlag << "flipXY" << flipXY
        << "axesOn" << axesOn << "unitDisplayFlag"<< unitDisplayFlag
        << "colormapCoef" << colormapCoef << "deformedConfiguration" << deformedConfiguration
        << "spatialCoordinates" << spatialCoordinates <<"}";
}
void drawOrigin::read(const cv::FileNode& node) //Read serialization for this class
{
    cv::FileNodeIterator minMaxManualIt = node["minMaxManualVals"].begin();
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            manualBounds[j][i] = (double)*minMaxManualIt;
            ++minMaxManualIt;
        }
    }
    cv::FileNodeIterator minMaxSliderIt = node["manualMinMaxSlider"].begin();
    for(int i=0; i< 2 ; ++i){
        for(int j=0; j<15 ; ++j){
            manualMinMaxSlider[j][i] = (double)*minMaxSliderIt;
            ++minMaxSliderIt;
        }
    }
    cv::FileNodeIterator autoScaleOnIt = node["autoScaleOn"].begin();
    for(int i=0; i< 15 ; ++i){
        autoScaleOn[i] = (int)*autoScaleOnIt;
        ++autoScaleOnIt;
    }
    cv::FileNode circleShapeNode= node["circleShape"];
    cv::FileNodeIterator ptsIt = circleShapeNode["center"].begin(), ptsItEnd = circleShapeNode["center"].end();
    for(;ptsIt != ptsItEnd; ++ptsIt){
        circleShape.center.x = (int)*ptsIt;
        ++ptsIt;
        circleShape.center.y = (int)*ptsIt;
    }
    circleShape.radius = (double)circleShapeNode["radius"];
    circleShape.angle = (double)circleShapeNode["angle"];

    cv::FileNodeIterator xVecInit = node["xVector"].begin(), xVecEnd = node["xVector"].end();
    for(;xVecInit != xVecEnd; ++xVecInit){
        xVector.x = (int)*xVecInit;
        ++xVecInit;
        xVector.y = (int)*xVecInit;
    }
    cv::FileNodeIterator yVecInit = node["yVector"].begin(), yVecEnd = node["yVector"].end();
    for(;yVecInit != yVecEnd; ++yVecInit){
        yVector.x = (int)*yVecInit;
        ++yVecInit;
        yVector.y = (int)*yVecInit;
    }
    polarCartFlag = (int)node["polarCartFlag"];
    flipXY = (bool)((int)node["flipXY"]);
    axesOn = (bool)((int)node["axesOn"]);
    unitDisplayFlag = (int)node["unitDisplayFlag"];
    colormapCoef = (float)node["colormapCoef"];
    spatialCoordinates = (int)node["spatialCoordinates"];
    deformedConfiguration = (int)node["deformedConfiguration"];
}
