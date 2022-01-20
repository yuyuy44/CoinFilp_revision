#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

#include "mycoin.h"

class PlayScene : public QMainWindow {
    Q_OBJECT

  public:

    int levelIndex;
    bool isWin = true;
    bool isRandom = false;

    int gameArray[4][4];
    MyCoin *coinBtn[4][4];

    //    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelIndex);

    void load(PlayScene *playScene);
    void paintEvent(QPaintEvent *event);

  signals:

    void nextLevelScene();
    void chooseSceneBack();
    void homeSceneBack();
    void resetScene();
};

#endif // PLAYSCENE_H
