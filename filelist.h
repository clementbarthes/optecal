#ifndef FILELIST_H
#define FILELIST_H
#include <QList>
#include <QDir>
#include<QListWidget>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QtAlgorithms>
#include <QDebug>

#include <stdlib.h>
#include "opencv2/opencv.hpp"
class fileList
{

    struct fileAttributes {
        QString filePath;
        QString fileNames;
        QDateTime fileDates;
        QDateTime fileDatesModified;
        bool refImage;
        bool isSolved;

        std::vector<cv::Point2f> imageCorners;

        bool operator==(const fileAttributes& rhs) const
        {
            return fileNames == rhs.fileNames;
        }

    };



    QDir rootFolder;
    QListWidget* listWidget;
    int currentImg;
    QList<fileAttributes> fileDef;
    int fileType; //0: correlation files, 1: calibration files, 2: RAW files

public:
    int sortFlag;

    static const int correlationFiles = 0;
    static const int calibrationFiles = 1;
    static const int rawFiles = 2;

    static const int sortByNames = 0;
    static const int sortByDateCreated = 1;
    static const int sortByDateModified = 2;

    fileList(int fileType, QDir rootFolder);
    fileList();
    ~fileList();
    void setListDisplay(QListWidget *listWidget);
    void appendList(QStringList newFilePath);
    QStringList getFilePath();
    QString getFilePath(int idx);

    QStringList getFileNames();
    QString getFileNames(int idx);

    QList<QDateTime> getFileDates();
    QDateTime getFileDates(int idx);

    void setRefImage(int idx);
    int getRefImageIdx() const;

    bool isRefImage(int idx);
    QString getRefImagePath();

    int getNoFiles();

    void sortFiles(int sortIndex);

    cv::Mat getRefImage();
    cv::Mat getImage(int idx);
    cv::Mat getImage8bits(int idx);
    cv::Mat getImageColor8bits(int idx);

    bool getIsSolved(int index);
    void setIsSolved(int index, bool solved);

    void setCurrentImgIdx(int currentImg);
    int getCurrentImgIdx();
    int getImageType();

    void deleteImage(int imgIdx);

    QString getCurrentImgPath();

    void updateRootFolder(QDir newRootFolder);

    void updateImageFolder(QString newFolder);

    void setImageCorners(std::vector<cv::Point2f> imageCorners, int imgIdx);
    std::vector<cv::Point2f> getImageCorners(int imgIdx);

    void clear();
    void write(cv::FileStorage &fs) const;
    void read(const cv::FileNode &node);


private:
    struct {
        bool operator()(fileAttributes a, fileAttributes b)
        {
            return a.fileNames <= b.fileNames;
        }
    } compareNames;

    struct {
        bool operator()(fileAttributes a, fileAttributes b)
        {
            return a.fileDates <= b.fileDates;
        }
    } compareDates;

    struct {
        bool operator()(fileAttributes a, fileAttributes b)
        {
            return a.fileDatesModified <= b.fileDatesModified;
        }
    } compareDatesModified;

    struct {
        /// Thanks to github.com/laurent22 for this natural sort code
        bool operator() (fileAttributes a, fileAttributes b) {
            QString s1 = a.fileNames;
            QString s2 = b.fileNames;
            if (s1 == "" || s2 == "") return s1 < s2;

            // Move to the first difference between the strings
            int startIndex = -1;
            int length = s1.length() > s2.length() ? s2.length() : s1.length();
            for (int i = 0; i < length; i++) {
                QChar c1 = s1[i];
                QChar c2 = s2[i];
                if (c1 != c2) {
                    startIndex = i;
                    break;
                }
            }

            // If the strings are the same, exit now.
            if (startIndex < 0) return s1 < s2;

            // Now extract the numbers, if any, from the two strings.
            QString sn1;
            QString sn2;
            bool done1 = false;
            bool done2 = false;
            length = s1.length() < s2.length() ? s2.length() : s1.length();

            for (int i = startIndex; i < length; i++) {
                if (!done1 && i < s1.length()) {
                    if (s1[i] >= '0' && s1[i] <= '9') {
                        sn1 += QString(s1[i]);
                    } else {
                        done1 = true;
                    }
                }

                if (!done2 && i < s2.length()) {
                    if (s2[i] >= '0' && s2[i] <= '9') {
                        sn2 += QString(s2[i]);
                    } else {
                        done2 = true;
                    }
                }

                if (done1 && done2) break;
            }

            // If none of the strings contain a number, use a regular comparison.
            if (sn1 == "" && sn2 == "") return s1 < s2;

            // If one of the strings doesn't contain a number at that position,
            // we put the string without number first so that, for example,
            // "example.bin" is before "example1.bin"
            if (sn1 == "" && sn2 != "") return true;
            if (sn1 != "" && sn2 == "") return false;

            return sn1.toInt() < sn2.toInt();
        }
    }naturalSortCompare;


    friend class displacements;
};



#endif // FILELIST_H
