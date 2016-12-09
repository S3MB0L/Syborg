QT += core
QT -= gui

CONFIG += c++11

TARGET = syborg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
SOURCES += client.c
SOURCES += serial.c
SOURCES += server.c
SOURCES += socket.c

HEADERS += main.h
