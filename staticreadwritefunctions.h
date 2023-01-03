#ifndef STATICREADWRITEFUNCTIONS_H
#define STATICREADWRITEFUNCTIONS_H
#include "drawseedpoint.h"
#include "calibration.h"
#include "virtualmeasurementtools.h"


//These write and read functions must be defined for the serialization in FileStorage to work
static void write(cv::FileStorage& fs, const std::string&,const fileList& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, fileList& x, const fileList& default_value = fileList()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

static void write(cv::FileStorage& fs, const std::string&,const drawShape& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, drawShape& x, const drawShape& default_value = drawShape()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

static void write(cv::FileStorage& fs, const std::string&,const drawSeedPoint& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, drawSeedPoint& x, const drawSeedPoint& default_value = drawSeedPoint()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

static void write(cv::FileStorage& fs, const std::string&,const drawOrigin& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, drawOrigin& x, const drawOrigin& default_value = drawOrigin()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}




static void write(cv::FileStorage& fs, const std::string&,const displacements& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, displacements& x, const displacements& default_value = displacements()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

static void write(cv::FileStorage& fs, const std::string&,const calibration& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, calibration& x, const calibration& default_value = calibration()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

static void write(cv::FileStorage& fs, const std::string&,const virtualMeasurementTools& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, virtualMeasurementTools& x, const virtualMeasurementTools& default_value = virtualMeasurementTools()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

#endif // STATICREADWRITEFUNCTIONS_H
