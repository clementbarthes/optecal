#include "rawconverter.h"

#define snprintf _snprintf
#define TOFF(ptr) ((char *)(&(ptr)) - (char *)th)

#define P1 RawProcessor.imgdata.idata
#define S RawProcessor.imgdata.sizes
#define C RawProcessor.imgdata.color
#define T RawProcessor.imgdata.thumbnail
#define P2 RawProcessor.imgdata.other
#define rawParams RawProcessor.imgdata.params


int rawConverter::rotationIndex = 0;

QLineEdit* rawConverter::aCal = 0;
QLineEdit* rawConverter::bCal = 0;
QLineEdit* rawConverter::cCal = 0;
QLineEdit* rawConverter::cropFactorEdit = 0;
QCheckBox* rawConverter::distortionCheck = 0;
calibration* rawConverter::cam1Calibration = 0;
cv::Mat rawConverter::remapX = cv::Mat::zeros(1,1,CV_32F);
cv::Mat rawConverter::remapY = cv::Mat::zeros(1,1,CV_32F);


rawConverter::rawConverter(QString filePath)
{
    this->filePath = filePath;
    fileName = QString("exported").toLatin1().data();
}

void rawConverter::run()
{
    LibRaw RawProcessor;
    cv::Mat cvImage, cvImageR,cvImageG1,cvImageB,cvImageG2;

    const int kernelSize = 15;
    int halfKernel = kernelSize/2;
    const int upSamplingRatio =2;
    const double PI = 3.141592653;
    cv::Mat lanczosKernel(kernelSize,1,CV_64F);
    int n = -halfKernel;
    for (int j=0; j< kernelSize;++j, ++n){
        if(n== 0) lanczosKernel.at<double>(j,1) = 1.;
        else{
            double x = (double)n*PI/(double)upSamplingRatio;
            lanczosKernel.at<double>(j,1) = (double)halfKernel*sin(x/(double)halfKernel)*sin(x)/pow(x,2);
        }
    }

    if( (RawProcessor.open_file(filePath.toUtf8())) == LIBRAW_SUCCESS){
        qDebug() << "Raw image opened";
        qDebug() << "Size:" <<
                    RawProcessor.imgdata.sizes.width << "x"
                 << RawProcessor.imgdata.sizes.height << ", Flip:" << RawProcessor.imgdata.sizes.flip;

        //cvImage = cv::Mat::zeros(RawProcessor.imgdata.sizes.height,RawProcessor.imgdata.sizes.width,CV_64F);
        rawParams.output_tiff = 1;
        rawParams.output_bps=16;
        rawParams.no_interpolation=1;
        rawParams.gamm[0] = rawParams.gamm[1] = 1;

        if( RawProcessor.unpack()  == LIBRAW_SUCCESS){
            rawParams.output_color = 0;
            if( RawProcessor.dcraw_process() == LIBRAW_SUCCESS){
                P1.colors = 1;
                S.width = S.iwidth;
                S.height = S.iheight;
                libraw_processed_image_t *image1, *image2, *image3, *image4;
                for (int layer=0;layer<4;layer++)
                {
                    if(layer>0)
                    {
                        for (int rc = 0; rc < S.iheight*S.iwidth; rc++)
                            RawProcessor.imgdata.image[rc][0] = RawProcessor.imgdata.image[rc][layer];
                    }

                    //create a Mat object by data obtained from LibRaw
                    if(layer == 0){
                        image1 = RawProcessor.dcraw_make_mem_image();
                        cvImageR = cv::Mat(cv::Size(image1->width, image1->height), CV_16UC1,image1->data, cv::Mat::AUTO_STEP);
                    }
                    if(layer == 1){
                        image2 = RawProcessor.dcraw_make_mem_image();
                        cvImageG1 = cv::Mat(cv::Size(image2->width, image2->height), CV_16UC1,image2->data, cv::Mat::AUTO_STEP);
                    }
                    if(layer == 2){
                        image3 = RawProcessor.dcraw_make_mem_image();
                        cvImageB = cv::Mat(cv::Size(image3->width, image3->height), CV_16UC1,image3->data, cv::Mat::AUTO_STEP);

                    }
                    if(layer == 3){
                        image4 = RawProcessor.dcraw_make_mem_image();
                        cvImageG2 = cv::Mat(cv::Size(image4->width, image4->height), CV_16UC1,image4->data, cv::Mat::AUTO_STEP);
                    }


                }

                cvImageR.convertTo(cvImageR,CV_64F);
                cvImageG1.convertTo(cvImageG1,CV_64F);
                cvImageB.convertTo(cvImageB,CV_64F);
                cvImageG2.convertTo(cvImageG2,CV_64F);


                cv::sepFilter2D(cvImageR,cvImageR,CV_64F,lanczosKernel,lanczosKernel.t(),cv::Point(-1,-1));
                cv::sepFilter2D(cvImageG1,cvImageG1,CV_64F,lanczosKernel,lanczosKernel.t(),cv::Point(-1,-1));
                cv::sepFilter2D(cvImageB,cvImageB,CV_64F,lanczosKernel,lanczosKernel.t(),cv::Point(-1,-1));
                cv::sepFilter2D(cvImageG2,cvImageG2,CV_64F,lanczosKernel,lanczosKernel.t(),cv::Point(-1,-1));
                cvImage = cvImageR + cvImageB + 0.5*( cvImageG1 + cvImageG2 );

                double minVal = 0., maxVal = 0.;
                cv::minMaxLoc( cvImage, &minVal, &maxVal);
                qDebug() << "Min Val: " << minVal << "Max Val: " << maxVal;
                cvImage.convertTo(cvImage,CV_16UC1,65535./(maxVal-minVal),-65535.*minVal/(maxVal-minVal));

                if(rotationIndex == 1){
                    cv::transpose(cvImage,cvImage);
                    cv::flip(cvImage,cvImage,1);
                } else if (rotationIndex == 2){
                    cv::flip(cvImage,cvImage,-1);
                } else if (rotationIndex == 3){
                    cv::transpose(cvImage,cvImage);
                    cv::flip(cvImage,cvImage,0);
                }

                qDebug() << "Raw image converted";

                // Correct distortions
                if (distortionCheck->isChecked()){
                    correctDistortion(cvImage);
                }

                cv::imwrite(savePath, cvImage);

                cvImageB.release(); cvImageR.release(); cvImageG1.release(); cvImageG2.release();
                cvImage.release();
                LibRaw::dcraw_clear_mem(image1);
                LibRaw::dcraw_clear_mem(image2);
                LibRaw::dcraw_clear_mem(image3);
                LibRaw::dcraw_clear_mem(image4);
                RawProcessor.recycle();
                emit finished();
                return;
            }
        }
    }
    cv::Mat processedImage = cv::imread(filePath.toLatin1().data(), cv::ImreadModes::IMREAD_ANYDEPTH | cv::ImreadModes::IMREAD_GRAYSCALE);
    if (processedImage.data){
        // Correct distortions
        if (distortionCheck->isChecked()){
            correctDistortion(processedImage);
        }
        cv::imwrite(savePath,processedImage);
        processedImage.release();
        emit finished();
        return;
    }


    cv::Mat NotRecognized = cv::Mat::zeros(200,280,CV_8UC3);
    cv::putText(NotRecognized, "Image file not recognized", cv::Point2i(30,100),
                cv::FONT_HERSHEY_PLAIN, 1., cv::Scalar(255,255,255), 1., cv::LINE_AA);
    RawProcessor.recycle();
    emit finished();
    return;


}

