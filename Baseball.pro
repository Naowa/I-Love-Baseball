TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    baseball_graph.cpp \
    stadium.cpp

HEADERS += \
    Graph.h \
    baseball_graph.h \
    stadium.h \
    vertex.h \
    national_stadium.h \
    american_stadium.h

