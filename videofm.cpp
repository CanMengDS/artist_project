#include "videofm.h"
#include <QDebug>

videoFm::viedeoFm(QString path) {
    this->path = path;
    av_format = avformat_alloc_context(); //avformatContext的初始化
}

int videoFm::open(QString path){
    if(av_format == nullptr){
        return -1;
    }
    int ret = avformat_open_input(av_format,path,nullptr,nullptr);

    if(ret != 0){
        qDebug()<< "ret返回数据不为true";
    }

    if(!ret){
        ret = avformat_find_stream_info(av_format,nullptr);
    }
    return ret;
}

int videoFm::close()
{
    if(av_format == nullptr){
        return -1;
    }
    avformat_close_input(av_format);
    return 0;
}

videoFm::~videoFm()
{
    if(av_format != nullptr){
        avformat_free_context(av_format);
        av_format = nullptr;
    }
}