void rawConverter::correctDistortion(cv::Mat &image)
{
    cv::Point2i frameCenter(image.cols/2,image.rows/2);
    float normFactor;
    float a = aCal->text().toFloat();
    float b = bCal->text().toFloat();
    float c = cCal->text().toFloat();
    float cropFactorValue = cropFactorEdit->text().toFloat();
    float lensCalCropFactor = cam1Calibration->lensMakerList[cam1Calibration->getLensMakerIdx()].
            lensList[cam1Calibration->getLensIdx()].lensLab[cam1Calibration->getBestLensLab()].cropFactor;
    if (image.cols >= image.rows){
        normFactor = 2.*lensCalCropFactor/((float)image.rows*cropFactorValue);
    }
    else {
        normFactor = 2.*lensCalCropFactor/((float)image.cols*cropFactorValue);
    }
    if (remapX.size() != image.size()) {
        remapX = cv::Mat::zeros(image.size(),CV_32F);
        remapY = cv::Mat::zeros(image.size(),CV_32F);
        cv::Mat_<float>::iterator remapXIter = remapX.begin<float>();
        cv::Mat_<float>::iterator remapYIter = remapY.begin<float>();
        int iCol = 0;
        int iRow = 0;
        float rSrc, rDest;
        for(; remapXIter != remapX.end<float>(); ++remapXIter, ++remapYIter){
            float angle;
            rSrc = sqrt(pow((float)(iCol-frameCenter.x),2) + pow((float)(iRow-frameCenter.y),2));
            angle = atan2((float)(iRow-frameCenter.y),(float)(iCol-frameCenter.x));
            // Normalize rSrc:
            rSrc *= normFactor;

            // Compute normalied rDest
            rDest = (a*pow(rSrc,3)+b*pow(rSrc,2)+c*rSrc + 1.-a-b-c)*rSrc;
            // De-normalize rDest
            rDest /= normFactor;
            // Compute the remap matrices
            *remapXIter = cos(angle)*rDest + (float)frameCenter.x;
            *remapYIter = sin(angle)*rDest + (float)frameCenter.y;
            ++iCol;
            if(iCol == remapX.cols){
                iCol = 0;
                ++iRow;
            }
        }
        qDebug() << iCol << "," << iRow << "," << image.cols << ","<< image.rows;
    }

    cv::remap(image,image,remapX,remapY, cv::INTER_LANCZOS4);

}

