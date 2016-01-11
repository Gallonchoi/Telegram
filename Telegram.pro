#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T10:11:38
#
#-------------------------------------------------

QT += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Telegram
TEMPLATE = app

SOURCES +=\
    main.cc \
    mainwindow.cc \
    scanwindow.cc \
    logwindow.cc \
    aboutwindow.cc \
    connectwindow.cc \
    udpscanner.cc \
    udplistener.cc \
    tcpserver.cc \
    tcpclient.cc \
    filesender.cc \
    filereceiver.cc \
    tcpconnection.cc \
    greeting.cc \
    inboxwidget.cc

HEADERS  += \
    mainwindow.h \
    scanwindow.h \
    logwindow.h \
    aboutwindow.h \
    connectwindow.h \
    serverstatus.h \
    udpscanner.h \
    udplistener.h \
    tcpserver.h \
    tcpclient.h \
    filesender.h \
    filereceiver.h \
    tcpconnection.h \
    greeting.h \
    inboxwidget.h

FORMS += \
         mainwindow.ui \
         scanwindow.ui \
    logwindow.ui \
    aboutwindow.ui \
    connectwindow.ui \
    inboxwidget.ui

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11
