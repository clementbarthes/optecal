#include "filelist.h"


fileList::fileList(int fileType, QDir rootFolder)
{
    this->fileType = fileType;
    this->rootFolder = rootFolder;
    sortFlag = 0;
}

fileList::fileList()
{
    //  this->fileType = correlationFiles;
}

fileList::~fileList()
{
    fileDef.clear();
}

void fileList::setListDisplay(QListWidget* listWidget){
    this->listWidget = listWidget;
}

void fileList::appendList(QStringList newFilePath)
{
    for (int i = 0; i < newFilePath.size(); ++i)
    {
        fileAttributes tmpFileAttribute = {
            rootFolder.relativeFilePath(newFilePath[i]),
            QFileInfo(rootFolder.absoluteFilePath(newFilePath[i])).baseName(),
            QFileInfo(rootFolder.absoluteFilePath(newFilePath[i])).lastModified(),
            QFileInfo(rootFolder.absoluteFilePath(newFilePath[i])).lastModified(),
            false,
            false,
            std::vector<cv::Point2f>()
        };
        // Remove from list if file already exists
        fileDef.removeAll(tmpFileAttribute);
        fileDef.append(tmpFileAttribute);
    }
    sortFiles(sortFlag);
    // Set the first image as reference if files are for correlation
    if(fileType==correlationFiles) fileDef[0].refImage = true;
}

QStringList fileList::getFilePath()
{
    QStringList filePath;
    for (int i = 0; i < fileDef.size(); ++i)
    {
        filePath << rootFolder.filePath(fileDef[i].filePath);
    }
    return filePath;
}

QString fileList::getFilePath(int idx)
{
    if (idx>=0){
        return rootFolder.filePath(fileDef[idx].filePath);
    } else return rootFolder.filePath(fileDef[0].filePath);
}

QStringList fileList::getFileNames()
{
    QStringList listOfFiles;
    for (int i = 0; i < fileDef.size(); ++i)
    {
        listOfFiles << fileDef[i].fileNames;
    }
    return listOfFiles;
}
QString fileList::getFileNames(int idx)
{
    return fileDef[idx].fileNames;
}

QList<QDateTime> fileList::getFileDates()
{
    QList<QDateTime> fileDates;
    for (int i = 0; i < fileDef.size(); ++i)
    {
        fileDates << fileDef[i].fileDates;
    }
    return fileDates;
}

QDateTime fileList::getFileDates(int idx)
{
    return fileDef[idx].fileDates;
}

void fileList::sortFiles(int sortIndex){
    sortFlag = sortIndex;
    if (sortIndex == sortByNames ){
        std::sort(fileDef.begin(), fileDef.end(),naturalSortCompare);
    }else if (sortIndex == sortByDateCreated ){
        std::sort(fileDef.begin(), fileDef.end(),compareDates);
    }else if (sortIndex == sortByDateModified){
        std::sort(fileDef.begin(), fileDef.end(),compareDatesModified);
    }
}

void fileList::setRefImage(int idx){
    for (int i = 0; i < fileDef.size(); ++i)
    {
        // Remove current Reference image
        if (fileDef[i].refImage){
            fileDef[i].refImage = false;
        }
    }
    // Set idx as the new reference image
    fileDef[idx].refImage = true;
}
int fileList::getRefImageIdx() const
{
    for (int i = 0; i < fileDef.size(); ++i)
    {
        if(fileDef[i].refImage){
            return i;
        }
    }
    return -1;
}

bool fileList::isRefImage(int idx)
{
    return fileDef[idx].refImage;
}
QString fileList::getRefImagePath(){
    for (int i = 0; i < fileDef.size(); ++i)
    {
        if(fileDef[i].refImage){
            return rootFolder.filePath(fileDef[i].filePath);
        }
    }
    return 0;
}

int fileList::getNoFiles()
{
    return fileDef.size();
}


cv::Mat fileList::getRefImage()
{
    cv::Mat image;
    for (int i = 0; i < fileDef.size(); ++i)
    {
        if(fileDef[i].refImage){
            //Open images in grayscale. If the images are opened with this function they can be 16-bits
            image = cv::imread((rootFolder.filePath(fileDef[i].filePath).toLatin1()).data(),cv::ImreadModes::IMREAD_ANYDEPTH | cv::ImreadModes::IMREAD_GRAYSCALE );
            image.convertTo(image,CV_32F);
            return image;
        }
    }
    return image;
}

