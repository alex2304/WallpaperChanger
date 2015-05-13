#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T19:34:04
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4){
  QT += widgets
}

#VERSION = 1.0.0.0
#QMAKE_TARGET_PRODUCT = ES Wallpaper Changer
#QMAKE_TARGET_DESCRIPTION = Simple and functional wallpaper manager
#QMAKE_TARGET_COPYRIGHT = Alexey Marashov, alex2304el@gmail.com

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

RC_FILE = info.rc

LIBS += -L/libs
