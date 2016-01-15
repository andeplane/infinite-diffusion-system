import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QMLPlot 1.0

Window {
    visible: true
    width: 1024
    height: 768
    MySimulator {
        id: simulator
        system: System {
            Component.onCompleted: {
                createParticles(100000,-100,100)
            }

            properties: SystemProperties {
                geometry: CylinderGeometry { radius: 100.0 }
                // geometry: PerlinGeometry { }
                //geometry: VoidGeometry { }
                stepLength: 10.0
            }
        }

        lineGraphDataSource: LineGraphDataSource {

        }
    }

    Visualizer {
        anchors.fill: parent
        simulator: simulator
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
    }
    Figure {
        id: figure
        width: 400
        height: 400
        //color: "red"
        color: Qt.rgba(0.76, 0.66, 0.57, 0.85)
        fitData: true
        xLabel: "r^2(t)"
        yLabel: "#"
        title: ""
        LineGraph {
            id: graph
            dataSource: simulator.lineGraphDataSource
            width: 1
        }
        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }

        Row {
            x: 6
            y: 5
            spacing: 10
            Label {
                text: "Diffusion mean: "+simulator.diffusionMean.toFixed(3)
            }
            Label {
                text: "Time: "+simulator.time
            }
        }
        Row {
            x: 6
            y: 20
            spacing: 10
            Label {
                text: "Diffusion sigma: "+simulator.diffusionStandardDeviation.toFixed(3)
            }
            Label {
                text: "Time per timestep [ms]: "+simulator.timePerTimestep.toFixed(3)
            }

        }

    }
}

