import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import GeometryLibrary 1.0
import Qt.labs.settings 1.0

Row {
    property OctreeModel model
    Button {
        text: "Load XYZ"
        onClicked: {
            fileDialogOpen.mode = "loadxyz"
            fileDialogOpen.open()
        }
    }
    Button {
        text: "Save octree"
        onClicked: {
            fileDialogSave.open()
        }
    }
    Button {
        text: "Load octree"
        onClicked: {
            fileDialogOpen.mode = "loadoctree"
            fileDialogOpen.open()
        }
    }

    Settings {
        property alias lastFileDialogOpenFolder: fileDialogOpen.folder
        property alias lastFileDialogSaveFolder: fileDialogSave.folder
    }

    FileDialog {
        id: fileDialogOpen

        property string mode
        title: "Please choose a file"

        onAccepted: {
            if(mode==="loadxyz") {
                console.log("File chosen: "+fileDialogOpen.fileUrls.toString())
                model.setFile(fileDialogOpen.fileUrls.toString())
                model.readFile()
                // model.removeCylinder(0.25);
                model.buildTree(true);
            } else if(mode==="loadoctree") {
                model.loadOctree(fileDialogOpen.fileUrls.toString())
            }
        }
    }

    FileDialog {
        id: fileDialogSave
        selectExisting : false
        property string mode
        title: "Please choose a location to save"

        onAccepted: {
            model.saveOctree(fileDialogOpen.fileUrls.toString())
        }
    }
}
