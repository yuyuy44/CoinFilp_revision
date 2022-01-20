#include "mycoin.h"

// MyCoin::MyCoin(QWidget *parent)
//    : QWidget{parent}
// {

// }

MyCoin::MyCoin(QString butImg) {
    QPixmap pix;
    bool ret = pix.load(butImg);
    if (!ret) {
        return;
    }
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("border{0px;}");
    this->setIcon(pix);
    this->setIconSize(pix.size());

    timer1 = new QTimer;
    timer2 = new QTimer;
    connect(timer1, &QTimer::timeout, [ = ]() {

        QString coins = QString(":/res/Coin000%1.png").arg(min++);
        QPixmap pix;
        bool ret = pix.load(coins);
        if (!ret) {
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
        if (min > max) {
            min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });
    connect(timer2, &QTimer::timeout, [ = ]() {
        QString coins = QString(":/res/Coin000%1.png").arg(max--);
        QPixmap pix;
        bool ret = pix.load(coins);
        if (!ret) {
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
        if (max < min) {
            max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void MyCoin::changeFlag() {
    if (flag) {
        timer1->start(30);
    } else {
        timer2->start(30);
    }
    isAnimation = true;
    flag = !flag;
}

void MyCoin::mousePressEvent(QMouseEvent *e) {
    if (isAnimation || isWin) {
        return;
    }
    QPushButton::mousePressEvent(e);
}

void MyCoin::reverse() {
    QPixmap pix0;
    QPixmap pix1;
    pix0.load(":/res/Coin0008.png");
    pix1.load(":/res/Coin0001.png");

    setIcon(flag  ? pix0 : pix1);
    flag = flag == 0 ? 1 : 0;
}
