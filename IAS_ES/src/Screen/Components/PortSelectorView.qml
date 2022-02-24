import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

Rectangle {
    id: root
    property TextFieldViewModel textFieldViewModel
    readonly property int margin: 10
    readonly property int textWidth: width/4
    readonly property int textFieldWidth: width-textWidth
    implicitWidth: exposedViewModels.screenProperties.buttonWidth
    implicitHeight: exposedViewModels.screenProperties.buttonHeight
    color: "transparent"
    Text {
        text: (textFieldViewModel) ? textFieldViewModel.title : ""
//        anchors.left: parent.left
//        anchors.leftMargin: root.margin
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        width: root.textWidth - root.margin
        height: root.height
    }
    TextField {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        placeholderText: (textFieldViewModel) ? textFieldViewModel.placeholderText : ""
        width: root.textFieldWidth
        height: root.height
        onAccepted: {
            if (textFieldViewModel)
            {
                textFieldViewModel.setText(text)
            }
        }
    }


}
