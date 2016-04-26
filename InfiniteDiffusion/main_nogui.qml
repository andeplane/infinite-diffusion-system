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
    }

    DiffusionVisualizer {
        id: visualizer
        anchors.fill: parent
        simulator: simulator
        spheresScale: scaleSlider.value
        alpha: alphaSlider.value
        spheresVisible: spheresVisible.checked
        octreeVisible: octreeVisible.checked
        pointsVisible: pointsVisible.checked
        pointsScale: pointsSlider.value
    }

    Column {
        Row {
            Label {
                text: "Alpha: "
                color: "white"
            }
            CheckBox {
                id: octreeVisible
                checked: visualizer.octreeVisible
            }
            Slider {
                id: alphaSlider
                value: 0.15
                minimumValue: 0
                maximumValue: 0.15
            }
        }
        Row {
            Label {
                text: "Spheres: "
                color: "white"
            }
            CheckBox {
                id: spheresVisible
                checked: visualizer.spheresVisible
            }
            Slider {
                id: scaleSlider
                value: visualizer.spheresScale
                minimumValue: 0.5
                maximumValue: 5.0
            }
        }
        Row {
            Label {
                text: "Points: "
                color: "white"
            }
            CheckBox {
                id: pointsVisible
                checked: visualizer.pointsVisible
            }
            Slider {
                id: pointsSlider
                value: visualizer.pointsScale
                minimumValue: 0.1
                maximumValue: 10.0
            }
        }
    }

}
