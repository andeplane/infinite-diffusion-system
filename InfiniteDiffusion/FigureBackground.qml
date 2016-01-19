import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QMLPlot 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Rectangle {
    id: figureBackground
    property LineGraph loaded: loaded
    property LineGraph graph: graph
    property Figure figure: figure
    property real fullHeight: 420
    width: 400
    height: fullHeight
    color: Qt.rgba(0.76, 0.66, 0.57, 0.85)
    anchors.left: parent.left
    anchors.top: parent.top
    
    Figure {
        id: figure
        width: parent.width
        height: parent.height-20
        visible: figureBackground.height===figureBackground.fullHeight
        fitData: true
        fitExact: false
        // fitY: true
        yMin: 0
        yMax: 0.05
        xMin: 0
        xMax: 100
        color: Qt.rgba(0.0, 0.0, 0.0, 0.0)
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
            dataSource: statisticDiffusion.dataSource
            width: 1
        }
    }
    
    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 25
        anchors.topMargin: 3
        spacing: 2
        Row {
            spacing: 10
            Label {
                text: "Diffusion mean: "+statisticDiffusion.mean.toFixed(3)
            }
            Label {
                text: "Time: "+simulator.time
            }
        }
        Row {
            spacing: 10
            Label {
                text: "Diffusion sigma: "+statisticDiffusion.standardDeviation.toFixed(3)
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
            visible: figureBackground.height===figureBackground.fullHeight
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
            visible: figureBackground.height===figureBackground.fullHeight
            onClicked: {
                fileDialog.mode = "saveSVG"
                fileDialog.selectExisting = false
                fileDialog.open()
            }
        }
        Button {
            text: "Save PNG"
            visible: figureBackground.height===figureBackground.fullHeight
            onClicked: {
                fileDialog.mode = "savePNG"
                fileDialog.selectExisting = false
                fileDialog.open()
            }
        }
        Button {
            text: "Load"
            visible: figureBackground.height===figureBackground.fullHeight
            onClicked: {
                fileDialog.mode = "load"
                fileDialog.selectExisting = true
                fileDialog.open()
            }
        }
        Button {
            text: "Save"
            visible: figureBackground.height===figureBackground.fullHeight
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
                figureBackground.height = 40
            } else {
                text = "-"
                figureBackground.height = figureBackground.fullHeight
            }
        }
    }
}
