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

    MySimulator {
        id: simulator
        octree: octreeModel
        system: System {
            id: system
            properties: SystemProperties {
                id: systemProperties
                stepLength: parseFloat(stepLength.text)
                posMin: parseFloat(posMin.text)
                posMax: parseFloat(posMax.text)
                periodic: periodic.checked
                mirrored: mirrored.checked
                numberOfParticles: parseInt(numberOfParticles.text)
                model: voidModel
            }
            statistics: [
                statisticMSD
            ]
        }
    }

    DiffusionVisualizer {
        id: visualizer
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

        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }

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
                    id: modelComboBox
                    currentIndex: 0
                    model: ListModel {
                        id: cbItems
                        ListElement { text: "Void";}
                        ListElement { text: "Regular noise";}
                        ListElement { text: "Cylinder";}
                        ListElement { text: "Static model from file";}
                    }
                    width: 200
                    onCurrentIndexChanged: {
                        if(modelComboBox.currentText === "Regular noise") {
                            systemProperties.model = regularNoiseModel
                        } else if(modelComboBox.currentText === "Static model from file") {
                            systemProperties.model = octreeModel
                        } else if(modelComboBox.currentText === "Cylinder") {
                            systemProperties.model = cylinderModel
                        } else if(modelComboBox.currentText === "Void") {
                            systemProperties.model = voidModel
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
                height: contentHeight + 30 + paramRect.height
                parameters: systemProperties.model ? systemProperties.model.parameters : undefined
                Row {
                    anchors.bottom: paramRect.top
                    Button {
                        id: paramLoad
                        property string previous
                        text: "Load"
                        onClicked: {
                            fileDialogOpen.mode = "parameters"
                            fileDialogOpen.open()
                        }
                    }
                    Button {
                        id: paramSave
                        text: "Save"
                        onClicked: {
                            fileDialogSave.mode = "parameters"
                            fileDialogSave.open()
                        }
                    }
                    Button {
                        id: paramLoadPrev

                        text: "Load previous"
                        onClicked: {
                            systemProperties.model.parameters.load(paramLoad.previous)
                        }
                    }
                }
                Rectangle {
                    id: paramRect
                    height: 50
                    anchors.bottom: parent.bottom
                    OctreeControl {
                        visible: (modelComboBox.currentText === "Static model from file")
                        model: octreeModel
                        width: paramGUI.width
                    }
                }
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
                        CheckBox {
                            id: periodic
                            text: "Periodic"
                            checked: systemProperties.periodic
                        }
                    }
                    Row {
                        spacing: 5
                        CheckBox {
                            id: mirrored
                            text: "Mirrored"
                            checked: systemProperties.mirrored
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

    FileDialog {
        id: fileDialogOpen

        property string mode
        title: "Please choose a file"

        onAccepted: {
            if (mode==="parameters") {
                paramLoad.previous = fileDialogOpen.fileUrls.toString()
                systemProperties.model.parameters.load(fileDialogOpen.fileUrls.toString())
            }
        }
    }

    FileDialog {
        id: fileDialogSave
        selectExisting : false
        property string mode
        title: "Please choose a location to save"

        onAccepted: {
            if(mode==="parameters") {
                systemProperties.model.parameters.save(fileDialogSave.fileUrls.toString())
            }
        }
    }

    CheckBox {
        text: "Octree visualizer"
        checked: visualizer.visualizeOctree
        onCheckedChanged: {
            visualizer.visualizeOctree = checked
        }
    }
    Slider {
        value: visualizer.alpha
        onValueChanged: visualizer.alpha = value
        minimumValue: 0
        maximumValue: 1
    }
}
