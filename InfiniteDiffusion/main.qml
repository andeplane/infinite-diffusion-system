import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import GeometryLibrary 1.0

Window {
    visible: true
    width: 1024
    height: 768

    RegularNoiseModel {
        id: regularNoiseModel
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
                stepLength: parseFloat(stepLength.text)
                posMin: parseFloat(posMin.text)
                posMax: parseFloat(posMax.text)
                numberOfParticles: parseInt(numberOfParticles.text)
            }
            statistics: [
                statisticDiffusion
            ]
        }
    }

    DiffusionVisualizer {
        anchors.fill: parent
        simulator: simulator
    }

    FigureBackground {
        id: figureBackground
        radius: 10
    }

    Rectangle {
        id: controller
        width: 400
        height: settingsColumn.height
        color: Qt.rgba(0.76, 0.66, 0.57, 0.85)
        anchors.right: parent.right
        anchors.top: parent.top
        radius: 10

        Column {
            id: settingsColumn
            spacing: 10
            Label {
                text: "Simulation settings"
            }

            Row {
                Label {
                    text: "Model: "
                }

                ComboBox {
                    currentIndex: 0
                    model: ListModel {
                        id: cbItems
                        ListElement { text: "Regular noise";}
                        ListElement { text: "Multifractal noise";}
                        ListElement { text: "Void";}
                    }
                    width: 200
                    onCurrentIndexChanged: {
                        if(cbItems.get(currentIndex).text === "Regular noise") {
                            systemProperties.model = regularNoiseModel
                        }
                    }
                }
            }

            ParametersGUI {
                id: paramGUI
                color: "white"
                radius: 10
                textColor: "black"
                labelWidth: 100
                parameters: systemProperties.model ? systemProperties.model.parameters : undefined
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
                    Row {
                        spacing: 5
                        Label {
                            text: "Step length: "
                        }

                        TextField {
                            id: stepLength
                            text: "1.0"
                        }
                    }
                }
            }

            Button {
                text: "Run"
                onClicked: {
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
            //            if(mode === "load") {
            //                figureBackground.loaded.load(fileDialog.fileUrls)
            //            } else if (mode === "save") {
            //                figureBackground.graph.save(fileDialog.fileUrls)
            //            } else if (mode === "saveSVG") {
            //                figureBackground.figure.saveSVG(fileDialog.fileUrls)
            //            } else if (mode === "savePNG") {
            //                figureBackground.figure.savePNG(fileDialog.fileUrls)
            //            }
        }
    }
}

