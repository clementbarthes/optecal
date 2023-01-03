#include "qlabelwmouse.h"

QLabelWMouse::QLabelWMouse(QWidget *parent) :
    QLabel(parent)
{
    allowZoom = false;
    middleClickHeld = false;
    leftClickHeld = false;
}

void QLabelWMouse::mouseMoveEvent(QMouseEvent *ev){
    this->x = ev->position().x();
    this->y = ev->position().y();
    this->leftClickHeld = (ev->buttons() == Qt::LeftButton);
    this->middleClickHeld = (ev->buttons() == Qt::MiddleButton);
    emit Mouse_Pos();

}

void QLabelWMouse::wheelEvent(QWheelEvent *ev){
    if(!allowZoom) return;
    float zoomVal = 1. + (float)ev->angleDelta().y()/600.;
    zoomVal = zoomVal > 0. ? zoomVal : 0.5;
    if(!((this->width() > 2000 || this->height() > 2000) && zoomVal > 1.) && !(this->width() < 100 && zoomVal < 1.)){
        float xRatio = (float)ev->position().x()/(float)this->width();
        float yRatio = (float)ev->position().y()/(float)this->height();
        this->setFixedWidth((zoomVal*imgRatio)*this->height());
        this->setFixedHeight(zoomVal*this->height());
        emit updateSize(xRatio,yRatio);
    }
}

void QLabelWMouse::mousePressEvent(QMouseEvent *ev){
    //this->rightClick = (ev->button() == Qt::RightButton);
    if(ev->button() == Qt::LeftButton)
        emit Mouse_Pressed();

    if(ev->button() == Qt::MiddleButton){
        qDebug() << "Middle button pressed";
        xStatic = ev->position().x();
        yStatic = ev->position().y();
        emit Mouse_MiddlePressed();

    }
    if(ev->button() == Qt::RightButton){
        qDebug() << "Right button pressed";
        emit Mouse_RightPressed(ev->pos());
    }
}

//void QLabelWMouse::mouseReleaseEvent(QMouseEvent *ev){

//    if(ev->button() == Qt::MiddleButton){
//        qDebug() << "Middle button released";
//        emit Mouse_MiddleReleased();
//    }
//}

void QLabelWMouse::enterEvent(QEvent *){
    emit Mouse_Entered();
}

void QLabelWMouse::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}

void QLabelWMouse::mouseDoubleClickEvent(QMouseEvent *){
    emit Mouse_DoubleClick();
}

void QLabelWMouse::keyPressEvent(QKeyEvent *ev)
{
    this->key = ev->key();
    emit Key_Pressed();
}

