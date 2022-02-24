import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

ListView {
    id: root
    delegate: Loader {
        Component.onCompleted: {
            console.log("Delegate ", index)
            if (modelData.type === ButtonViewModel.COMMON)
            {
                console.log("ButtonViewModel.COMMON")
                sourceComponent = commonButton
            }
            else if (modelData.type === ButtonViewModel.CHECKEABLE)
            {
                console.log("ButtonViewModel.CHECKEABLE")
                sourceComponent = checkeableButton

            }
            else if (modelData.type === ButtonViewModel.SWITCH)
            {
                console.log("ButtonViewModel.SWITCH")
                sourceComponent = switchButton
            }
            console.log("sourceComponent: ", sourceComponent)
            item.buttonViewModel = modelData
        }
    }

    Component {
        id: commonButton
        CommonButtonView {

        }
    }

    Component {
        id: checkeableButton
        CommonButtonView {
            checkable: true
        }
    }

    Component {
        id: switchButton
        SwitchButtonView {

        }
    }
}
