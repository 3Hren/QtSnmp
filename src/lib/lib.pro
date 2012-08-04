TEMPLATE = lib
DESTDIR = ../../lib
TARGET = qtsnmp

QT       += core
QT       -= gui

CONFIG   += console debug

SOURCES += main.cpp

include(QtSnmp.pri)

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS="-std=c++0x" ./configure

unix:{
    OBJECTS_DIR = ./debug/obj
    MOC_DIR = ./debug/moc
}
