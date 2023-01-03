#ifndef QLABELWMOUSE_H
#define QLABELWMOUSE_H

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>


class QLabelWMouse : public QLabel
{
    Q_OBJECT
public:
    int x, y;
    int xStatic, yStatic;
    int key;
    bool rightClick;
    bool leftClickHeld;
    bool middleClickHeld;
    float imgRatio;

    bool allowZoom;

    explicit QLabelWMouse(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
//    void mouseReleaseEvent(QMouseEvent *ev);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *ev);
    void wheelEvent(QWheelEvent *ev);
signals:
    void Mouse_Pressed();
    void Mouse_MiddlePressed();
//    void Mouse_MiddleReleased();
    void Mouse_RightPressed(QPoint);
    void Mouse_Pos();
    void Mouse_Entered();
    void Mouse_Left();
    void Mouse_DoubleClick();
    void Key_Pressed();
    void updateSize(float, float);

public slots:

};

#endif // QLABELWMOUSE_H
