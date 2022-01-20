#include "mypushbutton.h"
#include "playscene.h"
#include "mycoin.h"
#include "dataconfig.h"

#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSoundEffect>
#include <QRandomGenerator>

// PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
// {

// }

void setCoinNotDo(MyCoin *coinBtn[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            coinBtn[i][j]->isWin = true;
        }
    }
}
void setCoinDo(MyCoin *coinBtn[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            coinBtn[i][j]->isWin = false;
        }
    }
}

void filp(int gameArray[4][4], int i, int j) {
    gameArray[i][j] = gameArray[i][j] == 1 ? 0 : 1;
    if (i + 1 <= 3) {
        gameArray[i + 1][j] = gameArray[i + 1][j] == 1 ? 0 : 1;
    }
    if (i - 1 >= 0) {
        gameArray[i - 1][j] = gameArray[i - 1][j] == 1 ? 0 : 1;
    }
    if (j + 1 <= 3) {
        gameArray[i ][j + 1] = gameArray[i ][j + 1] == 1 ? 0 : 1;
    }
    if (j - 1 >= 0) {
        gameArray[i ][j - 1] = gameArray[i][j - 1] == 1 ? 0 : 1;
    }
}

PlayScene::PlayScene(int levelIndex) {
    this->levelIndex = levelIndex;
    if (levelIndex < 0) {
        isRandom = true;
    }

    QMenuBar *bar = menuBar();
    QMenu    *startMenu = bar->addMenu("开始");

    if (isRandom) {
        QAction *resetAction = startMenu->addAction("重新刷新");
        connect(resetAction, &QAction::triggered, [ = ]() {
            emit resetScene();
        });
    } else if (levelIndex < 20) {
        QAction *nextAction = startMenu->addAction("下一关");
        connect(nextAction, &QAction::triggered, [ = ]() {
            hide();
            emit nextLevelScene();
        });
    }

    QAction *homeAction = startMenu->addAction("返回主界面");
    connect(homeAction, &QAction::triggered, [ = ]() {
        hide();
        emit homeSceneBack();
    });

    QAction *backAction = startMenu->addAction("返回选择关卡");
    connect(backAction, &QAction::triggered, [ = ]() {
        hide();
        emit chooseSceneBack();
    });

    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [ = ]() {
        this->close();
    });


    QLabel *label = new QLabel;
    label->setParent(this);

    if (isRandom) {
        QString level = QString("随机模式");
        label->setText(level);
        QString str = QString("翻金币 随机模式");
        this->setWindowTitle(str);
    } else {
        QString level = QString("level:%1").arg(levelIndex);
        label->setText(level);
        QString str = QString("翻金币 第%1关").arg(levelIndex);
        this->setWindowTitle(str);
    }

    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    QSoundEffect *winSound = new QSoundEffect;
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    QSoundEffect *backBtnSound = new QSoundEffect;
    backBtnSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    QSoundEffect *flipSound = new QSoundEffect;
    flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));

    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",
            ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(width() - backBtn->width() - 10,
                  height() - backBtn->height() - 10);

    connect(backBtn, &QPushButton::clicked, [ = ]() {
        backBtnSound->play();
        QTimer::singleShot(500, this, [ = ]() {
            emit chooseSceneBack();
        });
    });

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setGeometry(QRect(30, this->height() - 50, 120, 50));

    QLabel *winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->setParent(this);
    winLabel->move((this->width() - pix.width()) * 0.5, -pix.height());

    if (isRandom) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                gameArray[i][j] = 1;
            }
        }
        int count = QRandomGenerator::global()->bounded(1, 10);
        for (int i = 0; i < count; ++i) {
            filp(gameArray, QRandomGenerator::global()->bounded(0, 4), QRandomGenerator::global()->bounded(0, 4));
        }
    } else {
        dataConfig data;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                gameArray[i][j] = data.mData[levelIndex][i][j];
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QLabel *lbbg = new QLabel;
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            lbbg->setGeometry(0, 0, pix.width(), pix.height());
            lbbg->setPixmap(pix);
            lbbg->setParent(this);
            lbbg->move(57 + i * pix.width(), 200 + j * pix.height());

            QString coinStr;
            if (gameArray[i][j] == 1) {
                coinStr = ":/res/Coin0001.png";
            } else {
                coinStr = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(coinStr);
            coin->setParent(this);
            coin->move(57 + i * pix.width(), 200 + j * pix.height());

            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];

            coinBtn[i][j] = coin;

            connect(coin, &MyCoin::clicked, [ = ]() {
                flipSound->play();

                setCoinNotDo(coinBtn);

                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 1 ? 0 : 1;

                QTimer::singleShot(200, this, [ = ]() {
                    if (coin->posX + 1 <= 3) {
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        gameArray[coin->posX + 1][coin->posY] = gameArray[coin->posX + 1][coin->posY] == 1 ? 0 : 1;
                    }
                    if (coin->posX - 1 >= 0) {
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        gameArray[coin->posX - 1][coin->posY] = gameArray[coin->posX - 1][coin->posY] == 1 ? 0 : 1;
                    }
                    if (coin->posY + 1 <= 3) {
                        coinBtn[coin->posX ][coin->posY + 1]->changeFlag();
                        gameArray[coin->posX ][coin->posY + 1] = gameArray[coin->posX ][coin->posY + 1] == 1 ? 0 : 1;
                    }
                    if (coin->posY - 1 >= 0) {
                        coinBtn[coin->posX ][coin->posY - 1]->changeFlag();
                        gameArray[coin->posX ][coin->posY - 1] = gameArray[coin->posX][coin->posY - 1] == 1 ? 0 : 1;
                    }

                    isWin = true;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if (!coinBtn[i][j]->flag) {
                                isWin = false;
                                break;
                            }
                        }
                    }
                    if (isWin) {
                        QPropertyAnimation *winAnimation = new QPropertyAnimation(winLabel, "geometry");
                        winAnimation->setDuration(1000);
                        winAnimation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        winAnimation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
                        winAnimation->setEasingCurve(QEasingCurve::OutBounce);
                        winAnimation->start(QAbstractAnimation::DeleteWhenStopped);
                        winSound->play();
                    } else {
                        setCoinDo(coinBtn);
                    }
                });
            });
        }
    }

    connect(this, &PlayScene::resetScene, [ = ]() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                gameArray[i][j] = 1;
            }
        }
        int count = QRandomGenerator::global()->bounded(1, 10);
        for (int i = 0; i < count; ++i) {
            filp(gameArray, QRandomGenerator::global()->bounded(0, 4), QRandomGenerator::global()->bounded(0, 4));
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (coinBtn[i][j]->flag != gameArray[i][j]) {
                    coinBtn[i][j]->reverse();
                    coinBtn[i][j]->isWin = false;
                    winLabel->move((this->width() - pix.width()) * 0.5, -pix.height());
                }
            }
        }
    });
}

void PlayScene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap  pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5,
                       30,
                       pix.width(),
                       pix.height(),
                       pix);
}
