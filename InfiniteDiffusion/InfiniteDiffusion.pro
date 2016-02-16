TEMPLATE = app
CONFIG -= app_bundle
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
    geometry/voidgeometry.cpp \
    QMLPlot/figure.cpp \
    QMLPlot/graph.cpp \
    QMLPlot/linegraph.cpp \
    GeometryLibrary/geometrylibrary.cpp \
    GeometryLibrary/model.cpp \
    GeometryLibrary/models/multifractalmodel.cpp \
    GeometryLibrary/models/multifractalparameters.cpp \
    GeometryLibrary/models/regularmodel.cpp \
    GeometryLibrary/noise.cpp \
    GeometryLibrary/parameters.cpp \
    GeometryLibrary/perlin.cpp \
    GeometryLibrary/simplex.cpp \
    GeometryLibrary/simplexnoise.cpp \
    statistics/statistic.cpp \
    statistics/statisticdiffusiondistribution.cpp \
    datasource.cpp \
    nogui.cpp \
    cutil.cpp \
    GeometryLibrary/models/regularparameters.cpp


INCLUDEPATH += /usr/local/include
INCLUDEPATH += GeometryLibrary
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
    geometry/voidgeometry.h \
    QMLPlot/figure.h \
    QMLPlot/graph.h \
    QMLPlot/linegraph.h \
    GeometryLibrary/geometrylibrary.h \
    GeometryLibrary/model.h \
    GeometryLibrary/models/multifractalmodel.h \
    GeometryLibrary/models/multifractalparameters.h \
    GeometryLibrary/models/regularmodel.h \
    GeometryLibrary/noise.h \
    GeometryLibrary/parameters.h \
    GeometryLibrary/perlin.h \
    GeometryLibrary/simplex.h \
    GeometryLibrary/simplexnoise.h \
    statistics/statistic.h \
    statistics/statisticdiffusiondistribution.h \
    statistics/statistics.h \
    datasource.h \
    nogui.h \
    cinifile.h \
    cutil.h \
    GeometryLibrary/models/regularparameters.h
