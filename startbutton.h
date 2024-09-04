#ifndef STARTBUTTON_H
#define STARTBUTTON_H
#include <QPushButton>
#include <QWidget>


class StartButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit StartButton(QWidget *parent = nullptr);
    StartButton(QString normalName);

    virtual void enterEvent(QEnterEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void timerEvent(QTimerEvent *e);

    void animation_up();
    void animation_down();
    void paintEvent(QPaintEvent *ev);

    QString normalName;
    QPixmap m_pixmap;
signals:

};

#endif // STARTBUTTON_H
