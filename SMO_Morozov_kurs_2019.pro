#-------------------------------------------------
#
# Project created by QtCreator 2019-11-17T17:09:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMO_Morozov_kurs_2019
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    configure.cpp \
    automode.cpp \
    stepmode.cpp \
    request.cpp \
    source.cpp \
    buffer.cpp \
    controller.cpp \
    analytics.cpp \
    device.cpp

HEADERS += \
        mainwindow.h \
    configure.h \
    automode.h \
    stepmode.h \
    request.h \
    source.h \
    controller.h \
    buffer.h \
    device.h \
    analytics.h

FORMS += \
        mainwindow.ui \
    configure.ui \
    automode.ui \
    stepmode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
