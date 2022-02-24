import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

Rectangle {
    id: root
    property ButtonViewModel buttonViewModel
    implicitWidth: exposedViewModels.screenProperties.buttonWidth
    implicitHeight: exposedViewModels.screenProperties.buttonHeight
    enabled: (buttonViewModel) ? buttonViewModel.enabled : false
    color: !root.enabled ? "lightgray" : (root.pressed || root.checked) ? "dimgray" : "gray"
    border.color: "black"
    border.width: 2
    radius: 5

    readonly property int textLeftMargin: 10
    Item {
        anchors.fill: parent
        Switch {
            id: control
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            checked: buttonViewModel.checked

            indicator: Rectangle {
                implicitWidth: 48
                implicitHeight: 26
                x: control.leftPadding
                y: parent.height / 2 - height / 2
                radius: 13
                color: control.checked ? "cornflowerblue" : "white"
                border.color: "black" //control.checked ? "#17a81a" : "#cccccc"

                Rectangle {
                    x: control.checked ? parent.width - width : 0
                    width: 26
                    height: 26
                    radius: 13
                    color: "white" //control.down ? "#cccccc" : "#ffffff"
                    border.color: "black" //control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
                }
            }
            onClicked: {
                if (buttonViewModel)
                {
                    if (checked)
                    {
                        buttonViewModel.checked = true
                    }
                    else
                    {
                        buttonViewModel.checked = false
                    }
                    buttonViewModel.clicked()
                    console.log("switch clicked!!")
                }
            }
        }

        Text {
            anchors.left: parent.left
            anchors.leftMargin: root.textLeftMargin
            verticalAlignment: Text.AlignVCenter
            text: (buttonViewModel) ? buttonViewModel.text : ""
            width: root.width - root.textLeftMargin
            height: root.height
            color: root.enabled ? "black" : "gray"
        }
    }
}
