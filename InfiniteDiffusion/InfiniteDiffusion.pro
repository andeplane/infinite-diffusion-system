TEMPLATE = app
CONFIG += c++11

QT += qml quick widgets opengl openglextensions svg

SOURCES += main.cpp \
    mysimulator.cpp \
    system.cpp \
    particle.cpp \
    geometry/perlingeometry.cpp \
    geometry/geometry.cpp \
    geometry/cylindergeometry.cpp \
    random.cpp \
    figure.cpp \
    linegraph.cpp \
    graph.cpp \
    geometry/voidgeometry.cpp

LIBS += -L../../build-GeometryLibrary-Desktop_Qt_5_5_1_clang_64bit-Release/
LIBS += -L/projects/GeometryLibrary/build-GeometryLibrary-Desktop_Qt_5_5_1_clang_64bit-Release
LIBS += -lGeometryLibrary
INCLUDEPATH += /projects/GeometryLibrary/GeometryLibrary
INCLUDEPATH += ../../GeometryLibrary/

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lgsl

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
    random.h \
    figure.h \
    linegraph.h \
    graph.h \
    geometry/voidgeometry.h
