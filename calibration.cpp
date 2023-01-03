

#include "calibration.h"

calibration::calibration(): m_squareLength(10.0), m_flag(0), m_mustInitUndistort(true)
{
    pxLine = 1.;
    unitLine = 1.;
    mmPerPixel = 0.;
    unitFlag = 0;
}
void calibration::setComboBoxes(QComboBox *cameraMakerWidget, QComboBox *cameraWidget,
                                QComboBox *lensMakerWidget, QComboBox *lensWidget,
                                QComboBox *focalLengthWidget){
    this->cameraMakerWidget = cameraMakerWidget;
    this->cameraWidget = cameraWidget;
    this->lensMakerWidget = lensMakerWidget;
    this->lensWidget = lensWidget;
    this->focalLengthWidget = focalLengthWidget;
}

void calibration::enableComboBoxes(bool val)
{
    this->cameraMakerWidget->setEnabled(val);
    this->cameraWidget->setEnabled(val);
    this->lensMakerWidget->setEnabled(val);
    this->lensWidget->setEnabled(val);
    this->focalLengthWidget->setEnabled(val);
}



void calibration::parseMakerLists()
{
    cameraMakerWidget->clear();
    if (cameraMakerList.size() > 0){
        for (std::vector<maker>::iterator makerIter = cameraMakerList.begin();
             makerIter != cameraMakerList.end(); ++makerIter){
            cameraMakerWidget->addItem(makerIter->name);
        }

        //parseCameraList(0);
    }
    lensMakerWidget->clear();
    if (lensMakerList.size() > 0){
        for (std::vector<maker>::iterator makerIter = lensMakerList.begin();
             makerIter != lensMakerList.end(); ++makerIter){
            lensMakerWidget->addItem(makerIter->name);
        }
        //parseLensList(0);
    }
}

void calibration::parseCameraList(int makerIdx)
{
    if(makerIdx < cameraMakerWidget->count()){
        cameraWidget->clear();
        if (cameraMakerList[makerIdx].cameraList.size() > 0){
            for (std::vector<camera>::iterator cameraIter = cameraMakerList[makerIdx].cameraList.begin();
                 cameraIter != cameraMakerList[makerIdx].cameraList.end(); ++cameraIter){
                cameraWidget->addItem(cameraIter->name);
            }
        }
    }
}

void calibration::parseLensList(int makerIdx)
{
    if(makerIdx < lensMakerWidget->count()){
        lensWidget->clear();
        if (lensMakerList[makerIdx].lensList.size() > 0){
            for (std::vector<lens>::iterator lensIter = lensMakerList[makerIdx].lensList.begin();
                 lensIter != lensMakerList[makerIdx].lensList.end(); ++lensIter){
                lensWidget->addItem(lensIter->name);
            }
            parseFocalLengthList(0);
        }
    }
}

void calibration::parseFocalLengthList(int modelIdx)
{
    int bestCrop = getBestLensLab();
    if(modelIdx < lensWidget->count()){
        focalLengthWidget->clear();
        if(!lensMakerList[lensMakerWidget->currentIndex()].lensList[lensWidget->currentIndex()].lensLab[bestCrop].lensProps.empty()){
            std::vector<calibration::lensProperties> currentLensPropList =
                    lensMakerList[lensMakerWidget->currentIndex()].lensList[lensWidget->currentIndex()].lensLab[bestCrop].lensProps;
            for (std::vector<calibration::lensProperties>::iterator lensPropIter = currentLensPropList.begin();
                 lensPropIter != currentLensPropList.end(); ++lensPropIter){
                double focalLength = lensPropIter->focalLength;
                if (focalLength == 0.){
                    focalLengthWidget->addItem("NA");
                } else {
                    focalLengthWidget->addItem(QString::number(focalLength) + "mm");
                }
            }
        }
    }
}

