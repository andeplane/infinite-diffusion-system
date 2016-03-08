#ifdef RUNUNITTESTS

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "GeometryLibrary/models/models.h"
#include <QFile>
#include <QUrl>
#include <QDebug>

TEST_CASE( "XYZ model", "[models]" ) {
    XYZModel xyzModel;
    SECTION( "Are the parameters created?" ) {
        REQUIRE(xyzModel.parameters()->getParameter("voxelsperdimension") != nullptr);
        REQUIRE(xyzModel.parameters()->getParameter("threshold") != nullptr);
        REQUIRE(xyzModel.parameters()->getParameter("maxdistance") != nullptr);
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
    SECTION( "Is system read correctly?" ) {
        REQUIRE(xyzModel.getLx()<=158.0);
        REQUIRE(xyzModel.getLy()<=158.0);
        REQUIRE(xyzModel.getLz()<=158.0);
        REQUIRE(xyzModel.getLx()>=157.0);
        REQUIRE(xyzModel.getLy()>=157.0);
        REQUIRE(xyzModel.getLz()>=157.0);
        REQUIRE(xyzModel.getPoints().size()==255552);
        REQUIRE(xyzModel.getPoints()[0]==QVector3D(156.936, 3.29732, 5.05774));
        REQUIRE(xyzModel.getPoints()[3]==QVector3D(0.617383, 149.326, 5.73065));
        REQUIRE(xyzModel.getPoints().last()==QVector3D(145.012, 148.467, 148.465));
    }

    int numCellsX = xyzModel.getLx() / xyzModel.maxDistance();
    int numCellsY = xyzModel.getLy() / xyzModel.maxDistance();
    int numCellsZ = xyzModel.getLz() / xyzModel.maxDistance();

    // If max distance is too large, have at least three cells
    if(numCellsX < 3) numCellsX = 3;
    if(numCellsY < 3) numCellsY = 3;
    if(numCellsZ < 3) numCellsZ = 3;

    QVector3D cellSize(xyzModel.getLx() / numCellsX, xyzModel.getLy() / numCellsY, xyzModel.getLz() / numCellsZ);
    CellList cellList = xyzModel.buildCellList(cellSize, numCellsX, numCellsY, numCellsZ);
    SECTION( "Cell list" ) {
        REQUIRE(cellList.size()==numCellsX);
        REQUIRE(cellList[0].size()==numCellsY);
        REQUIRE(cellList[0][0].size()==numCellsZ);
    }

//    xyzModel.updateDistanceToAtomField();
}
#endif
