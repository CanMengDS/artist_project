QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=E:\ffmpeg-7.0.2-full_build-shared\include

LIBS+=-L E:\ffmpeg-7.0.2-full_build-shared\lib \
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavutil \
        -lavformat\
        -lpostproc \
        -lswresample \
        -lswscale

SOURCES += \
    choosesence.cpp \
    main.cpp \
    mainwindow.cpp \
    mediaplayersence.cpp \
    mypushbutton.cpp \
    startbutton.cpp

HEADERS += \
    choosesence.h \
    mainwindow.h \
    mediaplayersence.h \
    mypushbutton.h \
    startbutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
