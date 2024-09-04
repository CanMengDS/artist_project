#ifndef VIDEOFM_H
#define VIDEOFM_H

#include <QString>
#include <libswresample/swresample.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
}

class videoFm
{
public:
    videoFm(QString path);
    ~videoFm();
    int open(QString path);
    int close();
private:
    QString path;
    AVStream* av_stream = nullptr;
    AVFormatContext* av_format = nullptr;
};

#endif // VIDEOFM_H
