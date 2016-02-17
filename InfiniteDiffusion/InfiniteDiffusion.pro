TEMPLATE = app
CONFIG -= app_bundle
CONFIG += c++11

QT += qml quick widgets opengl openglextensions

SOURCES += main.cpp \
    GeometryLibrary/models/multifractalmodel.cpp \
    GeometryLibrary/models/regularnoisemodel.cpp \
    GeometryLibrary/noise.cpp \
    GeometryLibrary/parameters.cpp \
    GeometryLibrary/perlin.cpp \
    GeometryLibrary/simplex.cpp \
    GeometryLibrary/simplexnoise.cpp \
    GeometryLibrary/models/model.cpp \
    mysimulator.cpp \
    system.cpp \
    particle.cpp \
    random.cpp \
    statistics/statistic.cpp \
    statistics/statisticdiffusiondistribution.cpp \
    datasource.cpp \
    nogui.cpp \
    cutil.cpp


INCLUDEPATH += /usr/local/include
#INCLUDEPATH += GeometryLibrary
LIBS += -L/usr/local/lib -lgsl -lgslcblas

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include(../SimVis/library_deployment.pri)

HEADERS += \
    GeometryLibrary/models/multifractalmodel.h \
    GeometryLibrary/models/regularnoisemodel.h \
    GeometryLibrary/models/model.h \
    GeometryLibrary/models/models.h \
    GeometryLibrary/noise.h \
    GeometryLibrary/parameters.h \
    GeometryLibrary/perlin.h \
    GeometryLibrary/simplex.h \
    GeometryLibrary/simplexnoise.h \
    mysimulator.h \
    system.h \
    particle.h \
    random.h \
    statistics/statistic.h \
    statistics/statisticdiffusiondistribution.h \
    statistics/statistics.h \
    datasource.h \
    nogui.h \
    cinifile.h \
    cutil.h
