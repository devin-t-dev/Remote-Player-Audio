#-------------------------------------------------
#
# Project created by QtCreator 2014-08-09T17:04:46
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Console
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Output/Error.cpp \
    ../../Output/ffmpeg.cpp \
    ../../Output/Riproduttore.cpp \
    ../../Output/util.cpp \
    ../../Output/mpg123.c \
    ../../Process/Fx/Echo.cpp \
    ../../Process/Fx/Delay.c \
    ../../Process/Fx/Flanger.c \
    ../../Process/Fx/Reverb.c \
    ../../Process/sampleConversion.c \
    ../../Input/Analyze.cpp \
    ../../Input/Archive.cpp \
    ../../Input/Load.cpp

HEADERS  += mainwindow.h \
    ../../Output/ffmpeg.h \
    ../../Output/mpg123.h \
    ../../Output/Riproduttore.h \
    ../../Output/util.h \
    ../../Process/Fx/Delay.h \
    ../../Process/Fx/Flanger.h \
    ../../Input/Analyze.h \
    ../../Input/Archive.h \
    ../../Input/Load.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -lao

unix:!macx: LIBS += -lmpg123

unix:!macx: LIBS += -lavcodec

unix:!macx: LIBS += -lavformat
