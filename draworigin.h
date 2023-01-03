#ifndef DRAWORIGIN_H
#define DRAWORIGIN_H
#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "math.h"

#include "autoresize.h"

class drawOrigin
{

    autoResize *cam1Display;
    cv::Mat previousImage;
    cv::Mat originMask;
    cv::Mat* imageToDraw;
    struct shape {
        cv::Point2i center;
        double radius;
        double angle;
    } circleShape;

    cv::Point2i xVector;
    cv::Point2i yVector;
    double angleSet;

    float imgResizeCoef;
    int updatedPoint;

    void drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color);


public:

    static const int mouseNearEdgeVectorVert = 1;
    static const int mouseNearCircleCenter = 2;
    static const int mouseNearCircleEdgeLeft = 3;
    static const int mouseNearCircleEdgeRight = 4;

    static const int pixelUnit = 0;
    static const int mmUnit = 1;
    static const int cmUnit = 2;
    static const int mUnit = 3;
    static const int inUnit = 4;
    static const int ftUnit = 5;


    int polarCartFlag;
    bool flipXY;
    // Axes display on or off
    bool axesOn;

    // Unit displayed (flag defined in calibration.h)
    int unitDisplayFlag;

    bool deformedConfiguration;

    bool spatialCoordinates;

    float colormapCoef;

    // True if the auto-scale is turned on
    bool autoScaleOn[15];

    //col 0: min value, col 1: max value
    double manualBounds[15][2];
    //col 0: min value of the slider, col 1: max value of the slider
    double manualMinMaxSlider[15][2];

    // Max Clipping value allowed by slider
    double maxClippingSliderVal;

    // Amplfied motion parameters
    float motionAmplification;

    // Background intensity for amplified motion
    float backgroundAmplifiedMotion;

    static const int cartesianCoord = 0;
    static const int polarCoord = 1;


    cv::Point2i pointGrabbed;
    bool drawingInProgress;
    bool updatePointInProgress;

    drawOrigin();
    ~drawOrigin();

    // Defines the display box
     void setDisplayFrame(autoResize *cam1Display);

    // Defines background image
    void setImage(cv::Mat* image, float imgResizeCoef);

    // Update the image resize coefficient
    void setImageResizeCoef(float imgResizeCoef);

    // Initialize the shape
    void initShape();

    // Updates the position of a specified point based on mouse position
    void updatePoint(cv::Point2i *currentPoint);

    // Add a point to the vector of points
    void setPoint(cv::Point2i newPoint);

    // Set the angle
    void setAngle();

    // Get the angle
    double getAngle();

    // Get the origin
    cv::Point2i getOrigin();

    // Updates the drawing
    void updateDrawing();

    //returns true if close from point and points to the shape number and point number selected
    int isMouseNearPoint(cv::Point2i *currentPoint);

    //Clears the current shape parameters
    void clearShape();

    // Flip the X and Y axes
    void setFlipXY(bool check);

    void setPolarCartesian(int val);

    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);

    float getImageResizeCoef();
};

#endif // DRAWORIGIN_H
