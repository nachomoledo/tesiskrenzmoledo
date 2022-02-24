import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "Screen"

ApplicationWindow {
    id: root
    readonly property int contentHorizontalMargin: 20
    readonly property int contentVerticalMargin: 20
    visible: true
    width: exposedViewModels.screenProperties.width
    height: exposedViewModels.screenProperties.height
    minimumHeight: exposedViewModels.screenProperties.height
    minimumWidth: exposedViewModels.screenProperties.width
    title: "μ-Sat 3 IAS Simulation"
    background: Rectangle {
        color: "lightblue"
        width: root.width
        height: root.height
    }
    MainScreen {
        width: root.width - 2*contentHorizontalMargin
        height: root.height - 2*contentVerticalMargin
        anchors.centerIn: parent
    }

//    Item {
//        id: item
//        anchors.fill: parent

//        Column {
//            anchors.centerIn: parent
//            Button {
//                id: button
//                anchors.horizontalCenter: parent.horizontalCenter
//                text: "pedirLenna"
//                font.pixelSize: 24
//                onClicked: {
//                    imageManager.sendImageCommandReqMessage(1)
//                }
//                background: Rectangle {
//                    implicitHeight: 100
//                    implicitWidth: 200
//                    color: button.pressed ? "blue" : "red"
//                }
//            }
//            Button {
//                id: button2
//                anchors.horizontalCenter: parent.horizontalCenter
//                text: "pedirCatalogo"
//                font.pixelSize: 24
//                onClicked: {
//                    imageManager.sendCatalogCommandReqMessage()
//                }
//                background: Rectangle {
//                    implicitHeight: 100
//                    implicitWidth: 200
//                    color: button.pressed ? "blue" : "red"
//                }
//            }

//            Button {
//                id: button3
//                anchors.horizontalCenter: parent.horizontalCenter
//                text: "recortarCa01"
//                font.pixelSize: 24
//                onClicked: {
//                    imageManager.selectROI(1)
//                }
//                background: Rectangle {
//                    implicitHeight: 100
//                    implicitWidth: 200
//                    color: button.pressed ? "blue" : "red"
//                }

//            }
//        }


//        Button {
//            id: button3
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.top: button2.bottom
//            text: "borrar borrar.jpg"
//            font.pixelSize: 24
//            onClicked: {
//                imageManager.sendDeleteReqMessage(5)
//            }
//            background: Rectangle {
//                implicitHeight: 100
//                implicitWidth: 200
//                color: button.pressed ? "blue" : "red"
//            }

//        }
//    }
}
