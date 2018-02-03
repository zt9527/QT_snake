#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QMouseEvent>
#include <QRectF>
#include <QColorDialog>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QProcess>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *event);

    void timerEvent(QTimerEvent *event);

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QPoint buf;
    QPoint point;
    QRectF rectangle;

    QPoint body[1024];
    QPoint head_point;
    QPoint food_point;
    int timeid;
    int len;
    int eatflag;
    int direction;//0 w,1 s,2 a,3 d
    int randx,randy;
    int score;
};


#endif // WIDGET_H
