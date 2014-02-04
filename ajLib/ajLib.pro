#-------------------------------------------------
#
# Project created by QtCreator 2014-01-14T10:56:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = ajLib
TEMPLATE = lib
CONFIG += staticlib

LIBS += -lGL -lGLU -glui -lglut

SOURCES += \
    src/ajmath/sequence.cpp \
    src/ajmath/matrix3.cpp \
    src/ajmath/matrix.cpp \
    src/ajmath/ajmath.cpp \
    src/ajutil/list.cpp \
    src/ajutil/ajutil.cpp \
    src/main.cpp \
    src/ajgl/window.cpp \
    src/ajgl/scene.cpp \
    src/ajgl/rectangle.cpp \
    src/ajgl/color.cpp \
    src/ajgl/object2d.cpp \
    src/ajutil/bTree.cpp

HEADERS += ajlib.h \
    src/ajmath/sequence.h \
    src/ajmath/matrix3.h \
    src/ajmath/matrix.h \
    src/ajmath/ajmath.h \
    src/ajutil/list.h \
    src/ajutil/ajutil.h \
    src/ajgl/window.h \
    src/ajgl/scene.h \
    src/ajgl/rectangle.h \
    src/ajgl/color.h \
    src/ajgl/object2d.h \
    src/ajutil/bTree.h

headers.path = $$OUT_PWD/inc
headers.files = ajlib.h \
    src/ajmath/*.h \
    src/ajutil/*.h

INSTALLS += headers

CONFIG(release, debug | release) {
    SOURCES -= src/main.cpp
}

CONFIG(debug, debug | release) {
    CONFIG -= staticlib
    CONFIG += console

    TEMPLATE -= lib
    TEMPLATE += app

    QT += core
}
