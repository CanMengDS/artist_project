#include "startbutton.h"
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimerEvent>

// StartButton::StartButton(QWidget *parent)
//     : QPushButton{parent}
// {}

    StartButton::StartButton(QString normalName){
        this->normalName = normalName;
        QPixmap pixmap;
        bool ix = pixmap.load(normalName);
        pixmap = pixmap.scaled(pixmap.width() * 0.5,pixmap.height() * 0.5);
        if(!ix){
            qDebug()<< "加载失败";
            return;
        }
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->m_pixmap = pixmap;
        // this->setStyleSheet("QPushButton{border:0px;}");
        // this->setIcon(pixmap);
        // this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        this->setCursor(QCursor(Qt::PointingHandCursor));
    }

    void StartButton::timerEvent(QTimerEvent *e){
        if(this->y() < 450 - 10){
            this->move(this->x(),450);
            qDebug() << "控件y轴已超过450";
            return;
        }
    }

    void StartButton::leaveEvent(QEvent *){
        if(this->y() < 450 - 10){
            this->move(this->x(),450);
            qDebug() << "控件y轴已超过450";
        }
        qDebug()<< "离开控件,改为false";
    }

    void StartButton::enterEvent(QEnterEvent *){
        if(this->y() < 450 - 10){
            this->move(this->x(),450);
            qDebug() << "控件y轴已超过450";
        }
        qDebug()<< "进入控件,改为true";
        animation_up();
        animation_down();
    }

    void StartButton::paintEvent(QPaintEvent *ev){
        QPainter painter(this);
        m_pixmap = m_pixmap.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,this->width(),this->height(),m_pixmap);
    }

    void StartButton::animation_up(){
        QPropertyAnimation* animationBig = new QPropertyAnimation(this,"geometry");
        animationBig->setDuration(500);
        animationBig->setStartValue(QVariant(QRect(this->x(),this->y(),this->width(),this->height())));
        animationBig->setEndValue(QVariant(QRect(this->x() , this->y() +20,this->width()+10,this->height()+10)));
        animationBig->setEasingCurve(QEasingCurve::InOutBack);
        animationBig->start();
    }

    void StartButton::animation_down(){
        QPropertyAnimation* animationBig = new QPropertyAnimation(this,"geometry");
        animationBig->setDuration(600);
        animationBig->setStartValue(QVariant(QRect(this->x(),this->y() -20,this->width(),this->height())));
        animationBig->setEndValue(QVariant(QRect(this->x(), this->y(),this->width()-10,this->height()-10)));
        animationBig->setEasingCurve(QEasingCurve::InOutBack);
        animationBig->start();
    }

    void endAnimation(QPropertyAnimation& pa){
        pa.stop();
    }
