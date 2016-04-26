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
    property alias spheresVisible: spheres.visible
    property alias octreeVisible: octreeTriangles.visible
    property alias spheresScale: spheres.scale
    property alias pointsVisible: points.visible
    property alias pointsScale: points.pointSize

    camera: Camera {
        id: camera
        position: Qt.vector3d(0,0,-300)
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
        visible: true
        pointSize: 1.0
    }

    Spheres {
        id: spheres
        color: "red"
        scale: 1.5
        enabled: false
        visible: false
        Light {
            id: light
            ambientColor: "yellow"
            specularColor: "white"
            diffuseColor: spheres.color
            ambientIntensity: 0.5
            diffuseIntensity: 0.5
            specularIntensity: 1.0
            shininess: 40.0
            attenuation: 0.01
            position: camera.position
        }
    }

    TriangleCollection {
        id: octreeTriangles
        alpha: 0.15
    }
}
