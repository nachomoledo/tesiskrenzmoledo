import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

Button {
    id: root
    property ButtonViewModel buttonViewModel
    implicitWidth: exposedViewModels.screenProperties.buttonWidth
    implicitHeight: exposedViewModels.screenProperties.buttonHeight
    enabled: (buttonViewModel) ? buttonViewModel.enabled : false

    background: Rectangle {
        width: root.width
        height: root.height
        color: !root.enabled ? "lightgray" : (root.pressed || root.checked) ? "dimgray" : "gray"
        border.color: "black"
        border.width: 2
        radius: 5
    }
    contentItem: Text {
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: (buttonViewModel) ? buttonViewModel.text : ""
        width: root.width
        height: root.hight
        color: root.enabled ? "black" : "gray"
    }
    onClicked: {
        if (buttonViewModel)
        {
            buttonViewModel.clicked()
            console.log("button clicked!!")
        }
    }
}
