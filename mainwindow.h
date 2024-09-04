#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "choosesence.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    void paintBackground();
    void opacityAnimation();
    void levelControlInitiali();

    ChooseSence* choose = NULL;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
