#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    rectangle = QRectF(10,40,this->width()-10-10,this->height()-40-10);
    timeid = startTimer(20);
    len = 1;
    eatflag = 0;
    head_point.setX(250);
    head_point.setY(250);
    direction = 0;
    score = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::black)));
    painter.setBrush(QBrush(QColor(Qt::white)));
    painter.drawRect(rectangle);

    QPen pen;
    pen.setWidth(10);
    painter.setPen(pen);

    //food_init
    if(!eatflag)
    {
        eatflag = 1;
        QTime time = QTime::currentTime();
        qsrand(time.msec()*qrand()*qrand()*qrand());
        while(1)
        {
            randx = qrand() % (this->width());
            randy = qrand() % (this->height());
            if(randx >= 15 && randy >= 45)
            {
                if(randx <= (this->width()-15) && randy <= (this->height()-15))
                {
                    food_point.setX(randx);
                    food_point.setY(randy);
                    break;
                }
            }
        }

    }

    painter.drawPoint(food_point);

    for(int j= 0;j < len;j++)
    {
        painter.drawPoint(body[j]);
    }
    //eat_food
    if((head_point.y() < (food_point.y()+5))&&(head_point.y() > (food_point.y()-5)))
    {
        if((head_point.x()<(food_point.x()+5))&&(head_point.x()>(food_point.x()-5)))
        {
            len += 5;
            score += 1;
            eatflag = 0;
//            qDebug() << "eat!!";
        }
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    static int i = 0;
    //update score
    QString text = QString("your score:%1").arg(score);
    ui->label_2->setText(text);
    //eat body
    for(i = 1;i<len;i++)
    {
        if(head_point == body[i])
        {
            killTimer(timeid);
            QMessageBox::about(this,"game over",text);
        }
    }

    //gameover
    if(head_point.x() <= 15 || head_point.y() <= 45)
    {
        killTimer(timeid);
        QMessageBox::about(this,"game over",text);
    }
    else if(head_point.x() >= (this->width()-15) || head_point.y() >= (this->height()-15))
    {
        killTimer(timeid);
        QMessageBox::about(this,"game over",text);
    }
    //
    switch (direction)
    {
    case 0:

        point = body[0];
        head_point.setY(head_point.y()-1);
        body[0] = head_point;
        for(i = 1; i < len; i++)
        {
            buf = body[i];
            body[i] = point;
            point = buf;
        }

        break;
    case 1:

        point = body[0];
        head_point.setY(head_point.y()+1);
        body[0] = head_point;
        for(i = 1; i < len; i++)
        {
            buf = body[i];
            body[i] = point;
            point = buf;
        }
        break;
    case 2:

        point = body[0];
        head_point.setX(head_point.x()-1);
        body[0] = head_point;
        for(i = 1; i < len; i++)
        {
            buf = body[i];
            body[i] = point;
            point = buf;
        }
        break;
    case 3:

        point = body[0];
        head_point.setX(head_point.x()+1);
        body[0] = head_point;
        for(i = 1; i < len; i++)
        {
            buf = body[i];
            body[i] = point;
            point = buf;
        }
        break;
    default:
        break;
    }
    update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        if(direction == 1)
            break;
        direction = 0;
        break;
    case Qt::Key_S:
        if(direction == 0)
           break;
        direction = 1;
        break;
    case Qt::Key_A:
        if(direction == 3)
            break;
        direction = 2;
        break;
    case Qt::Key_D:
        if(direction == 2)
            break;
        direction = 3;
        break;
    default:
        break;
    }
}

void Widget::on_pushButton_clicked()
{
    qApp->exit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}
