#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T17:35:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anything
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filefolder.cpp \
    node.cpp \
    filestatemachine.cpp \
    sqlite3.c \
    filequery.cpp

HEADERS  += mainwindow.h \
    filefolder.h \
    node.h \
    filestatemachine.h \
    sqlite3.h \
    filequery.h

FORMS    += mainwindow.ui
