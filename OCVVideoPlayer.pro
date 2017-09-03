#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T17:14:29
#
#-------------------------------------------------

QT       += core gui widgets
#CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OCVVideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videothread.cpp

HEADERS  += mainwindow.h \
    videothread.h

FORMS    += mainwindow.ui



INCLUDEPATH += /usr/local/include


LIBS += -L/usr/local/lib\
        -lopencv_core\
        -lopencv_highgui\
        -lopencv_imgcodecs\
        -lopencv_imgproc\
        -lopencv_videoio\
        -llept
