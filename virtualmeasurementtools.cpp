#include "virtualmeasurementtools.h"


virtualMeasurementTools::virtualMeasurementTools()
{
    strainGaugeDrawingCenter = false;
    strainGaugeDrawingWidth = false;
    updateCenterInProgress = false;
    updateWidthInProgress = false;
    updateAngleInProgress = false;
    extensometerDrawingInProgress = false;
    currentStrainGauge = -1;
    currentExtensometer = -1;
    pd = new QProgressDialog("Exporting...", "Cancel", 0, 13);
    pd->close();
}

void virtualMeasurementTools::setRootPath(QDir rootFolder)
{
    this->rootFolder = rootFolder;
}

void virtualMeasurementTools::addStrainGauge()
{
    //    static int nStrainGauges = 0;
    //    ++nStrainGauges;
    strainGaugeDrawingCenter = true;
    strainGaugeDrawingWidth = false;
    strainGauge newStrainGauge;

    newStrainGauge.name = new QListWidgetItem(QString("Strain Gauge " + QString::number((int)strainGaugeList.size()+1)));
    newStrainGauge.name->setFlags (newStrainGauge.name->flags () | Qt::ItemIsEditable);
    newStrainGauge.height = 200;
    newStrainGauge.width = 100;
    newStrainGauge.angle = 0.;
    newStrainGauge.center = cv::Point2i(-1000,-1000);
    strainGaugeList.push_back(newStrainGauge);
}

void virtualMeasurementTools::addExtensometer()
{
    //    static int nExtensometers = 0;
    //    ++nExtensometers;
    extensometerDrawingInProgress = true;
    extensometer newExtensometer;
    newExtensometer.name = new QListWidgetItem(
                QString("Extensometer " + QString::number((int)extensometerList.size()+1)));
    newExtensometer.name->setFlags(newExtensometer.name->flags () | Qt::ItemIsEditable);
    newExtensometer.points.push_back(cv::Point2i(0,0));
    extensometerList.push_back(newExtensometer);

}

void virtualMeasurementTools::setDisplayFrame(autoResize *cam1Display)
{
    this->cam1Display = cam1Display;
}



void virtualMeasurementTools::setImage(cv::Mat *image, float imgResizeCoef)
{
    previousImage = image->clone();
    imageToDraw = image;
    toolsMask = cv::Mat::zeros(imageToDraw->rows,
                               imageToDraw->cols,imageToDraw->type());
    this->imgResizeCoef = imgResizeCoef;
}

void virtualMeasurementTools::setCalibPointer(calibration* cam1Calibration)
{
    this->cam1Calibration = cam1Calibration;
}

void virtualMeasurementTools::setLabels(QLabel *e11Label, QLabel *e12Label, QLabel *e22Label,
                                        QLabel *elongationLabel, QLabel *elongationXLabel, QLabel *elongationYLabel,
                                        QLabel *sgWidthLabel, QLabel *sgHeightLabel, QLabel *sgCenterLabel, QLabel *sgAngleLabel,
                                        QLabel *extPointsLabel, QLabel *extLengthLabel)
{
    this->e11Label = e11Label;
    this->e12Label = e12Label;
    this->e22Label = e22Label;
    this->elongationLabel = elongationLabel;
    this->elongationXLabel = elongationXLabel;
    this->elongationYLabel = elongationYLabel;
    this->sgWidthLabel = sgWidthLabel;
    this->sgHeightLabel = sgHeightLabel;
    this->sgCenterLabel = sgCenterLabel;
    this->sgAngleLabel = sgAngleLabel;
    this->extPointsLabel = extPointsLabel;
    this->extLengthLabel = extLengthLabel;
}

void virtualMeasurementTools::setImageResizeCoef(float imgResizeCoef)
{
    this->imgResizeCoef = imgResizeCoef;
}

void virtualMeasurementTools::updateCenter(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    if(strainGaugeDrawingCenter || updateCenterInProgress){
        strainGaugeList[currentStrainGauge].center = pointUpdate;
    }
}

void virtualMeasurementTools::updateWidth(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    double angle = strainGaugeList[currentStrainGauge].angle;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    if(strainGaugeDrawingWidth || updateWidthInProgress){
        strainGaugeList[currentStrainGauge].width = 2*abs((pointUpdate.x - strainGaugeList[currentStrainGauge].center.x)*cos(angle)
                                                          - (pointUpdate.y - strainGaugeList[currentStrainGauge].center.y)*sin(angle));
        strainGaugeList[currentStrainGauge].height = 2*abs((pointUpdate.y - strainGaugeList[currentStrainGauge].center.y)*cos(angle)
                                                           + (pointUpdate.x - strainGaugeList[currentStrainGauge].center.x)*sin(angle));
        qDebug() << strainGaugeList[currentStrainGauge].width << "x" << strainGaugeList[currentStrainGauge].height;
    }
}

