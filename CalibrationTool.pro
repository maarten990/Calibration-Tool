#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T09:16:09
#
#-------------------------------------------------

QT       += core gui

TARGET = CalibrationTool
TEMPLATE = app

unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += opencv
}

SOURCES += main.cpp\
        mainwindow.cpp \
    calgraphicsview.cpp

HEADERS  += mainwindow.h \
    calgraphicsview.h

FORMS    += mainwindow.ui
