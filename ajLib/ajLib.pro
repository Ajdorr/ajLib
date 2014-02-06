#-------------------------------------------------
#
# Project created by QtCreator 2014-01-14T10:56:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = ajLib csc418a1
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
    src/ajgl/color.cpp \
    src/ajutil/bTree.cpp \
    src/ajgl/object.cpp \
    src/ajmath/matrix4.cpp \
    src/ajutil/dlist.cpp

HEADERS += \
    src/ajlib.h \
    src/ajmath/sequence.h \
    src/ajmath/matrix3.h \
    src/ajmath/matrix.h \
    src/ajmath/ajmath.h \
    src/ajutil/list.h \
    src/ajutil/ajutil.h \
    src/ajgl/window.h \
    src/ajgl/color.h \
    src/ajutil/bTree.h \
    src/ajgl/object.h \
    src/ajmath/matrix4.h \
    src/ajgl/ajgl.h \
    src/ajutil/dlist.h

ajlib.path = $$OUT_PWD/inc
ajlib.files = src/ajlib.h

mathlib.path = $$OUT_PWD/inc/ajmath
mathlib.files = src/ajmath/*.h

utillib.path = $$OUT_PWD/inc/ajutil
utillib.files = src/ajutil/*.h

gllib.path = $$OUT_PWD/inc/ajgl
gllib.files = src/ajgl/*.h

INSTALLS += ajlib mathlib utillib gllib

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

OTHER_FILES +=
