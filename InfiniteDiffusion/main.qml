import QtQuick 2.5
import QtQuick.Window 2.2
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0

Window {
    visible: true
    width: 1024
    height: 768
    MySimulator {
        id: simulator
        diffusionGeometry: CylinderGeometry {
            radius: 1.0
        }
    }

    Visualizer {
        anchors.fill: parent
        simulator: simulator
        camera: Camera {
            id: camera
        }
        backgroundColor: "black"

        TrackballNavigator {
            id: navigator
            anchors.fill: parent
            camera: camera
        }
    }
}

