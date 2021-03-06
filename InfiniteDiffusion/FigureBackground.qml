import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import SimVis 1.0
import MySimulator 1.0
import Diffusion 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import DataSource 1.0

Rectangle {
    id: figureBackground
    property LineGraph loaded: loaded
    property LineGraph graph: graph
    property Figure figure: figure
    property real fullHeight: 420
    width: 400
    height: fullHeight
    anchors.left: parent.left
    anchors.top: parent.top
    color: Qt.rgba(1.0, 1.0, 1.0, 0.85)

    Figure {
        id: figure
        width: parent.width
        height: parent.height-20
        visible: figureBackground.height===figureBackground.fullHeight
        lineGraphs: [graph]
        LineGraph {
            id: loaded
            figure: figure
            color: "red"
            dataSource: DataSource {
                
            }
            onDataSourceChanged: {
                dataSource.updated.connect(function() {
                    figure.updateLimits()
                })
            }
        }
        LineGraph {
            id: graph
            figure: figure
            dataSource: statisticMSD.dataSource
            onDataSourceChanged: {
                dataSource.updated.connect(function() {
                    if(figure != undefined) {
                        figure.updateLimits()
                    }
                })
            }
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
                text: "Time: "+simulator.time
            }
        }
        Row {
            spacing: 10
            Label {
                text: "Time per timestep [ms]: "+simulator.timePerTimestep.toFixed(3)
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