void virtualMeasurementTools::updateAngle(cv::Point2i *currentPoint)
{
    strainGauge *updatedStrainGauge = &strainGaugeList[currentStrainGauge];
    const double PI = 3.141592653;
    double angleUpdate;
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    angleUpdate = -atan2((double)(pointUpdate.y-updatedStrainGauge->center.y),(double)(pointUpdate.x-updatedStrainGauge->center.x))
            + atan2((double)(pointGrabbed.y-updatedStrainGauge->center.y),(double)(pointGrabbed.x-updatedStrainGauge->center.x));
    updatedStrainGauge->angle = angleUpdate + angleSet;
    updatedStrainGauge->angle = fmod(updatedStrainGauge->angle,2*PI);
    qDebug() << "Angle = " << updatedStrainGauge->angle*180./PI << "degrees";
}

void virtualMeasurementTools::addExtensometerPoint(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    extensometerList[currentExtensometer].points.back() = pointUpdate;
}

void virtualMeasurementTools::updateExtensometer(cv::Point2i *currentPoint)
{
    cv::Point2i pointUpdate = *currentPoint;
    pointUpdate.x = pointUpdate.x >= 0 ? pointUpdate.x : 0;
    pointUpdate.y = pointUpdate.y >= 0 ? pointUpdate.y : 0;
    pointUpdate.x = pointUpdate.x <= (imageToDraw->cols)*imgResizeCoef ? pointUpdate.x : imageToDraw->cols*imgResizeCoef;
    pointUpdate.y = pointUpdate.y <= (imageToDraw->rows)*imgResizeCoef ? pointUpdate.y : imageToDraw->rows*imgResizeCoef;

    extensometerList[currentExtensometer].points[pointGrabbedIdx] = pointUpdate;
}

void virtualMeasurementTools::updateSolutionMap(drawOrigin *originAndAxesLayer,
                                                int currentImg, fileList *correlationFiles)
{
    if(currentImg <0)
        return;
    dispSol.clear();
    if(displacements::openSolutionFile(currentImg, correlationFiles,&dispSol)){
        //  Get processing parameters for the results
        //dispSol = *dispFbk;
        dispSol.createResizedSolution(correlationFiles->getImageColor8bits(currentImg));
        this->originAndAxesLayer = *originAndAxesLayer;
        this->originAndAxesLayer.setImageResizeCoef(1.0);
        loadDispAndCoords();
        qDebug() << "Post-processing solution updated";
    }
}

void virtualMeasurementTools::updateDrawing()
{
    toolsMask = cv::Mat::zeros(imageToDraw->rows,
                               imageToDraw->cols,imageToDraw->type());
    previousImage.copyTo(*imageToDraw);
    if ((currentStrainGauge>=0) && (currentStrainGauge<(int)strainGaugeList.size())){
        drawStrainGauge(currentStrainGauge);
    } else if((currentExtensometer>=0) && (currentExtensometer<(int)extensometerList.size())) {
        drawExtensometer(currentExtensometer);
    }
    //cv::add(previousImage,toolsMask,*imageToDraw);
}

void virtualMeasurementTools::deleteStrainGauge(int idx)
{
    strainGaugeList.erase(strainGaugeList.begin()+idx);

}

void virtualMeasurementTools::deleteExtensometer(int idx)
{
    extensometerList.erase(extensometerList.begin()+idx);
}


