#include "choosesence.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QEvent>
#include <QTransform>
#include "animationsence.h"
#include <mediaplayersence.h>

ChooseSence::ChooseSence(QWidget *parent)
    : QMainWindow{parent}{
    this->move(0,0);
    this->resize(360,580);
    this->setWindowTitle("■■■Error■■■");
    this->setWindowIcon(QIcon(":/MIcon/error_icon.png"));

    connect(this,&ChooseSence::startAnimation,this,mainSm);
}

void ChooseSence::mainSm(){
    start_gapWidgetEffect();
    QTimer::singleShot(4000,this,[=](){
        start_moveAnimationEffect();
        QTimer::singleShot(3500,this,[=](){
            this->move(780,200);
            this->ended = true;
            this->setWindowTitle("请选择你的艺术家");
            this->setWindowIcon(QIcon(":/MIcon/seaSky.png"));
            update();
            QTimer::singleShot(500,this,[=](){
                widthChangeAnimation();
                QTimer::singleShot(1600,this,[=](){
                    end_AnimationiInitialiWidget();
                });
            });
        });
    });

    initiali_Setting_WidgetControl();
}



void ChooseSence::levelControlInitiali(){
    int mapIndex = 0;
    int controlWidth = 50;
    int gapWidth = 32;
    for(int x =0;x<=3;x++){
        for(int y =0; y<= 4;y++){
            myPushButton* myp = new myPushButton(":/MIcon/normal_undeveloped_icon.png");
            myp->setParent(this);
            myp->move(32 + x *(controlWidth + gapWidth),32 + y *(controlWidth + gapWidth));
            myp->resize(50,50);
            myp->show();
            levelControlMap.insert(mapIndex,myp);
            mapIndex++;
        }
    }
}


void ChooseSence::end_AnimationiInitialiWidget(){
    this->setFixedSize(360,580);
    // this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    levelControlInitiali();
    levelControlAddPixmap();
    // this->show();
    back->show();
}


void ChooseSence::levelControlAddPixmap(){
    QMap<int,myPushButton*>::iterator control_one =  levelControlMap.find(0);
    control_one.value()->setNormalName(":/MIcon/seaSky.png");
    // AnimationSence* animationSence_one = new AnimationSence(":/mSource/MSource/over.mp4");
    connect(control_one.value(),&myPushButton::clicked,[=](){
        qDebug()<<"已触发control_one";
        // animationSence_one->show();
    });
}


bool ChooseSence::event(QEvent *event){
    if(event->type() == Qt::WindowMaximized){
        return true;
    }
    return QWidget::event(event);
}

void ChooseSence::initiali_Setting_WidgetControl(){
    QMenuBar* men = new QMenuBar();
    setMenuBar(men);
    QMenu* choose_startMenu = men->addMenu("选项");
    QAction* choose_closeAction = choose_startMenu->addAction("退出程序");
    connect(choose_closeAction,&QAction::triggered,[=](){ this->close();});

    back = new QPushButton(this);
    back->resize(100,40);
    back ->setFont(QFont("微软雅黑",10));
    back->move(this->width() - back->width(),this->height() - back->height());
    back->setText("Back");
    back->setStyleSheet("QPushButton{background-color: rgb(190,190,190);border-radius: 10px;}QPushButton:pressed{background-color: rgb(211,211,211 );color: rgb(105,105,105)};");
    back->hide();
    connect(back,&QPushButton::clicked,[=](){
        this->hide();
        emit backMainWidget();
    });
}

