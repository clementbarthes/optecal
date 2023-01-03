#include "templatematch.h"

templateMatch::templateMatch()
{
}

templateMatch::~templateMatch()
{

}

cv::Point templateMatch::matchSeed(cv::Mat img, cv::Mat& templ)
{

    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    cv::Mat result;
    result.create( result_cols, result_rows, CV_32FC1 );

    /// Do the Matching and Normalize
    int match_method = cv::TM_SQDIFF_NORMED;
    cv::matchTemplate( img, templ, result, match_method );
    cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::Point matchLoc;

    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );


    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
    else
    { matchLoc = maxLoc; }

    // Offset matchLoc to be located at the center of the subset
    matchLoc.x += templ.cols/2; matchLoc.y += templ.rows/2;

    result.release();
    return matchLoc;
}