int calibration::getBestLensLab()
{
    lens currentLens = this->lensMakerList[this->getLensMakerIdx()].
            lensList[this->getLensIdx()];
    camera currentCamera = this->cameraMakerList[this->getCameraMakerIdx()].
            cameraList[this->getCameraIdx()];
    double prevDifference = 10.;
    int bestIdx = 0;
    for (int i =0; i < (int)currentLens.lensLab.size(); ++i){
        if (abs(currentCamera.cropFactor-currentLens.lensLab[i].cropFactor) < prevDifference){
            bestIdx = i;
            prevDifference = abs(currentCamera.cropFactor-currentLens.lensLab[i].cropFactor);
        }
    }
    return bestIdx;
}

void calibration::loadLensFunDatabase()
{
    QDir lensfunDb(QCoreApplication::applicationDirPath() + "/lensfundb");
    qDebug() << lensfunDb;
    QStringList xmlFileList = lensfunDb.entryList(QStringList() << "*.xml",QDir::Files);
    for (int fileIter = 0; fileIter < (int)xmlFileList.size(); ++fileIter){
        QFile currentFile(lensfunDb.path() +QDir::separator() + xmlFileList[fileIter]);
        //qDebug() << lensfunDb.path() +QDir::separator() + xmlFileList[fileIter];
        if (!currentFile.open(QIODevice::ReadOnly)) {
            //qDebug() << "Can't open file: " << currentFile.fileName();
            return;
        }
        QXmlStreamReader xmlStream;
        xmlStream.setDevice(&currentFile);
        while(!xmlStream.atEnd()){
            QXmlStreamReader::TokenType tt = xmlStream.readNext();
            if (tt == QXmlStreamReader::StartElement){
                bool cameraLensBar;
                QString name = xmlStream.name().toString();
                if (name == "camera"){
                    cameraLensBar = true;
                    parseCalibrationElement(cameraMakerList, xmlStream, cameraLensBar);
                } else if (name == "lens"){
                    cameraLensBar = false;
                    parseCalibrationElement(lensMakerList, xmlStream, cameraLensBar);
                }
            }
        }
    }
    //qDebug() << cameraMakerList[0].name;
    // Sort all lists in alphabetical order
    std::sort(cameraMakerList.begin(),cameraMakerList.end(),compareNames);
    for(std::vector<maker>::iterator cameraMakerIter = cameraMakerList.begin();
        cameraMakerIter != cameraMakerList.end(); ++cameraMakerIter){
        std::sort(cameraMakerIter->cameraList.begin(),cameraMakerIter->cameraList.end(),compareCameraNames);
    }
    std::sort(lensMakerList.begin(),lensMakerList.end(),compareNames);
    for(std::vector<maker>::iterator lensMakerIter = lensMakerList.begin();
        lensMakerIter != lensMakerList.end(); ++lensMakerIter){
        std::sort(lensMakerIter->lensList.begin(),lensMakerIter->lensList.end(),compareLensNames);
    }

    // Add one more item for custom data
    maker customCameraMaker;
    maker customLensMaker;
    customCameraMaker.name = "Custom";
    customLensMaker.name = "Custom";
    camera customCam;
    customCam.name = "Custom";
    customCam.cropFactor = 1.0;
    lens customLens;
    customLens.name = "Custom";
    lensProperties customLensProp;
    lensLabResult customLensLab;
    customLensLab.cropFactor = 1.0;
    customLensProp.focalLength = 0.;
    customLensProp.a =0.;
    customLensProp.b = 0.;
    customLensProp.c = 0.;
    customLensLab.lensProps.push_back(customLensProp);
    customLens.lensLab.push_back(customLensLab);
    customCameraMaker.cameraList.push_back(customCam);
    customLensMaker.lensList.push_back(customLens);
    cameraMakerList.push_back(customCameraMaker);
    lensMakerList.push_back(customLensMaker);

    parseMakerLists();
}

int calibration::makerExists(QString name, std::vector<maker> &makerList){
    int iterIdx = 0;
    for (std::vector<maker>::iterator makerIter = makerList.begin();
         makerIter != makerList.end(); ++makerIter, ++iterIdx){
        if(makerIter->name == name){
            return iterIdx;
        }
    }
    //qDebug() << "New Maker:" << name;
    return -1;
}

