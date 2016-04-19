#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T23:55:57
#
#-------------------------------------------------

QT       -= gui

TARGET = QMaroxLib
TEMPLATE = lib

DEFINES += QMAROXLIB_LIBRARY

SOURCES += \
    QMaroxLib.cpp

HEADERS +=\
        qmaroxlib_global.h \
    QMaroxLib.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
