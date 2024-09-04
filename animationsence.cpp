  #include "animationsence.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>

AnimationSence::AnimationSence(const QString path):videoPath(path){
    initFFmpeg();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AnimationSence::decodeAndDisplayFrame);
    timer->start(1000 / 30); // 假设视频是25fps
    setFixedSize(640, 480); // 设置窗口大小
}

AnimationSence::~AnimationSence() {
    if (frame) {
        av_frame_free(&frame);
    }
    if (frameRGB) {
        av_frame_free(&frameRGB);
    }
    if (swsContext) {
        sws_freeContext(swsContext);
    }
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
    if (formatContext) {
        avformat_close_input(&formatContext);
    }
    delete timer;
}

void AnimationSence::initFFmpeg() {

    if (avformat_open_input(&formatContext, videoPath.toStdString().c_str(), nullptr, nullptr) != 0) {
        // 错误处理
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        // 错误处理
    }

    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        // 错误处理
    }

    AVCodecParameters *codecParameters = formatContext->streams[videoStreamIndex]->codecpar;
    const     AVCodec *codec = avcodec_find_decoder(codecParameters->codec_id);
    if (!codec) {
        // 错误处理
    }

    codecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecContext, codecParameters);
    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        // 错误处理
    }

    frame = av_frame_alloc();
    frameRGB = av_frame_alloc();

    swsContext = sws_getContext(
        codecContext->width,
        codecContext->height,
        codecContext->pix_fmt,
        codecContext->width,
        codecContext->height,
        AV_PIX_FMT_RGB24,
        SWS_BILINEAR,
        nullptr,
        nullptr,
        nullptr
        );
}

void AnimationSence::decodeAndDisplayFrame() {
    AVPacket packet;
    if (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == 0) {
            if (avcodec_send_packet(codecContext, &packet) == 0) {
                while (avcodec_receive_frame(codecContext, frame) == 0) {
                    sws_scale(
                        swsContext,
                        (uint8_t const * const *)frame->data,
                        frame->linesize,
                        0,
                        codecContext->height,
                        frameRGB->data,
                        frameRGB->linesize
                        );

                    update(); // 通知QWidget重绘
                }
            }
        }
        av_packet_unref(&packet);
    }
}

void AnimationSence::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (frameRGB->data[0]) {
        // 将解码后的帧绘制到窗口上
        painter.drawImage(0, 0, QImage(
                                    frameRGB->data[0],
                                    codecContext->width,
                                    codecContext->height,
                                    QImage::Format_RGB888
                                    ));
    }
}

