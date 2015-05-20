#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T11:58:56
#
#-------------------------------------------------

QT       += core network

QT       -= gui

QMAKE_CXXFLAGS = -std=c++11

TARGET = OTable
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    CommServer.cpp \
    RCBMsgParser.cpp

HEADERS += \
    CommServer.h \
    RCBMsgParser.h
