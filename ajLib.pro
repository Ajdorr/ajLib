TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lGLU -lglut -lglui

SOURCES += main.cpp \
    ajgl/object.cpp \
    ajgl/window.cpp \
    ajmath/sequence.cpp \
    ajmath/matrix4.cpp \
    ajmath/matrix3.cpp \
    ajmath/matrix.cpp \
    ajmath/ajmath.cpp \
    ajutil/list.cpp \
    ajutil/dlist.cpp \
    ajutil/bTree.cpp \
    ajutil/ajutil.cpp \
    ajgl/primitives.cpp \
    ajgl/material.cpp \
    ajutil/idtable.cpp \
    ajgl/scene.cpp \
    ajutil/kdtree.cpp \
    ajgl/camera.cpp

HEADERS += \
    ajlib.h \
    ajgl/window.h \
    ajgl/object.h \
    ajgl/ajgl.h \
    ajmath/sequence.h \
    ajmath/matrix4.h \
    ajmath/matrix3.h \
    ajmath/matrix.h \
    ajmath/ajmath.h \
    ajutil/list.h \
    ajutil/dlist.h \
    ajutil/bTree.h \
    ajutil/ajutil.h \
    ajgl/primitives.h \
    ajgl/material.h \
    ajutil/idtable.h \
    ajgl/scene.h \
    ajutil/kdtree.h \
    ajgl/camera.h

