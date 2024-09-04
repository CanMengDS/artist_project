#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <startbutton.h>
#include <QTimer>
#include <QPropertyAnimation>
#include <mypushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(360,580);
    this->setWindowIcon(QIcon(":/MIcon/no_cow.png"));
    this->setWindowTitle("为什么不吃牛肉");
    // this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    // this->setStyleSheet("QMainWindow{border-radius: 10px;}");
    ui->main_label->setStyleSheet("QLabel{color :white;}");
    ui->action_close->setIcon(QIcon(":/MIcon/close.png"));
    connect(ui->action_close,&QAction::triggered,[=](){
        this->close();
    });

    StartButton* startButton = new StartButton(":/MIcon/cow_button_icon.png");
    startButton->setParent(this);
    startButton->move((this->width() *0.5 - startButton->width() * 0.5),450);


    choose = new ChooseSence;
    connect(choose,&ChooseSence::backMainWidget,[=](){
        choose->hide();
        this->show();
        opacityAnimation();
        QTimer::singleShot(1000,this,[=](){
            this->close();
        });
    });

    connect(startButton,&StartButton::clicked,[=](){

        QTimer::singleShot(200,this,[=](){
            this->hide();
            choose->show();
            emit choose->startAnimation();
        });
        qDebug()<< "用户点击了开始按钮";
    });

    // myPushButton* myp = new myPushButton(":/MIcon/money.png");
    // myp->setParent(this);
    // myp->move(50,50);
    // myp->resize(200,200);
    // myp->show();
}




void MainWindow::opacityAnimation(){
    QPropertyAnimation* opAnimation = new QPropertyAnimation(this,"windowOpacity");
    opAnimation->setDuration(1000);
    opAnimation->setStartValue(0);
    opAnimation->setEndValue(1);
    opAnimation->start();
}

void MainWindow::paintEvent(QPaintEvent *event){
    paintBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintBackground(){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/MIcon/background.png"));
}