cv::Mat rawConverter::convertRawFile()
{
    return cv::Mat::zeros(1,1,0);
}

cv::Mat rawConverter::getThumbnail(fileList *rawFiles)
{
    LibRaw RawProcessor;
    cv::Mat cvImage;

    if(!QFile(filePath).exists()){
        QMessageBox fileNotFound;
        fileNotFound.setText("Image file not found. Do you want to specify the new folder location?");
        fileNotFound.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        fileNotFound.setDefaultButton(QMessageBox::No);
        fileNotFound.setModal(true);
        if(fileNotFound.exec() == QMessageBox::Yes){
            QString folderPath = QFileDialog::getExistingDirectory(0, tr("Choose a directory"),
                                                                   QString(), QFileDialog::ShowDirsOnly);
            if (!folderPath.isEmpty())
                rawFiles->updateImageFolder(folderPath);
        }
    }
    if( (RawProcessor.open_file(filePath.toUtf8())) == LIBRAW_SUCCESS){
        qDebug() << "Opening thumbnail";
        qDebug() << "Size:" <<
                    RawProcessor.imgdata.sizes.width << "x"
                 << RawProcessor.imgdata.sizes.height;
        qDebug() << "User Orientation (libraw flip): " << RawProcessor.imgdata.sizes.flip;
        if (RawProcessor.unpack_thumb() == LIBRAW_SUCCESS){
            RawProcessor.dcraw_process();
            //libraw_processed_image_t *image = RawProcessor.dcraw_make_mem_thumb();
            QTemporaryFile thumbfile;
            if(!thumbfile.open()){
                cv::Mat NotRecognized = cv::Mat::zeros(200,280,CV_8UC3);
                cv::putText(NotRecognized, "Image file not recognized", cv::Point2i(30,100),
                            cv::FONT_HERSHEY_PLAIN, 1., cv::Scalar(255,255,255), 1., cv::LINE_AA);
                return NotRecognized;
            }
            qDebug() << thumbfile.fileName();
            if(RawProcessor.dcraw_thumb_writer(thumbfile.fileName().toUtf8()) == LIBRAW_SUCCESS){
                cvImage = cv::imread(thumbfile.fileName().toStdString(), cv::ImreadModes::IMREAD_COLOR);
            }

            qDebug() << "Thumbnail type:" << cvImage.type();
            cv::cvtColor(cvImage,cvImage, cv::COLOR_BGR2RGB);
            RawProcessor.recycle();
            if(rotationIndex == 1){
                cv::transpose(cvImage,cvImage);
                cv::flip(cvImage,cvImage,1);
            } else if (rotationIndex == 2){
                cv::flip(cvImage,cvImage,-1);
            } else if (rotationIndex == 3){
                cv::transpose(cvImage,cvImage);
                cv::flip(cvImage,cvImage,0);
            }
            if (distortionCorrection){

            }
            return cvImage;
        }
    } else {
        cv::Mat processedImage = cv::imread(filePath.toLatin1().data());
        if (processedImage.data){
            cv::cvtColor(processedImage,processedImage,cv::COLOR_BGR2RGB);
            return processedImage;
        } else {
            cv::Mat NotRecognized = cv::Mat::zeros(200,280, CV_8UC3);
            cv::putText(NotRecognized, "Image file not recognized", cv::Point2i(30,100),
                        cv::FONT_HERSHEY_PLAIN, 1., cv::Scalar(255,255,255), 1., cv::LINE_AA);
            RawProcessor.recycle();
            return NotRecognized;
        }
    }
    return cv::Mat::zeros(200,280, CV_8UC3);
}

