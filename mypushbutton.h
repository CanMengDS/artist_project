#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QString normal);

    void paintEvent(QPaintEvent *ev);
    void setNormalName(QString path);
    void resizeEvent(QResizeEvent *event);
    QString normalName;
signals:
};

#endif // MYPUSHBUTTON_H
