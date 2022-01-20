#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include "playscene.h"

#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene) {
    ui->setupUi(this);

    this->setWindowTitle("翻金币");
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    connect(ui->actionquit, &QAction::triggered, [ = ]() {
        this->close();
    });
    connect(ui->actionstart, &QAction::triggered, [ = ]() {
        this->hide();
        levelScene->setGeometry(this->geometry());
        levelScene->show();
    });

    QSoundEffect *sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    levelScene = new ChooseLevelScene;

    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");

    startBtn->move((this->width() - startBtn->width()) * 0.5,
                   (this->height() * 0.7));
    startBtn->setParent(this);

    connect(startBtn, &QPushButton::clicked, [ = ]() {
        sound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500, this, [ = ]() {
            this->hide();
            levelScene->setGeometry(this->geometry());
            levelScene->show();
        });
    });

    connect(levelScene, &ChooseLevelScene::chooseSceneBack, [ = ]() {
        this->setGeometry(levelScene->geometry());
        show();
    });
}

void MainScene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap  pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}

MainScene::~MainScene() {
    delete ui;
}
