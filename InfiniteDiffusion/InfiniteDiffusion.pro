TEMPLATE = app
#CONFIG -= app_bundle
CONFIG += c++11
# DEFINES += RUNUNITTESTS
QT += qml quick widgets opengl openglextensions charts

SOURCES += main.cpp \
    GeometryLibrary/models/multifractalmodel.cpp \
    GeometryLibrary/models/regularnoisemodel.cpp \
    GeometryLibrary/noise.cpp \
    GeometryLibrary/parameters.cpp \
    GeometryLibrary/perlin.cpp \
    GeometryLibrary/simplex.cpp \
    GeometryLibrary/simplexnoise.cpp \
    GeometryLibrary/models/model.cpp \
    GeometryLibrary/models/octree.cpp \
    GeometryLibrary/models/xyzmodel.cpp \
    GeometryLibrary/likelihood/graphstatistics.cpp \
    GeometryLibrary/likelihood/lgraph.cpp \
    GeometryLibrary/likelihood/likelihood.cpp \
    GeometryLibrary/misc/cutil.cpp \
    GeometryLibrary/misc/util.cpp \
    mysimulator.cpp \
    system.cpp \
    particle.cpp \
    statistics/statistic.cpp \
    statistics/statisticdiffusiondistribution.cpp \
    datasource.cpp \
    nogui.cpp \
    unittests.cpp \
    GeometryLibrary/models/cylindermodel.cpp \
    GeometryLibrary/models/voidmodel.cpp \
    statistics/msdstatistic.cpp \
    GeometryLibrary/logger.cpp


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
    GeometryLibrary/models/octree.h \
    GeometryLibrary/models/models.h \
    GeometryLibrary/noise.h \
    GeometryLibrary/parameters.h \
    GeometryLibrary/perlin.h \
    GeometryLibrary/simplex.h \
    GeometryLibrary/simplexnoise.h \
    GeometryLibrary/models/xyzmodel.h \
    GeometryLibrary/likelihood/graphstatistics.h \
    GeometryLibrary/likelihood/lgraph.h \
    GeometryLibrary/likelihood/likelihood.h \
    GeometryLibrary/likelihood/spline.h \
    GeometryLibrary/misc/cinifile.h \
    GeometryLibrary/misc/cutil.h \
    GeometryLibrary/misc/util.h \
    mysimulator.h \
    system.h \
    particle.h \
    statistics/statistic.h \
    statistics/statisticdiffusiondistribution.h \
    statistics/statistics.h \
    datasource.h \
    nogui.h \
    GeometryLibrary/misc/random.h \
    catch.hpp \
    GeometryLibrary/models/cylindermodel.h \
    GeometryLibrary/models/voidmodel.h \
    statistics/msdstatistic.h \
    GeometryLibrary/logger.h

DISTFILES += \
    GeometryLibrary/README.md
