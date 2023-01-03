#ifndef RAWMODULE_H
#define RAWMODULE_H

#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QListWidget>
#include <QProgressDialog>
#include <QFileDialog>
#include <QtTest/QtTest>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QDebug>
#include <QThread>


#include "rawconverter.h"
#include "filelist.h"
#include "filelistpage.h"
#include "qlabelwmouse.h"

class rawModule : public QObject
{
    Q_OBJECT

    fileListPage* rawFilePage;
    fileList* rawFiles;
    QProgressDialog* pd;
    std::vector<int> selectedFrames;
    std::vector<int> processedFrames;
    QDir* rootFolder;
    QLabelWMouse *displayBox;
    QListWidget *listWidget;
    bool analysisCanceled;
    QString folderPath;
    int processedCounter;


public:
    explicit rawModule(fileList* rawFiles, fileListPage* rawFilePage,
                       QDir* rootFolder, QLabelWMouse *displayBox,
                       QListWidget *listWidget);



signals:

public slots:
    void multipleFrameSelection(QModelIndexList val);
    void multipleFrame();
    void allFrames();

    void clockwiseButton();
    void counterClockwiseButton();

private slots:
    void cancel();
    void threadFinished();

private:
        void loadNextThread();
};

#endif // RAWMODULE_H
