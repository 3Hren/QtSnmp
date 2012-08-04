TEMPLATE = app
DESTDIR = ../../../bin/tests
TARGET = tst_qtsnmplibtest

QT       += network testlib
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += tst_qtsnmplibtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../lib
DEPENDPATH += ../../lib

include(../../lib/QtSnmp.pri)

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS="-std=c++0x" ./configure

unix:{
    OBJECTS_DIR = ./debug/obj
    MOC_DIR = ./debug/moc
}