void virtualMeasurementTools::drawStrainGauge(int strainGaugeIdx)
{
    qDebug() << maskDouble.rows << maskDouble.cols;
    strainGaugeMask = cv::Mat::zeros(maskDouble.size(),CV_64F);
    cv::Point2i center = strainGaugeList[strainGaugeIdx].center;
    int width = strainGaugeList[strainGaugeIdx].width;
    int height = strainGaugeList[strainGaugeIdx].height;
    double angle = strainGaugeList[strainGaugeIdx].angle;
    cv::Scalar color = CV_RGB(10,10,10);

    cv::Point2i xVector = cv::Point2i(vectorLength*cos(angle),-vectorLength*sin(angle));
    cv::Point2i xLabelLoc = cv::Point2i(vectorLength*cos(angle)+9,-vectorLength*sin(angle)+30);
    cv::Point2i yVector = cv::Point2i(-vectorLength*sin(angle),-vectorLength*cos(angle));
    cv::Point2i yLabelLoc = cv::Point2i(-vectorLength*sin(angle)-10,-vectorLength*cos(angle)-10);

    qDebug() << center.x << "x" << center.y;
    std::vector<cv::Point2i> listOfPoints;
    listOfPoints.push_back(center + cv::Point2i(-(.5*cos(angle))*width+(.5*sin(angle))*height,
                                                (.5*sin(angle))*width+(.5*cos(angle))*height));
    listOfPoints.push_back(center + cv::Point2i((.5*cos(angle))*width+(.5*sin(angle))*height,
                                                -(.5*sin(angle))*width+(.5*cos(angle))*height));
    listOfPoints.push_back(center + cv::Point2i((.5*cos(angle))*width-(.5*sin(angle))*height,
                                                -(.5*sin(angle))*width-(.5*cos(angle))*height));
    listOfPoints.push_back(center + cv::Point2i(-(.5*cos(angle))*width-(.5*sin(angle))*height,
                                                +(.5*sin(angle))*width-(.5*cos(angle))*height));
    cv::line(*imageToDraw,listOfPoints[0]*(1./imgResizeCoef),
            listOfPoints[1]*(1./imgResizeCoef),color,1);
    cv::line(*imageToDraw,listOfPoints[1]*(1./imgResizeCoef),
            listOfPoints[2]*(1./imgResizeCoef), color,1);
    cv::line(*imageToDraw,listOfPoints[2]*(1./imgResizeCoef),
            listOfPoints[3]*(1./imgResizeCoef), color,1);
    cv::line(*imageToDraw,listOfPoints[3]*(1./imgResizeCoef),
            listOfPoints[0]*(1./imgResizeCoef), color,1);
    drawArrow(*imageToDraw, center*(1./imgResizeCoef), (center + xVector)*(1./imgResizeCoef), color);
    drawArrow(*imageToDraw, center*(1./imgResizeCoef), (center + yVector)*(1./imgResizeCoef), color);
    cv::putText(*imageToDraw, "1",(center+xLabelLoc)*(1./imgResizeCoef),
                cv::FONT_HERSHEY_PLAIN, 1, color, 1, cv::LINE_AA);
    cv::putText(*imageToDraw, "2",(center+yLabelLoc)*(1./imgResizeCoef),
                cv::FONT_HERSHEY_PLAIN, 1, color, 1, cv::LINE_AA);

    // Update strain gauge mask
    const cv::Point* pts = (const cv::Point*) cv::Mat(listOfPoints).data;
    int npts = cv::Mat(listOfPoints).rows;
    cv::fillPoly(strainGaugeMask,&pts,&npts,1,CV_RGB(1,1,1));
    std::vector<double> solution = computeStrainGaugeResults(strainGaugeList[currentStrainGauge]);
    qDebug() << "Solution size: " << solution.size();
    if ((int)strainGaugeList.size()>0){
        if (solution.empty()){
            sgWidthLabel->setText(QString("Width: NaN"));
            sgHeightLabel->setText(QString("Height: NaN"));
            sgAngleLabel->setText(QString("Angle: NaN"));
            sgCenterLabel->setText(QString("Origin: (NaN,NaN)"));
            e11Label->setText(QString("E11: NaN"));
            e22Label->setText(QString("E22: NaN"));
            e12Label->setText(QString("E12: NaN"));
        } else {
            sgWidthLabel->setText("Width: "+ QString::number(solution[4],'e', 3) + unitLabel);
            sgHeightLabel->setText("Height: "+ QString::number(solution[5],'e', 3) + unitLabel);

            sgAngleLabel->setText("Angle: "+ QString::number((int)(solution[3])) + " deg");
            sgCenterLabel->setText("Origin: ("+ QString::number(solution[6],'g',3) + "," +
                    QString::number(solution[7],'g',3) + ")" );
            e11Label->setText("E11: " + QString::number(solution[0],'e', 3));
            e22Label->setText("E22: " + QString::number(solution[1],'e', 3));
            e12Label->setText("E12: " + QString::number(solution[2],'e', 3));
        }
    }
}

void virtualMeasurementTools::drawExtensometer(int extensometerIdx)
{
    if (extensometerList[extensometerIdx].points.size() == 2){
        cv::Point2i point1 = extensometerList[extensometerIdx].points[0];
        cv::Point2i point2 = extensometerList[extensometerIdx].points[1];
        cv::Point2i midPoint = 0.5*(point1 + point2);
        const float dialSize = .25;
        const float needleSize = .707f*(dialSize-.02f);
        const float lineSize = .5-dialSize;
        cv::Scalar color = CV_RGB(10,10,10);
        int extensometerNorm = (int)cv::norm(point2-point1);
        cv::circle(*imageToDraw ,midPoint*(1./imgResizeCoef),0.02*extensometerNorm*(1./imgResizeCoef), color,-1);
        cv::circle(*imageToDraw ,midPoint*(1./imgResizeCoef),dialSize*extensometerNorm*(1./imgResizeCoef),color,1);
        drawArrow(*imageToDraw ,midPoint*(1./imgResizeCoef),
                  (midPoint+cv::Point2i(needleSize*extensometerNorm,-needleSize*extensometerNorm))*(1./imgResizeCoef),color);


        cv::line(*imageToDraw ,point1*(1./imgResizeCoef), (point1 + lineSize*(point2-point1))*(1./imgResizeCoef),color,1);
        cv::line(*imageToDraw ,point2*(1./imgResizeCoef), (point2 + lineSize*(point1-point2))*(1./imgResizeCoef), color,1);
        cv::circle(*imageToDraw ,point1*(1./imgResizeCoef), 3, color);
        cv::circle(*imageToDraw ,point2*(1./imgResizeCoef), 3, color);
        std::vector<double> solution = computeExtensometerResults(extensometerList[extensometerIdx]);


        if (solution.empty()){
            extPointsLabel->setText( "Anchor points: (NaN,NaN)\n(NaN,NaN)");
            extLengthLabel->setText("Length: NaN");
            elongationLabel->setText("Elongation: NaN");
            elongationXLabel->setText("X-Projection: NaN");
            elongationYLabel->setText("Y-Projection: NaN");
        } else {
            qDebug() << "Extensometer0" << unitLabel << solution[0] << solution.size();
            elongationLabel->setText(QString("Elongation: ") + QString::number(solution[0],'e', 3) + unitLabel);
            qDebug() << "Extensometer1";
            extLengthLabel->setText("Length: " + QString::number(solution[7],'g', 3)+ unitLabel);
            qDebug() << "Extensometer2";
            elongationXLabel->setText("X-Projection: " + QString::number(solution[1],'e', 3)+ unitLabel);
            qDebug() << "Extensometer3";
            elongationYLabel->setText("Y-Projection: " + QString::number(solution[2],'e', 3)+ unitLabel);
            qDebug() << "Extensometer4";
            extPointsLabel->setText( "Anchor points: (" + QString::number(solution[3],'g', 3) + ","
                    + QString::number(solution[4],'g', 3) + ")\n(" + QString::number(solution[5],'g', 3) + ","
                    + QString::number(solution[6],'g', 3) + ")" );
            qDebug() << "Extensometer5";
        }

    }
}

