#include "mediaplayersence.h"

mediaPlayerSence::mediaPlayerSence(QString path) {
    QVideoWidget* video = new QVideoWidget(this);
    QMediaPlayer* player = new QMediaPlayer(this);
    player->setVideoOutput(video);
    player->setSource(QUrl::fromLocalFile(path));
    video->setParent(this);
    video->resize(this->size());
    player->play();
}
