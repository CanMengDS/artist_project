#ifndef CHOOSESENCE_H
#define CHOOSESENCE_H

#include <QMainWindow>
#include <QPushButton>
#include <QMap>
#include "mypushbutton.h"

class ChooseSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseSence(QWidget *parent = nullptr);
    // ChooseSence(QPushButton& pb);
    void initiali_Setting_WidgetControl();
    void end_AnimationiInitialiWidget();
    void paintEvent(QPaintEvent *event);
    void noSeeAnimation();
    void levelControlInitiali();
    void levelControlAddPixmap();

    void mainSm();

    void formalStartWidgetAnimation();
    void developerStartWidget();

    bool event(QEvent *event);
    void widthChangeAnimation();
    void end_widthChange();
    void start_widthChange();
    void start_moveAnimationEffect();
    void start_gapWidgetEffect();

    QMap<int,myPushButton*> levelControlMap;
    QPushButton* back;
    bool ended = false;
signals:
    void backMainWidget();
    void startAnimation();
};

#endif // CHOOSESENCE_H
