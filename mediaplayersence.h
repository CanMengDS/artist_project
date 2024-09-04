#ifndef MEDIAPLAYERSENCE_H
#define MEDIAPLAYERSENCE_H
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QScreen>

class mediaPlayerSence:public QWidget
{
public:
    mediaPlayerSence(QString path);
};

#endif // MEDIAPLAYERSENCE_H
