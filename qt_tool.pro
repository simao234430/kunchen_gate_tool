#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T09:55:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_tool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    network.cpp \
    stationdata.cpp \
    config.cpp \
    tablemodel.cpp


HEADERS  += mainwindow.h \
    network.h \
    stationdata.h \
    config.h \
    tablemodel.h

FORMS    += mainwindow.ui
