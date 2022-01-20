#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton {
    Q_OBJECT

public:

    //    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,
                 QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();

    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYPUSHBUTTON_H
