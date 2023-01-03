#ifndef FILELISTCALIBRATIONPAGE_H
#define FILELISTCALIBRATIONPAGE_H

#include "filelistpage.h"
#include "calibration.h"

class fileListCalibrationPage : public fileListPage
{
    Q_OBJECT

    calibration* calibrationInstance;


public:
    fileListCalibrationPage(QFileDialog* loadImages, QListWidget* listFilesWidget,
                            autoResize* cam1Display, fileList* imageFiles,
                            calibration* calibrationInstance);
public slots:
  //  void on_listFilesWidget_currentRowChanged(int currentRow);
};

#endif // FILELISTCALIBRATIONPAGE_H
