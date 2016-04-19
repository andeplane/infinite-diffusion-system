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
    }

    Slider {
        value: visualizer.alpha
        onValueChanged: visualizer.alpha = value
        minimumValue: 0
        maximumValue: 1
    }
}
