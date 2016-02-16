import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Window {
    visible: true
    width: 1024
    height: 768
    CylinderGeometry {
        id: cylinderGeometry
        radius: parseFloat(cylinderRadius.text)
    }
    PerlinGeometry {
        id: perlinGeometry
    }
    VoidGeometry {
        id: voidGeometry
    }

    StatisticDiffusionDistribution {
        id: statisticDiffusion
        timeBetweenSampling: 100
        histogramBins: 500
        timeBetweenComputing: 200
    }

    MySimulator {
        id: simulator
        system: System {
            id: system
            properties: SystemProperties {
                id: systemProperties
                stepLength: 10.0
                posMin: parseFloat(posMin.text)
                posMax: parseFloat(posMax.text)
                numberOfParticles: parseInt(numberOfParticles.text)
            }
            statistics: [
                statisticDiffusion
            ]
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

    FigureBackground {
        id: figureBackground
    }

    Rectangle {
        id: controller
        property real fullHeight: 420
        width: 400
        height: fullHeight
        color: Qt.rgba(0.76, 0.66, 0.57, 0.85)
        anchors.right: parent.right
        anchors.top: parent.top
        Button {
            width: 20
            height: 20
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 2
            text: "-"
            onClicked: {
                if(text==="-") {
                    text = "+"
                    controller.height = 40
                } else {
                    text = "-"
                    controller.height = controller.fullHeight
                }
            }
        }
        Column {
            spacing: 10
            Label {
                text: "Simulation settings"
            }

            GroupBox {
                title: "Initial state"
                Column {
                    Row {
                        spacing: 5
                        Label {
                            text: "# particles: "
                        }

                        TextField {
                            id: numberOfParticles
                            text: "100000"
                        }
                    }
                    Row {
                        spacing: 5
                        Label {
                            text: "Min pos: "
                        }

                        TextField {
                            id: posMin
                            text: "-100"
                        }
                    }
                    Row {
                        spacing: 5
                        Label {
                            text: "Max pos: "
                        }

                        TextField {
                            id: posMax
                            text: "100"
                        }
                    }
                }
            }

            GroupBox {
                width: parent.width - 20
                title: "Geometry"
                visible: controller.height===controller.fullHeight
                ExclusiveGroup {
                    id: geometryGroup
                }

                Column {
                    Row {
                        RadioButton {
                            id: radGeometryVoid
                            text: "Void"
                            checked: true
                            exclusiveGroup: geometryGroup
                        }
                    }
                    Row {
                        RadioButton {
                            id: radGeometryCylinder
                            text: "Cylinder"
                            exclusiveGroup: geometryGroup
                        }
                        TextField {
                            id: cylinderRadius
                            text: "200"
                        }
                    }
                    Row {
                        RadioButton {
                            id: radGeometryPerlin
                            text: "Perlin"
                            exclusiveGroup: geometryGroup
                        }
                    }
                }
            }
            Button {
                text: "Run"
                onClicked: {
                    if(radGeometryVoid.checked) {
                        systemProperties.geometry = voidGeometry
                    } else if(radGeometryCylinder.checked) {
                        systemProperties.geometry = cylinderGeometry
                    } else if(radGeometryPerlin.checked) {
                        systemProperties.geometry = perlinGeometry
                    }

                    systemProperties.willReset = true
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
            if(mode === "load") {
                figureBackground.loaded.load(fileDialog.fileUrls)
            } else if (mode === "save") {
                figureBackground.graph.save(fileDialog.fileUrls)
            } else if (mode === "saveSVG") {
                figureBackground.figure.saveSVG(fileDialog.fileUrls)
            } else if (mode === "savePNG") {
                figureBackground.figure.savePNG(fileDialog.fileUrls)
            }
        }
    }
}

