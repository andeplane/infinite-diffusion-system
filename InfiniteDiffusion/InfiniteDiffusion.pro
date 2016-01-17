TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -vec-report=2 -openmp
QMAKE_LFLAGS += -openmp
QT += qml quick widgets opengl openglextensions

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
    geometry/voidgeometry.cpp \
    intelrandom.cpp

LIBS += -L/projects/GeometryLibrary/build-GeometryLibrary-Intel_Compiler-Release -lGeometryLibrary
#LIBS += -L/projects/GeometryLibrary/build-GeometryLibrary-Desktop_Qt_5_5_1_clang_64bit-Release/ -lGeometryLibrary
LIBS += -L/usr/local/lib -lgsl
INCLUDEPATH += /projects/GeometryLibrary/GeometryLibrary
INCLUDEPATH += /usr/local/include

INCLUDEPATH += /opt/intel/mkl/include
LIBS += -L/opt/intel/mkl/lib/ -lmkl_intel_thread -lmkl_core -lmkl_intel_ilp64
LIBS += -L/opt/intel/compilers_and_libraries/mac/lib

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
    geometry/voidgeometry.h \
    intelrandom.h
