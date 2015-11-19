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
    tcpserver.cpp \
    tcpclient.cpp

HEADERS  += widget.h \
    tcpserver.h \
    tcpclient.h

FORMS    += widget.ui \
    tcpserver.ui \
    tcpclient.ui

DISTFILES += \
    TcpserverForm.ui.qml \
    Tcpserver.qml

RESOURCES += \
    image.qrc
