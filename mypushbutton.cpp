#include "mypushbutton.h"

#include <QPropertyAnimation>

// MyPushButton::MyPushButton(QWidget *parent)
//    : QWidget{parent}
// {

// }

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    normalImgPath = normalImg;
    pressImgPath = pressImg;

    QPixmap pix;
    bool    ret = pix.load(normalImgPath);

    if (!ret)
    {
        return;
    }

    this->setFixedSize(pix.width(), pix.height());

    this->setStyleSheet("QPushButton{border:0px}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    // 动画间隔
    animation->setDuration(200);

    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(),
                                   this->height()));

    // 结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(),
                                 this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");


    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(),
                                   this->height()));

    animation->setEndValue(QRect(this->x(), this->y(), this->width(),
                                 this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::enterEvent(QEnterEvent *event)
{
    QPixmap pix;
    bool    ret = pix.load(normalImgPath);

    if (!ret)
    {
        return;
    }

    pix = pix.scaled(QSize(pix.width() * 1.02, pix.height() * 1.02),
                     Qt::KeepAspectRatio);
    this->setFixedSize(pix.width(), pix.height());

    this->setStyleSheet("QPushButton{border:0px}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(), pix.height()));

    QPushButton::enterEvent(event);
}

void MyPushButton::leaveEvent(QEvent *event)
{
    QPixmap pix;
    bool    ret = pix.load(normalImgPath);

    if (!ret)
    {
        return;
    }

    this->setFixedSize(pix.width(), pix.height());

    this->setStyleSheet("QPushButton{border:0px}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(), pix.height()));

    QPushButton::leaveEvent(event);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if (pressImgPath != "") {
        QPixmap pix;
        bool    ret = pix.load(pressImgPath);

        if (!ret)
        {
            return;
        }

        this->setFixedSize(pix.width(), pix.height());

        this->setStyleSheet("QPushButton{border:0px}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (pressImgPath != "") {
        QPixmap pix;
        bool    ret = pix.load(normalImgPath);

        if (!ret)
        {
            return;
        }

        this->setFixedSize(pix.width(), pix.height());

        this->setStyleSheet("QPushButton{border:0px}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    QPushButton::mouseReleaseEvent(e);
}
