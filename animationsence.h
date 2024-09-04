#ifndef ANIMATIONSENCE_H
#define ANIMATIONSENCE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QUrl>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QScreen>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
}


class AnimationSence : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationSence(const QString path);
    void paintEvent(QPaintEvent *event);
    ~AnimationSence();
private:
    QScreen* tScreen;
    AVFormatContext *formatContext = nullptr;
    AVCodecContext *codecContext = nullptr;
    AVFrame *frame = nullptr;
    AVFrame *frameRGB = nullptr;
    struct SwsContext *swsContext = nullptr;
    QString videoPath;
    QTimer *timer = nullptr;

    void initFFmpeg();
    void decodeAndDisplayFrame();
signals:
};

#endif // ANIMATIONSENCE_H
