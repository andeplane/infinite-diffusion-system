#ifdef RUNUNITTESTS

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "GeometryLibrary/models/models.h"
#include <QFile>
#include <QUrl>
#include <QDebug>

TEST_CASE( "Validate models", "[models]" ) {
    XYZModel xyzModel;
    Octree octreeModel;
    SECTION( "Are the parameters created?" ) {
        REQUIRE(xyzModel.parameters()->getParameter("voxelsperdimension") != nullptr);
        REQUIRE(xyzModel.parameters()->getParameter("threshold") != nullptr);
        REQUIRE(xyzModel.parameters()->getParameter("maxdistance") != nullptr);

        REQUIRE(octreeModel.parameters()->getParameter("maxdepth") != nullptr);
        REQUIRE(octreeModel.parameters()->getParameter("threshold") != nullptr);
    }

    xyzModel.parameters()->getParameter("voxelsperdimension")->setValue(32);
    xyzModel.parameters()->getParameter("threshold")->setValue(2.0);
    xyzModel.parameters()->getParameter("maxdistance")->setValue(15);
    SECTION( "Did we set the parameter values properly?" ) {
        REQUIRE(xyzModel.parameters()->getValue("voxelsperdimension")==32);
        REQUIRE(xyzModel.parameters()->getValue("threshold")==2.0);
        REQUIRE(xyzModel.parameters()->getValue("maxdistance")==15);
        REQUIRE(xyzModel.voxelsPerDimension()==32);
        REQUIRE(xyzModel.threshold()==2.0);
        REQUIRE(xyzModel.maxDistance()==15);
    }
    QString filename(":/sio2_bulk.xyz");
    xyzModel.setFile(filename);
    xyzModel.readFile();
    xyzModel.updateDistanceToAtomField();
}
#endif
