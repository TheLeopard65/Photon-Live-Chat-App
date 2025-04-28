QT -= gui
QT += core network
CONFIG += c++11 console
CONFIG -= app_bundle
TARGET = Server
DEFINES += QT_DEPRECATED_WARNINGS
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += main.cpp chatserver.cpp clienthandlerthread.cpp customtcpsocket.cpp
HEADERS += chatserver.h clienthandlerthread.h customtcpsocket.h
