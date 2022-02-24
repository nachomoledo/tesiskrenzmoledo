import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

ListView {
    id: root
    readonly property int delegateWidth: width/model//width/(model.length)
    readonly property int numericDelegateoffset: 40
    property string column1Text
    property string column2Text
    property string column3Text
    property string column4Text
    property string column5Text
    property bool fontBold: false
    property int fontPixelSize: 18
    property bool checkable: false
    property color borderColor: "black"
    property alias checked: button.checked

    width: parent.width
    height: 50
    orientation: Qt.Horizontal
    model: 5
    delegate: Rectangle {
        implicitWidth: (index <= 3) ? root.delegateWidth-numericDelegateoffset : 4*root.numericDelegateoffset+root.delegateWidth
        implicitHeight: root.height
        border.width: 1
        border.color: root.borderColor
        color: button.checked ? "blue" : "white"
        Text {
            id: delegateText
            text: (index == 0) ? column1Text : (index == 1) ? column2Text : (index == 2) ? column3Text : (index == 3) ? column4Text : (index == 4) ? column5Text : ""
            anchors.centerIn: parent
            color: button.checked ? "white" : "black"
            font.pixelSize: root.fontPixelSize
            font.bold: root.fontBold
        }
//        Component.onCompleted: {console.log("index ", index, " text = ", delegateText.text)}
    }
    Button {
        id: button
        anchors.fill: parent
        enabled: root.checkable
        checkable: root.checkable
        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }
        onCheckedChanged: {
            if (checked)
            {
                console.log("id = ", column1Text, " checked!")
                exposedViewModels.selectImage(column1Text, true)
            }
            else
            {
                console.log("id = ", column1Text, " unchecked!")
                exposedViewModels.selectImage(column1Text, false)
            }
        }
    }
}