cv::Mat fileList::getImage(int idx)
{
    cv::Mat image;
    //Open images in grayscale. If the images are opened with this function they can be 16-bits
    image = cv::imread((rootFolder.filePath(fileDef[idx].filePath).toLatin1()).data(),cv::ImreadModes::IMREAD_ANYDEPTH | cv::ImreadModes::IMREAD_GRAYSCALE);
    image.convertTo(image,CV_32F);
    return image;
}

cv::Mat fileList::getImage8bits(int idx)
{
    cv::Mat image;
    //Open images in grayscale and 8 bits
    image = cv::imread((rootFolder.filePath(fileDef[idx].filePath).toLatin1()).data(),cv::ImreadModes::IMREAD_GRAYSCALE);
    return image;
}

cv::Mat fileList::getImageColor8bits(int idx)
{
    cv::Mat image;
    //Open images in grayscale and 8 bits
    image = cv::imread((rootFolder.filePath(fileDef[idx].filePath).toLatin1()).data(), cv::ImreadModes::IMREAD_GRAYSCALE);
    image.convertTo(image,CV_8UC3);
    return image;
}

bool fileList::getIsSolved(int index)
{
    return fileDef[index].isSolved;
}

void fileList::setIsSolved(int index, bool solved)
{
    fileDef[index].isSolved = solved;
}

void fileList::setCurrentImgIdx(int currentImg)
{
    this->currentImg = currentImg;
    //listWidget->setCurrentRow(currentImg);

}

int fileList::getCurrentImgIdx()
{
    return currentImg;
}

int fileList::getImageType()
{
    return fileType;
}

void fileList::deleteImage(int imgIdx)
{
    // If deleted image is ref image, set first image as the new reference
    if((fileType == correlationFiles) && (imgIdx == getRefImageIdx())){
        fileDef.removeAt(imgIdx);
        setRefImage(0);
    }
    else{
        fileDef.removeAt(imgIdx);
    }

}

QString fileList::getCurrentImgPath()
{
    return rootFolder.filePath(fileDef[currentImg].filePath);
}

void fileList::updateRootFolder(QDir newRootFolder)
{
    for (int i = 0; i < fileDef.size(); ++i)
    {
        // Rewrite all paths as absolute using the old rootFolder
        fileDef[i].filePath = rootFolder.absoluteFilePath(fileDef[i].filePath);
        qDebug() << fileDef[i].filePath;
        // Rewrite all paths relative to the new rootFolder
        fileDef[i].filePath = newRootFolder.relativeFilePath(fileDef[i].filePath);
    }
    // Update rootFolder
    rootFolder = newRootFolder;
}

void fileList::updateImageFolder(QString newFolder)
{
    for (int i = 0; i < fileDef.size(); ++i)
    {
        // Rewrite all paths as absolute using the old rootFolder
        fileDef[i].filePath = QDir(newFolder).absoluteFilePath(QFileInfo(fileDef[i].filePath).fileName());

        // Rewrite all paths relative to the new rootFolder
        fileDef[i].filePath = rootFolder.relativeFilePath(fileDef[i].filePath);
        qDebug() <<fileDef[i].filePath;
    }
}

void fileList::setImageCorners(std::vector<cv::Point2f> imageCorners, int imgIdx){
    fileDef[imgIdx].imageCorners.clear();
    fileDef[imgIdx].imageCorners = imageCorners;
}

std::vector<cv::Point2f> fileList::getImageCorners(int imgIdx){
    return fileDef[imgIdx].imageCorners;
}

void fileList::clear()
{
    fileDef.clear();
    listWidget->clear();

}

void fileList::write(cv::FileStorage& fs) const                        //Write serialization for this class
{
    fs << "{" << "filePath" << "[";
    for (int i=0; i<fileDef.size();++i){
        fs<<fileDef[i].filePath.toStdString();
    }
    fs << "]";
    int refImage = this->getRefImageIdx();
    fs << "refImage" << refImage;
    fs << "sortFlag" << sortFlag << "}";
}
void fileList::read(const cv::FileNode& node)                          //Read serialization for this class
{
    QStringList fileList;
    if (node["filePath"].size() > 0){
    cv::FileNodeIterator it = node["filePath"].begin(), it_end = node["filePath"].end(); // Go through the node
    for (; it != it_end; ++it){
        fileList.append(QString::fromStdString(*it));
    }
    this->sortFlag = (int)(node["sortFlag"]);
    this->appendList(fileList);
    if (fileType == correlationFiles)
        this->setRefImage((int)(node["refImage"]));
    } else {
        qDebug() << "No file";
    }

}