int calibration::cameraExists(QString name, int makerIdx){
    int iterIdx = 0;
    for (std::vector<camera>::iterator modelIter = cameraMakerList[makerIdx].cameraList.begin();
         modelIter != cameraMakerList[makerIdx].cameraList.end(); ++modelIter, ++iterIdx){
        if(modelIter->name == name){
            return iterIdx;
        }
    }
    //qDebug() << "New Model:" << name;
    return -1;
}

int calibration::lensExists(QString name, int makerIdx){
    int iterIdx = 0;
    for (std::vector<lens>::iterator modelIter = lensMakerList[makerIdx].lensList.begin();
         modelIter != lensMakerList[makerIdx].lensList.end(); ++modelIter, ++iterIdx){
        if(modelIter->name == name){
            return iterIdx;
        }
    }
    //qDebug() << "New Model:" << name;
    return -1;
}

calibration::lensProperties calibration::getLensDistortion(QXmlStreamReader &xmlStream)
{
    lensProperties newLensProp;
    QXmlStreamAttributes lensAttributes = xmlStream.attributes();
    newLensProp.focalLength = lensAttributes.value("focal").toDouble();
    if (lensAttributes.value("model").toString() == "ptlens"){
        newLensProp.a = lensAttributes.value("a").toDouble();
        newLensProp.b = lensAttributes.value("b").toDouble();
        newLensProp.c = lensAttributes.value("c").toDouble();
    } else if ((lensAttributes.value("model").toString() == "poly3") ||
               (lensAttributes.value("model").toString() == "poly5")){
        newLensProp.a = 0.;
        newLensProp.c = lensAttributes.value("k1").toDouble();
        newLensProp.b = 0.;
        //qDebug() << "K1 exists";
    }
    //qDebug() << "Lens Properties: " << newLensProp.focalLength << newLensProp.a << newLensProp.b << newLensProp.c;
    return newLensProp;
}

void calibration::parseCalibrationElement(std::vector<maker> &makerList, QXmlStreamReader &xmlStream,
                                          bool cameraLensBar)
{
    int makerIdx;
    int modelIdx;
    double cropFactor = 0.;
    std::vector<lensProperties> lensPropList;
    QString modelName;
    std::vector<QString> tempMakers;
    std::vector<QString> tempModel;
    while (!xmlStream.atEnd()){
        QXmlStreamReader::TokenType subtt = xmlStream.readNext();
        if (subtt == QXmlStreamReader::StartElement){
            QString name = xmlStream.name().toString();
            /// Stack makers
            if (name == "maker"){
                tempMakers.push_back(xmlStream.readElementText());
            }
            /// Stack models
            else if ((name == "model")){
                tempModel.push_back(xmlStream.readElementText());
                /// Get crop factor
            } else if (name == "cropfactor"){
                cropFactor = xmlStream.readElementText().toDouble();
                /// Get focal length
            } else if (name == "distortion"){
                lensPropList.push_back(getLensDistortion(xmlStream));
            }
        } else if (subtt == QXmlStreamReader::EndElement){
            if ((xmlStream.name().toString() == "camera") || (xmlStream.name().toString() == "lens"))
                break;
        }
    }
    // Look for shortest maker name
    if(!tempMakers.empty()){
        std::sort(tempMakers.begin(), tempMakers.end(), compareLength);
        makerIdx = makerExists(tempMakers[0], makerList);
        if(makerIdx == -1){
            maker newMaker;
            newMaker.name = tempMakers[0];
            makerList.push_back(newMaker);
            makerIdx = (int)makerList.size()-1;
        }
    }
    if(!tempModel.empty()){
        std::sort(tempModel.begin(), tempModel.end(), compareLength);
        if(cameraLensBar){
            modelIdx = cameraExists(tempModel[0],makerIdx);
            if(modelIdx == -1){
                camera newCamera;
                newCamera.name = tempModel[0];
                makerList[makerIdx].cameraList.push_back(newCamera);
                modelIdx = (int)makerList[makerIdx].cameraList.size()-1;
            }
            makerList[makerIdx].cameraList[modelIdx].cropFactor = cropFactor;
        } else {
            if (!lensPropList.empty()){
                lensLabResult newLensLab;
                newLensLab.cropFactor = cropFactor;
                newLensLab.lensProps = lensPropList;
                modelIdx = lensExists(tempModel[0],makerIdx);
                if(modelIdx == -1){
                    lens newLens;
                    newLens.name = tempModel[0];

                    newLens.lensLab.push_back(newLensLab);
                    makerList[makerIdx].lensList.push_back(newLens);
                    modelIdx = (int)makerList[makerIdx].lensList.size()-1;
                } else {
                    makerList[makerIdx].lensList[modelIdx].lensLab.push_back(newLensLab);
                }
            }
        }
    }
}

