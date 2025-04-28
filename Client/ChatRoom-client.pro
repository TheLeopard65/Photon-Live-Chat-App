QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Client
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui
