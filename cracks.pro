#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T15:47:52
#
#-------------------------------------------------

QT       += core gui opengl cgal
TARGET = cracks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    viewer.cpp \
    mud.cpp \
    mudparticle.cpp \
    mudspring.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    viewer.h \
    mud.h \
    mudparticle.h \
    mudspring.h \
    utils.h

FORMS    += mainwindow.ui


LIBS += -lCGAL

QMAKE_CXXFLAGS += -std=c++0x -frounding-math
