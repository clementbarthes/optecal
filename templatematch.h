#ifndef TEMPLATEMATCH_H
#define TEMPLATEMATCH_H
#include <QDebug>
#include "opencv2/opencv.hpp"



class templateMatch
{
public:
    templateMatch();
    ~templateMatch();

    cv::Point matchSeed(cv::Mat img, cv::Mat &templ);

};

#endif // TEMPLATEMATCH_H
