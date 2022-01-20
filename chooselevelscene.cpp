#include "chooselevelscene.h"
#include "mypushbutton.h"
#include "playscene.h"

#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QPushButton>
#include <QSoundEffect>
#include <QTimer>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent} {
    QMenuBar *bar = menuBar();
    QMenu    *startMenu = bar->addMenu("开始");

    QAction *homeAction = startMenu->addAction("返回主界面");

    connect(homeAction, &QAction::triggered, [ = ]() {
        hide();
        emit chooseSceneBack();
    });

    QAction *enterRadomAction = startMenu->addAction("进入随机模式");

    connect(enterRadomAction, &QAction::triggered, [ = ]() {
        hide();
        randomScene = new PlayScene(-1);
        randomScene->setGeometry(this->geometry());
        randomScene->show();

        connect(randomScene, &PlayScene::chooseSceneBack, [ = ]() {
            delete randomScene;
            randomScene = NULL;
            show();
        });
        connect(randomScene, &PlayScene::homeSceneBack, [ = ]() {
            delete randomScene;
            randomScene = NULL;
            emit chooseSceneBack();
        });
    });

    QAction *quitAction = startMenu->addAction("退出");

    connect(quitAction, &QAction::triggered, [ = ]() {
        this->close();
    });

    this->setWindowTitle("选择关卡");
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    QSoundEffect *tapBtnSound = new QSoundEffect;
    tapBtnSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    QSoundEffect *backBtnSound = new QSoundEffect;
    backBtnSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",
            ":/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(width() - backBtn->width() - 10,
                  height() - backBtn->height() - 10);
    connect(backBtn, &QPushButton::clicked, [ = ]() {
        backBtnSound->play();
        QTimer::singleShot(500, this, [ = ]() {
            hide();
            emit chooseSceneBack();
        });
    });

    playScene = NULL;

    for (int i = 0; i < 20; ++i) {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);

        btns[i] = menuBtn;

        connect(menuBtn, &QPushButton::clicked, [ = ]() {
            tapBtnSound->play();
            playScene = new PlayScene(i + 1);
            this->hide();
            playScene->setGeometry(this->geometry());
            playScene->show();

            connect(playScene, &PlayScene::chooseSceneBack, [ = ]() {
                delete this->playScene;
                this->playScene = NULL;
                show();
            });
            connect(playScene, &PlayScene::homeSceneBack, [ = ]() {
                delete this->playScene;
                this->playScene = NULL;
                emit chooseSceneBack();
            });

            connect(playScene, &PlayScene::nextLevelScene, [ = ]() {
                int index = playScene->levelIndex;
                delete this->playScene;
                this->playScene = NULL;
                this->btns[index]->click();
            });
        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignCenter);
        label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);

        // 设置鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap  pix;

    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5,
                       30,
                       pix.width(),
                       pix.height(),
                       pix);
}