void ChooseSence::start_moveAnimationEffect(){
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup(this);

    QPropertyAnimation* animation_one = new QPropertyAnimation(this,"pos");
    animation_one->setStartValue(QVariant(QPoint(0,0)));
    animation_one->setEndValue(QVariant(QPoint(1580,0)));
    animation_one->setDuration(1000);
    // animation_one->setEasingCurve(QEasingCurve::OutQuart);

    QPropertyAnimation* animation_two = new QPropertyAnimation(this,"pos");
    animation_two->setStartValue(QVariant(QPoint(1580,0)));
    animation_two->setEndValue(QVariant(QPoint(1580,492)));
    animation_two->setDuration(500);
    // animation_two->setEasingCurve(QEasingCurve::OutQuart);

    QPropertyAnimation* animation_three = new QPropertyAnimation(this,"pos");
    animation_three->setStartValue(QVariant(QPoint(1580,492)));
    animation_three->setEndValue(QVariant(QPoint(0,492)));
    animation_three->setDuration(1000);
    // animation_three->setEasingCurve(QEasingCurve::OutQuart);

    QPropertyAnimation* animation_four = new QPropertyAnimation(this,"pos");
    animation_four->setStartValue(QVariant(QPoint(0,492)));
    animation_four->setEndValue(QVariant(QPoint(0,0)));
    animation_four->setDuration(500);
    // animation_four->setEasingCurve(QEasingCurve::OutQuart);

    group->addAnimation(animation_one);
    group->addAnimation(animation_two);
    group->addAnimation(animation_three);
    group->addAnimation(animation_four);

    group->start(QSequentialAnimationGroup::DeleteWhenStopped);
}

void ChooseSence::noSeeAnimation(){
    // QGraphicsColorizeEffect* gce = new QGraphicsColorizeEffect(this);
    // setGraphicsEffect(gce);
    QPropertyAnimation* noSee = new QPropertyAnimation(this,"windowOpacity");
    noSee->setDuration(1000);
    noSee->setStartValue(0);
    noSee->setEndValue(1);
    // noSee->setEasingCurve(QEasingCurve::InOutQuart);
    noSee->start(QAbstractAnimation::DeleteWhenStopped);
}

void ChooseSence::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QTransform trans;
    // QPixmap pixmap(":/MIcon/180.png");
    // pixmap = pixmap.scaled(this->width(),this->height());
    // painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    if(!ended){
        painter.setBrush(Qt::black);
        painter.drawRect(QRect(0,0,this->width(),this->height()));
    }else{
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/MIcon/180.png"));
    }
}

void ChooseSence::start_gapWidgetEffect(){
    // QTimer::singleShot(1500,this,[=](){
    //     this->move(0,0);
    //     noSeeAnimation();
        QTimer::singleShot(500,this,[=](){
            this->move(780,200);
            noSeeAnimation();
            QTimer::singleShot(500,this,[=](){
                this->move(1560,500);
                noSeeAnimation();
                QTimer::singleShot(500,this,[=](){
                    this->move(1560,0);
                    noSeeAnimation();
                    QTimer::singleShot(500,this,[=](){
                        this->move(780,200);
                        noSeeAnimation();
                        QTimer::singleShot(500,this,[=](){
                            this->move(0,500);
                            noSeeAnimation();
                            QTimer::singleShot(500,this,[=](){
                                this->move(780,200);
                                noSeeAnimation();
                            });
                        });
                    });
                });
            });
        });
    // });
}

void ChooseSence::widthChangeAnimation(){
    start_widthChange();
    QTimer::singleShot(1000,this,[=](){
        end_widthChange();
    });
}

void ChooseSence::start_widthChange(){
    QPropertyAnimation* start_widthChange = new QPropertyAnimation(this,"geometry");
    start_widthChange->setDuration(1000);
    start_widthChange->setStartValue(QVariant(QRect(this->x(),this->y(),this->width(),this->height())));
    start_widthChange->setEndValue(QVariant(QRect(this->x()-400,this->y(),this->width()+780,this->height())));
    start_widthChange->start(QAbstractAnimation::DeleteWhenStopped);
}

void ChooseSence::end_widthChange(){
    QPropertyAnimation* end_widthChange = new QPropertyAnimation(this,"geometry");
    end_widthChange->setDuration(500);
    end_widthChange->setStartValue(QVariant(QRect(this->x(),this->y(),this->width(),this->height())));
    end_widthChange->setEndValue(QVariant(QRect(this->x()+400,this->y(),this->width() -780,this->height())));
    end_widthChange->setEasingCurve(QEasingCurve::OutBack);
    end_widthChange->start(QAbstractAnimation::DeleteWhenStopped);
}


