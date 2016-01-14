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
        system: System {
            Component.onCompleted: {
                createParticles(10000,-100,100)
            }

            properties: SystemProperties {
                geometry: CylinderGeometry {
                    radius: 100.0
                }
                stepLength: 1.0
            }
        }
    }

    Visualizer {
        anchors.fill: parent
        simulator: simulator
        camera: Camera {
            id: camera
            position: Qt.vector3d(0,0,-500)
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
    }
}

