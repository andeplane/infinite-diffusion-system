import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QMLPlot 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Window {
    visible: true
    width: 1024
    height: 768
    MySimulator {
        id: simulator
        system: System {
            Component.onCompleted: {
                createParticles(250000,-1000,1000)
            }

            properties: SystemProperties {
                //geometry: CylinderGeometry { radius: 100.0 }
                geometry: PerlinGeometry { }
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
        xLabel: "D"
        yLabel: "P(D)"
        title: ""
        LineGraph {
            id: loaded
            color: "red"
            dataSource: LineGraphDataSource {

            }

            width: 1
        }
        LineGraph {
            id: graph
            dataSource: simulator.lineGraphDataSource
            visible: true
            width: 1
        }

        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }

        Column {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 30
            spacing: 2
            Row {
                spacing: 10
                Label {
                    text: "Diffusion mean: "+simulator.diffusionMean.toFixed(3)
                }
                Label {
                    text: "Time: "+simulator.time
                }
            }
            Row {
                spacing: 10
                Label {
                    text: "Diffusion sigma: "+simulator.diffusionStandardDeviation.toFixed(3)
                }
                Label {
                    text: "Time per timestep [ms]: "+simulator.timePerTimestep.toFixed(3)
                }
            }
        }

        Row {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            Button {
                text: "Freeze"
                visible: figure.height===400
                onClicked: {
                    figure.freeze = !figure.freeze
                    if(figure.freeze) {
                        text = "Unfreeze"
                    } else {
                        text = "Freeze"
                    }
                }
            }
            Button {
                text: "Save SVG"
                visible: figure.height===400
                onClicked: {
                    fileDialog.mode = "saveSVG"
                    fileDialog.selectExisting = false
                    fileDialog.open()
                }
            }
            Button {
                text: "Save PNG"
                visible: figure.height===400
                onClicked: {
                    fileDialog.mode = "savePNG"
                    fileDialog.selectExisting = false
                    fileDialog.open()
                }
            }
            Button {
                text: "Load"
                visible: figure.height===400
                onClicked: {
                    fileDialog.mode = "load"
                    fileDialog.selectExisting = true
                    fileDialog.open()
                }
            }
            Button {
                text: "Save"
                visible: figure.height===400
                onClicked: {
                    fileDialog.mode = "save"
                    fileDialog.selectExisting = false
                    fileDialog.open()
                }
            }
        }
        Button {
            width: 20
            height: 20
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 2
            text: "-"
            onClicked: {
                if(text==="-") {
                    text = "+"
                    figure.height = 40
                } else {
                    text = "-"
                    figure.height = 400
                }
            }
        }
    }

    Settings {
        property alias lastOpenedFolder: fileDialog.folder
    }

    FileDialog {
        id: fileDialog
        property string mode
        title: "Please choose a file"
        selectMultiple: false
        selectFolder: false
        onAccepted: {
            folder = fileDialog.fileUrls[0]
            if(mode === "load") {
                loaded.load(fileDialog.fileUrls)
            } else if (mode === "save") {
                graph.save(fileDialog.fileUrls)
            } else if (mode === "saveSVG") {
                figure.saveSVG(fileDialog.fileUrls)
            } else if (mode === "savePNG") {
                figure.savePNG(fileDialog.fileUrls)
            }
        }
    }
}

