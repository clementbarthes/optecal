#ifndef FILELISTPAGE_H
#define FILELISTPAGE_H

#include <QObject>
#include <QFileDialog>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QDebug>

#include "rawconverter.h"
#include "filelist.h"
#include "autoresize.h"
#include "calibration.h"


class fileListPage : public QObject
{
    Q_OBJECT
protected:
    QListWidget* listFilesWidget;
    QFileDialog* loadImages;
    fileList* imageFiles;
    autoResize* cam1Display;
    std::vector<int> selectedFrames;



public:
    fileListPage(QFileDialog* loadImages, QListWidget* listFilesWidget,
                          autoResize* cam1Display, fileList* imageFiles);
    void updateListFiles();

signals:
    void correctThumbnailDistortion();
public slots:
    void on_loadImage_clicked();
    void on_sortFilesComboBox_currentIndexChanged(int index);
    void on_listFilesWidget_currentRowChanged(int currentRow);
    void on_listFilesWidget_customContextMenuRequested(const QPoint &pos);
    void multipleFrameSelection(QModelIndexList val);

};

#endif // FILELISTPAGE_H
