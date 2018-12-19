#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T11:58:59
#
#-------------------------------------------------

QT       += core gui
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    file_name_dialog.cpp \
    error_message.cpp \
    creation_dialog.cpp \
    connection_dialog.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    file_name_dialog.h \
    error_message.h \
    creation_dialog.h \
    connection_dialog.h \
    client.h

FORMS    += mainwindow.ui \
    filenamedialog.ui \
    errormessage.ui \
    creationdialog.ui \
    connectiondialog.ui

DISTFILES += \
    client.pro.user

unix:!macx: LIBS += -L$$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug/ -ldata_types

INCLUDEPATH += $$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug
DEPENDPATH += $$PWD/../build-data_types-Desktop_Qt_5_7_0_GCC_64bit-Debug
