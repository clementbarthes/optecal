#include "drawroiwindow.h"
#include "ui_drawroiwindow.h"


drawROIWindow::drawROIWindow(QString roiImagePath, drawShape roiShapeCurrent, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawROIWindow)
{
    ui->setupUi(this);
    connect(ui->refImageLabel,SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(ui->refImageLabel,SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    connect(ui->refImageLabel,SIGNAL(Mouse_Entered()), this, SLOT(Mouse_Entered()));
    connect(ui->refImageLabel,SIGNAL(Mouse_DoubleClick()),this,SLOT(Mouse_DoubleClick()));
    connect(ui->refImageLabel,SIGNAL(Key_Pressed()),this,SLOT(Key_Pressed()));
    roiDisplay.setDisplayBox(ui->refImageLabel);
    roiDisplay.setCurrentImg(roiImagePath);
    imageResizeCoef = roiDisplay.getResizeCoef();
    roiShapes = roiShapeCurrent;
    roiShapes.setImage(roiDisplay.getCurrentImg());
}

void drawROIWindow::resizeEvent(QResizeEvent*){
    roiShapes.updateDrawing(roiDisplay.getResizeCoef());
    roiDisplay.update();
}



drawShape drawROIWindow::getRoi()
{
    return roiShapes;
}

void drawROIWindow::on_plusPolyButton_clicked()
{
    ui->plusPolyButton->setDown(true);
    ui->refImageLabel->grabKeyboard();
    ui->refImageLabel->setCursor(Qt::CrossCursor);
    roiShapes.initShape(drawShape::plusPoly);
    roiDisplay.update();
}

void drawROIWindow::Mouse_current_pos()
{
    cv::Point2i currentPoint((ui->refImageLabel->x)*imageResizeCoef,(ui->refImageLabel->y)*imageResizeCoef);
    if(roiShapes.drawingInProgress){
        roiShapes.updatePoint(&currentPoint);
        roiShapes.updateDrawing(roiDisplay.getResizeCoef());
        roiDisplay.update();
    } else if(roiShapes.updatePointInProgress){
        ui->refImageLabel->setCursor(Qt::SizeBDiagCursor);
        roiShapes.updatePoint(&currentPoint);
        roiShapes.updateDrawing(roiDisplay.getResizeCoef());
        roiDisplay.update();
    }
    else{
        ui->refImageLabel->setCursor(Qt::ArrowCursor);
        if(roiShapes.isMouseNearPoint(&currentPoint)){
            ui->refImageLabel->setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void drawROIWindow::Mouse_Pressed()
{
    cv::Point2i currentPoint((ui->refImageLabel->x)*imageResizeCoef,(ui->refImageLabel->y)*imageResizeCoef);
    if(roiShapes.drawingInProgress){
        roiShapes.setPoint(currentPoint);
    }else if ((!roiShapes.updatePointInProgress) & (roiShapes.isMouseNearPoint(&currentPoint))){
        roiShapes.updatePointInProgress = true;
    }else if (roiShapes.updatePointInProgress){
        roiShapes.updatePointInProgress = false;
    }
}

void drawROIWindow::Mouse_Entered()
{
    imageResizeCoef = roiDisplay.getResizeCoef();
}

void drawROIWindow::Mouse_DoubleClick()
{
    if(roiShapes.drawingInProgress){
        roiShapes.acceptShape();
        // Double-click creates 2 extra points, so reject them:
        roiShapes.rejectLastPoint();
        roiShapes.rejectLastPoint();
        releaseDrawingButtons();
    }
}

void drawROIWindow::Key_Pressed()
{
    if(roiShapes.drawingInProgress==true)
    {
        if((ui->refImageLabel->key == Qt::Key_Return)
                |(ui->refImageLabel->key == Qt::Key_Space)){
            ui->refImageLabel->releaseKeyboard();
            roiShapes.acceptShape();
        } else if(ui->refImageLabel->key == Qt::Key_Escape){
            ui->refImageLabel->releaseKeyboard();
            roiShapes.rejectLastPoint();
            releaseDrawingButtons();
        }
    }
    roiDisplay.update();
}

void drawROIWindow::releaseDrawingButtons(){
    ui->plusPolyButton->setDown(false);
    ui->minusPolyButton->setDown(false);
    ui->plusCircleButton->setDown(false);
    ui->minusCircleButton->setDown(false);
    ui->refImageLabel->releaseKeyboard();
}

drawROIWindow::~drawROIWindow()
{
    delete ui;
}