void virtualMeasurementTools::setExtensometerPoint(){
    if(extensometerList[currentExtensometer].points.size()<2){
        extensometerList[currentExtensometer].points.push_back(cv::Point2i(0,0));
    } else{
        extensometerDrawingInProgress = false;
    }
}



void virtualMeasurementTools::drawArrow(cv::Mat &image, cv::Point2i p, cv::Point2i q, cv::Scalar color)
{
    ///From Mliki Hazar blog (Thanks!!!)
    /// http://mlikihazar.blogspot.com/2013/02/draw-arrow-opencv.html

    int arrowMagnitude = 7;
    int thickness=1;
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

int virtualMeasurementTools::isMouseNearPoint(cv::Point2i *currentPoint){
    //updatedPoint = -1;
    int distance;
    double epsilon = 15.*imgResizeCoef;
    if((currentStrainGauge>=0) && (currentStrainGauge<((int)strainGaugeList.size()))){
        strainGauge diplayedStrainGauge = strainGaugeList[currentStrainGauge];
        if(!strainGaugeDrawingCenter && !strainGaugeDrawingWidth
                && !updateAngleInProgress && !updateCenterInProgress && !updateWidthInProgress){
            distance = cv::norm(diplayedStrainGauge.center - *currentPoint);
            if(distance<epsilon){
                return mouseNearCenter;
            }
            cv::Point2i center = diplayedStrainGauge.center;
            int width = diplayedStrainGauge.width;
            int height = diplayedStrainGauge.height;
            double angle = diplayedStrainGauge.angle;
            std::vector<cv::Point2i> listOfPoints;
            listOfPoints.push_back(center + cv::Point2i(-(.5*cos(angle))*width+(.5*sin(angle))*height,
                                                        (.5*sin(angle))*width+(.5*cos(angle))*height));
            listOfPoints.push_back(center + cv::Point2i((.5*cos(angle))*width+(.5*sin(angle))*height,
                                                        -(.5*sin(angle))*width+(.5*cos(angle))*height));
            listOfPoints.push_back(center + cv::Point2i((.5*cos(angle))*width-(.5*sin(angle))*height,
                                                        -(.5*sin(angle))*width-(.5*cos(angle))*height));
            listOfPoints.push_back(center + cv::Point2i(-(.5*cos(angle))*width-(.5*sin(angle))*height,
                                                        +(.5*sin(angle))*width-(.5*cos(angle))*height));
            std::vector<cv::Point2i>::iterator cornerIter = listOfPoints.begin();
            for(; cornerIter!=listOfPoints.end();++cornerIter){
                distance = cv::norm(*cornerIter - *currentPoint);
                if (distance<epsilon)
                    return mouseNearCorner;
            }

            distance = cv::norm(diplayedStrainGauge.center +
                                cv::Point2i(cos(angle)*vectorLength,-sin(angle)*vectorLength) - *currentPoint);
            if (distance<epsilon){
                pointGrabbed = diplayedStrainGauge.center + cv::Point2i(cos(angle)*vectorLength,-sin(angle)*vectorLength);
                angleSet = angle;
                return mouseNearVector;
            }
            distance = cv::norm(diplayedStrainGauge.center +
                                cv::Point2i(-sin(angle)*vectorLength,-cos(angle)*vectorLength) - *currentPoint);
            if (distance<epsilon){
                pointGrabbed = diplayedStrainGauge.center + cv::Point2i(-sin(angle)*vectorLength,-cos(angle)*vectorLength);
                angleSet = angle;
                return mouseNearVector;
            }

        }
    } else if((currentExtensometer>=0) && (currentExtensometer<((int)extensometerList.size()))){
        extensometer diplayedExtensometer = extensometerList[currentExtensometer];
        if(!extensometerDrawingInProgress && !updateExtensometerInProgress){
            distance = cv::norm(diplayedExtensometer.points[0] - *currentPoint);
            if(distance<epsilon){
                pointGrabbedIdx = 0;
                return mouseNearExtensometer;
            }
            distance = cv::norm(diplayedExtensometer.points[1] - *currentPoint);
            if(distance<epsilon){
                pointGrabbedIdx = 1;
                return mouseNearExtensometer;
            }
        }
    }

    return 0;

}
void virtualMeasurementTools::exportResults(fileList *correlationFiles, drawOrigin *originAndAxesLayer){
    QString outputFileName = QFileDialog::getSaveFileName(0, "Choose a file name",
                                                          rootFolder.absolutePath(),"Comma Separated Value (*.csv)"); //;;Matlab file (*.mat)
    if (outputFileName.length() == 0){
        return;
    }
    if (QFileInfo(outputFileName).suffix() == "mat"){
        MATFile *pmat;
        pmat = matOpen(outputFileName.toUtf8(), "w");
        if (pmat == NULL) {
            QMessageBox noFileErrorMessage;
            noFileErrorMessage.setText(
                        "Cannot write mat file in chosen folder.");
            noFileErrorMessage.exec();
            return;
        }
        std::vector<mxArray*> strainGaugeMatlab;
        std::vector<cv::Mat> strainGaugeOutput;
        //Initialize Matlab matrices for strain gauges

        for(int j=0; j<strainGaugeList.size();++j){
            strainGaugeMatlab.push_back(mxCreateDoubleMatrix(correlationFiles->getFileNames().size(),3,mxREAL));
            strainGaugeOutput.push_back(cv::Mat::zeros(correlationFiles->getFileNames().size(),3,CV_64F));
        }
        std::vector<mxArray*> extensometerMatlab;
        std::vector<cv::Mat> extensometerOutput;
        if(!extensometerList.empty()){
            for(int j=0; j<strainGaugeList.size();++j){
                extensometerMatlab.push_back(mxCreateDoubleMatrix(correlationFiles->getFileNames().size(),3,mxREAL));
                extensometerOutput.push_back(cv::Mat::zeros(correlationFiles->getFileNames().size(),3,CV_64F));
            }
        }
        for(int fileIter = 0; fileIter < correlationFiles->getFileNames().size(); ++fileIter){
            dispSol.clear();
            if(displacements::openSolutionFile(fileIter, correlationFiles,&dispSol)){
                if(!dispSol.isEmpty()){
                    updateSolutionMap(originAndAxesLayer,fileIter, correlationFiles);
                    // Populate the strain gauge matrix
                    if(!strainGaugeList.empty()){
                        for (int sgIter = 0 ; sgIter < strainGaugeList.size(); ++sgIter){
                            currentStrainGauge = sgIter;
                            drawStrainGauge(sgIter);
                            std::vector<double> solution = computeStrainGaugeResults(strainGaugeList[sgIter]);
                            if (!solution.empty()){
                                strainGaugeOutput[sgIter].at<double>(fileIter,0) = solution[0];
                                strainGaugeOutput[sgIter].at<double>(fileIter,1) = solution[1];
                                strainGaugeOutput[sgIter].at<double>(fileIter,2) = solution[2];
                            }
                        }
                    }

                    // Populate the extensometer matrix
                    //                    for(int extIter = 0; extIter < extensometerList.size(); ++ extIter){
                    //                        std::vector<double> solution =
                    //                                computeExtensometerResults(extensometerList[extIter]);
                    //                        if (!solution.empty()){
                    //                            extensometerOutput.at<cv::Vec3d>(fileIter,extIter)[0] = solution[0];
                    //                            extensometerOutput.at<cv::Vec3d>(fileIter,extIter)[1] = solution[1];
                    //                            extensometerOutput.at<cv::Vec3d>(fileIter,extIter)[2] = solution[2];
                    //                        }
                    //                    }


                    qDebug() << "Post-processing solution updated";
                }
            }


        }
        for(int sgIter = 0; sgIter < (int)strainGaugeList.size(); ++sgIter){
            strainGauge sgOut = strainGaugeList[sgIter];
            memcpy((void *)(mxGetPr(strainGaugeMatlab[sgIter])),
                   (void *)strainGaugeOutput[sgIter].data,
                   strainGaugeOutput[sgIter].rows*strainGaugeOutput[sgIter].cols*sizeof(double));
            matPutVariable(pmat, sgOut.name->text().toUtf8(), strainGaugeMatlab[sgIter]);
            //mxDestroyArray(strainGaugeMatlab[sgIter]);

        }

        if(matClose(pmat) != 0) {
            QMessageBox noFileErrorMessage;
            noFileErrorMessage.setText(
                        "Error writing MAT file");
            noFileErrorMessage.exec();
        }

        //        if(matClose(pmat) != 0) {
        //            QMessageBox noFileErrorMessage;
        //            noFileErrorMessage.setText(
        //                        "Error writing MAT file");
        //            noFileErrorMessage.exec();
        //            return false;
        //
    } else {
        pd->setMaximum(correlationFiles->getFilePath().size());
        pd->setValue(0);
        pd->show();
        exportCanceled = false;
        qApp->processEvents();
        cv::Mat csvOutput = cv::Mat::zeros(correlationFiles->getFileNames().size(),
                                           3*(int)strainGaugeList.size() + 3*(int)extensometerList.size(),CV_64F);

        for(int fileIter = 0; fileIter < correlationFiles->getFileNames().size(); ++fileIter){
            if(exportCanceled)
                return;
            dispSol.clear();
            if(displacements::openSolutionFile(fileIter, correlationFiles,&dispSol)){
                updateSolutionMap(originAndAxesLayer,fileIter, correlationFiles);
                // Populate the strain gauge matrix
                if(!strainGaugeList.empty()){
                    for (int sgIter = 0 ; sgIter < strainGaugeList.size(); ++sgIter){
                        currentStrainGauge = sgIter;
                        drawStrainGauge(sgIter);
                        std::vector<double> solution = computeStrainGaugeResults(strainGaugeList[sgIter]);
                        if (!solution.empty()){
                            csvOutput.at<double>(fileIter,3*sgIter) = solution[0];
                            csvOutput.at<double>(fileIter,3*sgIter+1) = solution[1];
                            csvOutput.at<double>(fileIter,3*sgIter+2) = solution[2];
                        }
                    }
                }
                // Populate the extensometer matrix
                if(!extensometerList.empty()){
                    for (int extIter = 0 ; extIter < extensometerList.size(); ++extIter){
                        currentExtensometer = extIter;
                        drawExtensometer(extIter);
                        std::vector<double> solution = computeExtensometerResults(extensometerList[extIter]);
                        if (!solution.empty()){
                            qDebug() << "Break1";
                            csvOutput.at<double>(fileIter,3*(int)strainGaugeList.size() + 3*extIter) = solution[0];
                            csvOutput.at<double>(fileIter,3*(int)strainGaugeList.size() + 3*extIter+1) = solution[1];
                            csvOutput.at<double>(fileIter,3*(int)strainGaugeList.size() + 3*extIter+2) = solution[2];
                        }
                    }
                }
            }
            pd->setValue(fileIter);
            qApp->processEvents();
        }
        pd->close();
        std::ofstream outputFile;
        outputFile.open (outputFileName.toStdString());
        for (int sgIter = 0; sgIter<(int)strainGaugeList.size();++sgIter){
            outputFile << strainGaugeList[sgIter].name->text().toStdString();
            QString paramsOutput;
            paramsOutput =  ", Properties: Center= x:" + QString::number(strainGaugeList[sgIter].center.x)  + " y:"
                    + QString::number(strainGaugeList[sgIter].center.y) + " Angle= " + QString::number(strainGaugeList[sgIter].angle) + " rad" +
                    " Width=" + QString::number(strainGaugeList[sgIter].width) + " Height=" + QString::number(strainGaugeList[sgIter].height);
                    //"+, , ";
            outputFile << paramsOutput.toStdString();
        }
        for (int extIter = 0; extIter<(int)extensometerList.size();++extIter){
            outputFile << extensometerList[extIter].name->text().toStdString();
            if(extIter != (int)extensometerList.size()-1){
               outputFile << ", , , ";
            } else {
                outputFile << ", , \n";
            }

        }
        for (int sgIter = 0; sgIter<(int)strainGaugeList.size();++sgIter){
            outputFile << "E11, E22, E33, ";
        }
        for (int extIter = 0; extIter<(int)extensometerList.size();++extIter){
            if(extIter != (int)extensometerList.size()-1){
               outputFile << " Elongation, X-Proj, Y-Proj, ";
            } else {
                outputFile << " Elongation, X-Proj, Y-Proj \n";
            }
        }
        outputFile << cv::format(csvOutput,cv::Formatter::FMT_CSV);
        outputFile.close();
    }
}

std::vector<double> virtualMeasurementTools::computeExtensometerResults(virtualMeasurementTools::extensometer extensometerComputed)
{
    std::vector<double> solution;
    solution.clear();
    qDebug() << "Disp sol empty: " << dispSol.isEmpty();
    if (!dispSol.isEmpty()) {

        //outputMat = convertToUnits(dispExportArray[j])*outputMat;
        if ((extensometerComputed.points[0].x >= 0) && (extensometerComputed.points[0].y >= 0)&&
                (extensometerComputed.points[1].x >= 0) && (extensometerComputed.points[1].y >= 0) &&
                (extensometerComputed.points[0].x < dispU.cols) && (extensometerComputed.points[0].y < dispU.rows)&&
                (extensometerComputed.points[1].x < dispU.cols) && (extensometerComputed.points[1].y < dispU.rows)){
            // Gather displacement matrices
            if((maskDouble.at<double>(extensometerComputed.points[0]) == 1.) &&
                    (maskDouble.at<double>(extensometerComputed.points[1]) == 1.)){
                double point0U = dispU.at<double>(extensometerComputed.points[0]);
                double point0V = dispV.at<double>(extensometerComputed.points[0]);
                double point1U = dispU.at<double>(extensometerComputed.points[1]);
                double point1V = dispV.at<double>(extensometerComputed.points[1]);
                double point0x = coordX.at<double>(extensometerComputed.points[0]);
                double point0y = coordY.at<double>(extensometerComputed.points[0]);
                double point1x = coordX.at<double>(extensometerComputed.points[1]);
                double point1y = coordY.at<double>(extensometerComputed.points[1]);
                qDebug() << extensometerComputed.points[0].x << extensometerComputed.points[0].y
                        << extensometerComputed.points[1].x << extensometerComputed.points[1].y;
                qDebug() << "U Disp of point 0: " << point0U;
                qDebug() << "V Disp of point 0: " << point0V;
                qDebug() << "U Disp of point 1: " << point1U;
                qDebug() << "V Disp of point 1: " << point1V;

                // Initial length
                double length0 = sqrt(pow(point1x-point0x,2) + pow(point1y-point0y,2));
                qDebug() << length0;
                // Current Length
                double length = sqrt(pow(point1x+point1U-point0x-point0U,2) +
                                     pow(point1y+point1V-point0y - point0V,2));
                qDebug() << length;
                // Scale to chosen units
                double conversionFactor = convertToUnits();
                solution.push_back(conversionFactor*(length-length0));
                solution.push_back(conversionFactor*(point1U-point0U));
                solution.push_back(conversionFactor*(point1V-point0V));
                solution.push_back(conversionFactor*point0x);
                solution.push_back(conversionFactor*point0y);
                solution.push_back(conversionFactor*point1x);
                solution.push_back(conversionFactor*point1y);
                solution.push_back(conversionFactor*length0);
            }
        }
    }
    return solution;
}


std::vector<double> virtualMeasurementTools::computeStrainGaugeResults(virtualMeasurementTools::strainGauge computedStrainGauge)
{
    const double PI = 3.141592653;
    double conversion = convertToUnits();
    std::vector<double> solution;
    qDebug() << "Disp sol empty: " << dispSol.isEmpty();
    if (!dispSol.isEmpty()) {
        if ((computedStrainGauge.center.x >= 0) && (computedStrainGauge.center.y >= 0)&&
                (computedStrainGauge.center.x < dispU.cols) && (computedStrainGauge.center.y < dispU.rows)){
            // Multiply the strain gauge mask with the solution mask
            cv::Mat mask = maskDouble.mul(strainGaugeMask);
            mask.convertTo(mask,CV_8U);
            // Average strains
            double sgExx = cv::mean(Exx,mask)[0];
            double sgEyy = cv::mean(Eyy,mask)[0];
            double sgExy = cv::mean(Exy,mask)[0];
            qDebug() << "Exx:" << sgExx;
            double angle;
            if(originAndAxesLayer.flipXY){
                angle = computedStrainGauge.angle +.5*PI -
                        originAndAxesLayer.getAngle();
            } else{
                angle = originAndAxesLayer.getAngle() + PI
                        - computedStrainGauge.angle;
            }



            cv::Matx22d strainXYBasis(sgExx,sgExy,sgExy,sgEyy);
            cv::Matx22d rotationMatrix(cos(angle),-sin(angle),sin(angle),cos(angle));
            cv::Matx22d strain12Basis = rotationMatrix.t()*strainXYBasis*rotationMatrix;
            qDebug() << originAndAxesLayer.getAngle() <<
                        computedStrainGauge.angle;
            // Rotate solution
            solution.push_back(strain12Basis(0,0));
            solution.push_back(strain12Basis(1,1));
            solution.push_back(strain12Basis(0,1));
            qDebug() << solution[0] << solution[1] << solution[2];



            double totalAngle;
            const double PI = 3.141592653;
            if(originAndAxesLayer.flipXY){
                totalAngle = computedStrainGauge.angle +.5*PI -
                        originAndAxesLayer.getAngle();
            } else{
                totalAngle = originAndAxesLayer.getAngle() + PI
                        - computedStrainGauge.angle;
            }
            totalAngle = fmod(totalAngle,2.*PI);
            if(totalAngle < -PI)
                totalAngle = fmod(totalAngle- PI, 2.*PI) + PI;
            else if (totalAngle > PI)
                totalAngle = fmod(totalAngle + PI, 2.*PI) - PI;


            solution.push_back(totalAngle*180./PI);
            solution.push_back(conversion*computedStrainGauge.width);
            solution.push_back(conversion*computedStrainGauge.height);
            solution.push_back(conversion*coordX.at<double>(computedStrainGauge.center));
            solution.push_back(conversion*coordY.at<double>(computedStrainGauge.center));
        }


    }
    return solution;
}

double virtualMeasurementTools::convertToUnits()
{
    double unitScaleFactor;
    switch (originAndAxesLayer.unitDisplayFlag) {
    case drawOrigin::pixelUnit:
        unitLabel = " px";
        unitScaleFactor = 1.;
        break;
    case drawOrigin::mmUnit:
        unitLabel = " mm";
        unitScaleFactor = cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::cmUnit:
        unitLabel = " cm";
        unitScaleFactor = .01*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::mUnit:
        unitLabel = " m";
        unitScaleFactor = .001*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::inUnit:
        unitLabel = " in";
        unitScaleFactor = 0.0393701*cam1Calibration->mmPerPixel;
        break;
    case drawOrigin::ftUnit:
        unitLabel = " ft";
        unitScaleFactor = 0.00328084*cam1Calibration->mmPerPixel;
        break;
    default:
        unitLabel = " px";
        unitScaleFactor = 1.;
        break;
    }
    return unitScaleFactor;
}

void virtualMeasurementTools::loadDispAndCoords(){
    if (!dispSol.isEmpty()) {
        dispSol.computeMaskAndLimits(displacements::getU,&originAndAxesLayer);
        dispSol.maskDisplay.convertTo(maskDouble,CV_64F);
        // If mask value is negative, make it zero, else make it 1
        //  Apply the slope and offset for the colormap
        for ( cv::Mat_<double>::iterator maskDoubleIter = maskDouble.begin<double>(); maskDoubleIter != maskDouble.end<double>(); ++maskDoubleIter)
        {
            *maskDoubleIter = *maskDoubleIter > 0. ? 1.:0.;
        }
        dispU = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getV,&originAndAxesLayer);
        dispV = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getX,&originAndAxesLayer);
        coordX = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getY,&originAndAxesLayer);
        coordY = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getExx,&originAndAxesLayer);
        Exx = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getExy,&originAndAxesLayer);
        Exy = dispSol.results.mul(maskDouble);
        dispSol.computeMaskAndLimits(displacements::getEyy,&originAndAxesLayer);
        Eyy = dispSol.results.mul(maskDouble);
    } else {
        //maskDouble = cv::Mat::zeros()
    }
}

