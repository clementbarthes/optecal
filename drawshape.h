#ifndef DRAWSHAPE_H
#define DRAWSHAPE_H
#include <QObject>
#include <QList>
#include <QDebug>

#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/opencv.hpp"


class drawShape
{
    cv::Mat previousImage;
    cv::Mat roiMask;
    cv::Mat* imageToDraw;
    struct shape {
        int drawType;
        std::vector<cv::Point2i> listOfPoints;
        double radius;
    };
    QList<shape> listOfShapes;
    int currentShapeNo;
    int currentPointNo;
    float imgResizeCoef;

public:
    // Shape flags
    static const int plusPoly = 0;
    static const int minusPoly = 1;
    static const int plusCircle = 2;
    static const int minusCircle = 3;
    static const int lineOnly = 4;

    static const int mouseNearPolyVertex = 1;
    static const int mouseNearCircleCenter = 2;
    static const int mouseNearCircleEdgeLeft = 3;
    static const int mouseNearCircleEdgeRight = 4;

    bool drawingInProgress;
    bool updatePointInProgress;

    drawShape();
    ~drawShape();
    // Defines background image
    void setImage(cv::Mat* image, float imgResizeCoef);

    // Initialize a shape specified by Type and create first point
    void initShape(int Type);

    // Add a point to the vector of points of the last shape
    void setPoint(cv::Point2i newPoint);

    // Updates the position of a specified point based on mouse position
    void updatePoint(cv::Point2i *currentPoint);

    // Updates the drawing
    void updateDrawing();

    // Draw the lines and points at the boundaries of the shapes (used when drawing ROI)
    void updateWLines();

    // If shape fulfills all conditions,then shape remains at the end of the list
    void acceptShape();

    // If user specifies it, the last shape is deleted
    void rejectShape();

    // Deletes the last point of the last shape
    void rejectLastPoint();

    // Points to the ROI mask, without the background image
    cv::Mat* getROIMask();

    //returns true if close from point and points to the shape number and point number selected
    int isMouseNearPoint(cv::Point2i *currentPoint);

    //Returns true if there is more than one shape
    bool isRoiDefined();

    // Returns number of shapes
    int numberShapes();

    // Returns length of a line
    double getLength();

    // Clear all shapes
    void clearShapes();

    // Clear object attributes
    void clear();

    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);


    void deletePoint();
    void deleteShape();
private:
    // Transform shape parameters into ROI Mask
    void getShapes();
    void drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color);
};
#endif // DRAWSHAPE_H
