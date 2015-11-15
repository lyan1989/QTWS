#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T20:44:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tcpserver.cpp

HEADERS  += widget.h \
    tcpserver.h

FORMS    += widget.ui \
    tcpserver.ui

DISTFILES += \
    TcpserverForm.ui.qml \
    Tcpserver.qml