void virtualMeasurementTools::clear()
{
    strainGaugeList.clear();
    extensometerList.clear();
}


void virtualMeasurementTools::write(cv::FileStorage &fs) const
{
    fs << "{" << "strainGauges" << "[";
    for (int i=0; i<strainGaugeList.size();++i){
        fs << "{" << "name" << strainGaugeList[i].name->text().toStdString()
           << "center" << strainGaugeList[i].center
           << "width" << strainGaugeList[i].width
           << "height" << strainGaugeList[i].height
           << "angle" << strainGaugeList[i].angle << "}";
    }
    fs << "]"
       << "extensometers" << "[";
    for (int i=0; i<extensometerList.size();++i){
        fs << "{" << "name" << extensometerList[i].name->text().toStdString()
           << "point1" << extensometerList[i].points[0]
           << "point2" << extensometerList[i].points[1] << "}";
    }
    fs << "]" << "}";
}

void virtualMeasurementTools::read(const cv::FileNode &node)
{
    cv::FileNodeIterator it = node["strainGauges"].begin(), it_end = node["strainGauges"].end(); // Go through the node
    for (; it != it_end; ++it){
        strainGauge newStrainGauge;
        newStrainGauge.name = new QListWidgetItem((QString::fromStdString((*it)["name"])));
        newStrainGauge.name->setFlags (newStrainGauge.name->flags () | Qt::ItemIsEditable);
        newStrainGauge.height = (int)(*it)["height"];
        newStrainGauge.width = (int)(*it)["width"];
        newStrainGauge.angle = (double)(*it)["angle"];
        cv::FileNodeIterator ptsIt = (*it)["center"].begin(), ptsItEnd = (*it)["center"].end();
        for(;ptsIt != ptsItEnd; ++ptsIt){
            newStrainGauge.center.x = (int)*ptsIt;
            ++ptsIt;
            newStrainGauge.center.y = (int)*ptsIt;
        }
        strainGaugeList.push_back(newStrainGauge);
    }

    cv::FileNodeIterator itExt = node["extensometers"].begin(), itExt_end = node["extensometers"].end(); // Go through the node
    for (; itExt != itExt_end; ++itExt){
        extensometer newExtensometer;
        newExtensometer.name = new QListWidgetItem((QString::fromStdString((*itExt)["name"])));
        newExtensometer.name->setFlags (newExtensometer.name->flags () | Qt::ItemIsEditable);
        cv::FileNodeIterator ptsIt1 = (*itExt)["point1"].begin(), ptsIt1End = (*itExt)["point1"].end();
        cv::Point2i point1;
        for(;ptsIt1 != ptsIt1End; ++ptsIt1){
            point1.x = (int)*ptsIt1;
            ++ptsIt1;
            point1.y = (int)*ptsIt1;
        }
        newExtensometer.points.push_back(point1);
        cv::FileNodeIterator ptsIt2 = (*itExt)["point2"].begin(), ptsIt2End = (*itExt)["point2"].end();
        cv::Point2i point2;
        for(;ptsIt2 != ptsIt2End; ++ptsIt2){
            point2.x = (int)*ptsIt2;
            ++ptsIt2;
            point2.y = (int)*ptsIt2;
        }
        newExtensometer.points.push_back(point2);
        extensometerList.push_back(newExtensometer);
    }
}