void calibration::remap(const cv::Mat &image, cv::Mat &undistorted){
    //apply mapping functions

    cv::remap(image,undistorted,m_map1,m_map2,cv::INTER_LINEAR);

    cv::Mat resizedUndistorted;

    cv::resize(undistorted,resizedUndistorted,cv::Size(667,500),0,0);

    cv::imshow("UNDISTORTED PICTURE",resizedUndistorted);

    cv::waitKey(50);


}


int calibration::getCameraMakerIdx()
{
    return cameraMakerWidget->currentIndex();
}

int calibration::getCameraIdx()
{
    return cameraWidget->currentIndex();
}

int calibration::getLensMakerIdx()
{
    return lensMakerWidget->currentIndex();
}

int calibration::getLensIdx()
{
    return lensWidget->currentIndex();
}

int calibration::getFocalLengthIdx()
{
    return focalLengthWidget->currentIndex();
}

bool calibration::isCameraCustom()
{
    if ((cameraMakerWidget->currentIndex() == cameraMakerWidget->count()-1) &&
            (cameraWidget->currentIndex() == cameraWidget->count()-1)){
        return true;
    }
    return false;
}

bool calibration::isLensCustom()
{
    if ((lensMakerWidget->currentIndex() == lensMakerWidget->count()-1) &&
            (lensWidget->currentIndex() == lensWidget->count()-1)){
        return true;
    }
    return false;
}

void calibration::setCameraCustom(double val)
{
    cameraMakerList.back().cameraList.back().cropFactor = val;
    if (!isCameraCustom()){
        cameraMakerWidget->setCurrentIndex(cameraMakerWidget->count()-1);
        cameraWidget->setCurrentIndex(cameraWidget->count()-1);
    }
}

void calibration::setLensCustom(double aVal, double bVal, double cVal)
{
    lensMakerList.back().lensList.back().lensLab[0].cropFactor = 1.;
    lensMakerList.back().lensList.back().lensLab[0].lensProps[0].a = aVal;
    lensMakerList.back().lensList.back().lensLab[0].lensProps[0].b = bVal;
    lensMakerList.back().lensList.back().lensLab[0].lensProps[0].c = cVal;
    if (!isLensCustom()){
        lensMakerWidget->setCurrentIndex(lensMakerWidget->count()-1);
        lensWidget->setCurrentIndex(lensWidget->count()-1);
    }
}

void calibration::write(cv::FileStorage& fs) const //Write serialization for this class
{


    fs << "{"
       <<  "pxLine" << pxLine
        <<  "unitLine" << unitLine
         <<  "mmPerPixel" << mmPerPixel
          <<  "ratioDisplayed" << ratioDisplayed
           <<  "unitFlag" << unitFlag
            <<"}";
}
void calibration::read(const cv::FileNode& node) //Read serialization for this class
{
    pxLine = (double)node["pxLine"];
    unitLine = (double)node["unitLine"];
    mmPerPixel = (double)node["mmPerPixel"];
    ratioDisplayed = (double)node["ratioDisplayed"];
    unitFlag = (double)node["unitFlag"];
}
