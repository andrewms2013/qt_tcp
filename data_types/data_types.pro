#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T12:18:46
#
#-------------------------------------------------

QT   += gui
QT += xml
QT += core
QT += core network
QT += widgets

TARGET = data_types
TEMPLATE = lib

DEFINES += DATA_TYPES_LIBRARY

SOURCES += \
    for_free.cpp \
    json_storage.cpp \
    storage_manager.cpp \
    tour_operator.cpp \
    request.cpp \
    response.cpp \
    serialisator.cpp

HEADERS +=\
        data_types_global.h \
    for_free.h \
    json_storage.h \
    storage_manager.h \
    tour_operator.h \
    request.h \
    response.h \
    serialisator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    data_types.pro.user
