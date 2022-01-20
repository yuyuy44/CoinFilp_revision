#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton {
    Q_OBJECT

  public:

    int posX;
    int posY;
    int flag;

    //    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);

    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    bool isAnimation = false;
    void mousePressEvent(QMouseEvent *e);

    bool isWin = false;

    void reverse();

  signals:
};

#endif // MYCOIN_H
