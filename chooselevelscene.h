#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include "playscene.h"

class ChooseLevelScene : public QMainWindow {
    Q_OBJECT

  public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    PlayScene *playScene;
    PlayScene *randomScene;

    QPushButton *btns[20];

  signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
