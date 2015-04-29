#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T19:34:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ESWalpappers
TEMPLATE = app


SOURCES += main.cpp\
        eswindow.cpp \
    configmanager.cpp \
    config.cpp \
    imagemanager.cpp

HEADERS  += eswindow.h \
    configmanager.h \
    config.h \
    imagemanager.h

FORMS    += eswindow.ui

RESOURCES += \
    res/resources.qrc
