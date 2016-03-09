import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import GeometryLibrary 1.0

Visualizer {
    property alias visualizeOctree: octreeTriangles.visible
    property alias alpha: octreeTriangles.alpha
    camera: Camera {
        id: camera
        position: Qt.vector3d(0,0,-5000)
        farPlane: 1000000
    }
    backgroundColor: "black"
    
    TrackballNavigator {
        id: navigator
        anchors.fill: parent
        camera: camera
    }
    
    Points {
        id: points
        pointSize: 2.0
    }
    TriangleCollection {
        id: octreeTriangles
    }
}
