QT += core
QT -= gui

CONFIG += c++11

TARGET = syborg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.c \
    serial.c \
    server.c \
    socket.c

HEADERS += \
    main.h
