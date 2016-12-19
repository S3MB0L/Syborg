TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    src/client.c \
    src/serial.c \
    src/server.c \
    src/socket.c

HEADERS += \
    inc/main.h

DISTFILES += \
    README.md

unix|win32: LIBS += -lpthread-2.24
