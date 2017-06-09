#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T08:58:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += C++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ILoveBaseball
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    stadium.cpp \
    baseball_graph.cpp

HEADERS  += mainwindow.h \
    user.h \
    stadium.h \
    baseball_graph.h \
    graph.h \
    vertex.h

FORMS    += mainwindow.ui