void rawConverter::setSavePath(std::string savePath)
{
    this->savePath = savePath;
}


void rawConverter::tiff_set (ushort *ntag,
                             ushort tag, ushort type, int count, int val)
{
    struct libraw_tiff_tag *tt;
    int c;

    tt = (struct libraw_tiff_tag *)(ntag+1) + (*ntag)++;
    tt->tag = tag;
    tt->type = type;
    tt->count = count;
    if (type < 3 && count <= 4)
        for(c=0;c<4;c++) tt->val.c[c] = val >> (c << 3);
    else if (type == 3 && count <= 2)
        for(c=0;c<2;c++) tt->val.s[c] = val >> (c << 4);
    else tt->val.i = val;
}
#define TOFF(ptr) ((char *)(&(ptr)) - (char *)th)

void rawConverter::tiff_head (int width, int height, struct tiff_hdr *th)
{
    int c;

    memset (th, 0, sizeof *th);
    th->t_order = qToBigEndian(0x4d4d4949) >> 16;
    th->magic = 42;
    th->ifd = 10;
    tiff_set (&th->ntag, 254, 4, 1, 0);
    tiff_set (&th->ntag, 256, 4, 1, width);
    tiff_set (&th->ntag, 257, 4, 1, height);
    tiff_set (&th->ntag, 258, 3, 1, 16);
    for(c=0;c<4;c++) th->bps[c] = 16;
    tiff_set (&th->ntag, 259, 3, 1, 1);
    tiff_set (&th->ntag, 262, 3, 1, 1);
    tiff_set (&th->ntag, 273, 4, 1, sizeof *th);
    tiff_set (&th->ntag, 277, 3, 1, 1);
    tiff_set (&th->ntag, 278, 4, 1, height);
    tiff_set (&th->ntag, 279, 4, 1, height*width*2);
    tiff_set (&th->ntag, 282, 5, 1, TOFF(th->rat[0]));
    tiff_set (&th->ntag, 283, 5, 1, TOFF(th->rat[2]));
    tiff_set (&th->ntag, 284, 3, 1, 1);
    tiff_set (&th->ntag, 296, 3, 1, 2);
    tiff_set (&th->ntag, 306, 2, 20, TOFF(th->date));
    th->rat[0] = th->rat[2] = 300;
    th->rat[1] = th->rat[3] = 1;
}


void rawConverter::write_tiff(int width, int height, unsigned short *bitmap, const char *fn)
{
    struct tiff_hdr th;

    FILE *ofp;
    errno_t err = fopen_s(&ofp, fn, "wb");
    if(err) return;
    tiff_head (width,height,&th);
    fwrite (&th, sizeof th, 1, ofp);
    fwrite (bitmap, 2, width*height, ofp);
    fclose(ofp);
}
