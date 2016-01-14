TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets opengl openglextensions

SOURCES += main.cpp \
    mysimulator.cpp \
    system.cpp \
    particle.cpp \
    geometry/perlingeometry.cpp \
    geometry/geometry.cpp \
    geometry/cylindergeometry.cpp \
    random.cpp

unix|win32: LIBS += -L$$PWD/../../build-GeometryLibrary-Desktop_Qt_5_5_1_clang_64bit-Release/ -lGeometryLibrary.1.0.0

INCLUDEPATH += $$PWD/../../GeometryLibrary
DEPENDPATH += $$PWD/../../GeometryLibrary


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include(../SimVis/library_deployment.pri)

HEADERS += \
    mysimulator.h \
    system.h \
    particle.h \
    geometry/perlingeometry.h \
    geometry/geometry.h \
    geometry/cylindergeometry.h \
    geometry/geometries.h \
    random.h
