#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QPainterPath>

myPushButton::myPushButton(QString normal):normalName(normal)
{

}

void myPushButton::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    update();
}


void myPushButton::paintEvent(QPaintEvent *ev){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap pixmap(normalName);
    if(pixmap.width() != pixmap.height()){
        return;
    }
    QPixmap tPixmap = pixmap.scaled(this->width(),this->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPainterPath path;
    QRect rect(0,0,this->width(),this->height());
    qDebug()<<this->width() << "  " << this->height();
    path.addEllipse(rect);
    painter.setClipPath(path);
    painter.drawPixmap(rect,tPixmap);
}

void myPushButton::setNormalName(QString path){
    this->normalName = path;
}
