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
    telegram.cc \
    logwindow.cc \
    aboutwindow.cc \
    connectwindow.cc \
    chattingserver.cc \
    udpscanner.cc \
    udplistener.cc \
    tcpserver.cc \
    tcpclient.cc

HEADERS  += \
    mainwindow.h \
    scanwindow.h \
    telegram.h \
    logwindow.h \
    aboutwindow.h \
    connectwindow.h \
    chattingserver.h \
    serverstatus.h \
    udpscanner.h \
    udplistener.h \
    tcpserver.h \
    tcpclient.h

FORMS += \
         mainwindow.ui \
         scanwindow.ui \
    logwindow.ui \
    aboutwindow.ui \
    connectwindow.ui
