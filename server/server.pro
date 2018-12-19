QT += core
QT -= gui
QT       += core network


CONFIG += c++11

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

DISTFILES += \
    server.pro.user

HEADERS += \
    server.h

unix:!macx: LIBS += -L$$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug/ -ldata_types

INCLUDEPATH += $$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug
DEPENDPATH += $$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug
