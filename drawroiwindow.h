#ifndef DRAWROIWINDOW_H
#define DRAWROIWINDOW_H
#include <Qt>
#include <QCursor>
#include <QDebug>
#include <QDialog>
#include <QString>
#include <Qlist>
#include <QMouseEvent>

#include "opencv2/opencv.hpp"

#include "qlabelwmouse.h"
#include "autoresize.h"
#include "drawshape.h"

namespace Ui {
class drawROIWindow;
}

class drawROIWindow : public QDialog
{
    Q_OBJECT
    drawShape roiShapes;
    autoResize roiDisplay;
    float imageResizeCoef;

public:
    explicit drawROIWindow(QString roiImagePath, drawShape roiShapeCurrent, QWidget *parent = 0);
    drawShape getRoi();
    ~drawROIWindow();



private:
    Ui::drawROIWindow *ui;

private slots:
    void resizeEvent(QResizeEvent*);

    void on_plusPolyButton_clicked();

    void Mouse_current_pos();
    void Mouse_Pressed();
    void Mouse_Entered();
    void Mouse_DoubleClick();
    void Key_Pressed();
    void releaseDrawingButtons();

};

#endif // DRAWROIWINDOW_H
