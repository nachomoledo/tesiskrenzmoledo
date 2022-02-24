import ViewModels 1.0

import "../Screen/Components"

import QtQuick 2.9
import QtQuick.Controls 2.2
//import QtQuick.Layouts 1.12

Rectangle {
    id: root
    property MainScreenViewModel mainScreenViewModel: exposedViewModels.mainScreenViewModel
    readonly property int columnsWidth: exposedViewModels.screenProperties.buttonWidth
    readonly property int catalogWidth: width - 2*columnsWidth - 4*borderMargin
    readonly property int borderMargin: 20

    GridView {
        id: portList
        readonly property int verticalSpacing: 12
        readonly property int horizontalSpacing: 18
        flow: GridView.FlowTopToBottom
        width: root.columnsWidth
        height: model ? (model.length/2)*(cellHeight) : 0 //parent.height-root.borderMargin-imageView.y
        anchors.top: parent.top
        anchors.topMargin: root.borderMargin// + (count <= 2) ? (65) : 0
        anchors.left: parent.left
        anchors.leftMargin: root.borderMargin// + (count <= 2) ? (90) : 0
        model: exposedViewModels.mainScreenViewModel.textFieldList
        cellWidth: exposedViewModels.screenProperties.buttonWidth/2
        cellHeight: exposedViewModels.screenProperties.buttonHeight+verticalSpacing
        delegate: PortSelectorView {
            width: portList.cellWidth-portList.horizontalSpacing
            height: portList.cellHeight-portList.verticalSpacing
            textFieldViewModel: modelData
        }
    }

    Rectangle {
        id: imageView
        width: root.columnsWidth
        height: root.columnsWidth
        border.width: 1
        anchors.top: portList.bottom
        anchors.topMargin: root.borderMargin-8
        //anchors.topMargin: (parent.height-height-portList.height-infoTexts.height-2*root.borderMargin)/2
        //anchors.top: parent.top
//        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: root.borderMargin
        Text {
            id: name
            visible: "" == image.source
            text: qsTr("Please select a downloaded sample to preview")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            anchors.fill: parent
        }
        Image {
            id: image
            property int espacioHorizontal: (width-paintedWidth)/2
            property int espacioVertical: (height-paintedHeight)/2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height-2*parent.border.width
            width: parent.width-2*parent.border.width
            source: exposedViewModels.imageToShow //"file:/home/tesis/Repos/TESIS_V2/res/image.jpg"//
            fillMode: Image.PreserveAspectFit
            MouseArea {
                id: mouseArea
                hoverEnabled :true
                anchors.verticalCenter: image.verticalCenter
                anchors.horizontalCenter: image.horizontalCenter
                width: image.paintedWidth
                height: image.paintedHeight
                onMouseXChanged: {
                    zoomRectangle.x = Math.round(image.espacioHorizontal + ((mouseArea.mouseX-zoomRectangle.width/2 < 0) ? 0 : (mouseArea.mouseX+zoomRectangle.width/2 < parent.paintedWidth) ? mouseArea.mouseX-zoomRectangle.width/2 : (parent.paintedWidth-zoomRectangle.width)))
                }
                onMouseYChanged: {
                    zoomRectangle.y = Math.round(image.espacioVertical + ((mouseArea.mouseY-zoomRectangle.height/2 < 0) ? 0 : (mouseArea.mouseY+zoomRectangle.height/2 < parent.paintedHeight) ? mouseArea.mouseY-zoomRectangle.height/2 : (parent.paintedHeight-zoomRectangle.height)))
                }
                onEntered: {
                    zoomRectangle.visible = true
                }
                onExited: {
                    zoomRectangle.visible = false
                }
            }
            Rectangle {
                id: zoomRectangle
                visible: false
                height: parent.height/5
                width: parent.width/5
                border.width: 1
                border.color: "black"
                color: "#80808080"
            }
        }
    }

    ListView {
        id: infoTexts
        readonly property int delegateHeight: 30
        spacing: 0
        anchors.top: imageView.bottom
        anchors.topMargin: root.borderMargin
        anchors.left: parent.left
        anchors.leftMargin: root.borderMargin
        height: model ? model.length*(spacing + delegateHeight) : 0
        width: root.columnsWidth
        model: exposedViewModels.mainScreenViewModel.infoTextList
        delegate: InfoTextView {
            infoTextViewModel: modelData
            height: infoTexts.delegateHeight
            width: parent.width
        }
    }

    Rectangle {
        id: catalog
        property int childWidth: width - 2*border.width
        color: "transparent"
        border.color: "black"
        border.width: 3
        anchors.top: parent.top
        anchors.topMargin: root.borderMargin
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.catalogWidth
        height: parent.height - 2*anchors.topMargin


        FileView {
            id: titleFile
            width: parent.childWidth
            anchors.top: parent.top
            anchors.topMargin: parent.border.width
    //        anchors.left: portList.right
            anchors.horizontalCenter: parent.horizontalCenter
            column1Text: "ID"
            column2Text: "Size"
            column3Text: "Width"
            column4Text: "Height"
            column5Text: "Date Created"
            fontBold: true
            fontPixelSize: 20
            borderColor: "black"
        }

        ListView
        {
            anchors.top: titleFile.bottom
    //        anchors.left: portList.right
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.childWidth
            height: parent.height - titleFile.height - 2*parent.border.width
            ScrollBar.vertical: ScrollBar {}
            boundsBehavior: Flickable.StopAtBounds
            model: exposedViewModels.mainScreenViewModel.catalogModel
            clip: true
            delegate: FileView {
                property ImagePropertiesViewModel imagePropertiesViewModel: modelData
                column1Text: imagePropertiesViewModel.imagePropertyList[0]
                column2Text: imagePropertiesViewModel.imagePropertyList[1]
                column3Text: imagePropertiesViewModel.imagePropertyList[2]
                column4Text: imagePropertiesViewModel.imagePropertyList[3]
                column5Text: imagePropertiesViewModel.imagePropertyList[4]
                width: parent.width
                checkable: true
                onCheckedChanged: {
                    if (checked)
                    {

                    }
                    else
                    {

                    }
                }
            }
        }
    }

    ButtonColumn {
        spacing: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: root.borderMargin
        height: (model) ? model.length * (spacing+exposedViewModels.screenProperties.buttonHeight) : 0
        width: exposedViewModels.screenProperties.buttonWidth
        model: exposedViewModels.mainScreenViewModel.buttonList
    }

    Rectangle {
        height: 600
        width: 600
        anchors.centerIn: parent
        border.width: 1
        color: "blue"
        property bool condicionX: ((zoomRectangle.x+zoomRectangle.width >= (image.width-image.paintedWidth)/2) && image.espacioHorizontal+image.paintedWidth >= zoomRectangle.x)
        property bool condicionY: ((zoomRectangle.y+zoomRectangle.height >= (image.height-image.paintedHeight)/2) && image.espacioVertical+image.paintedHeight >= zoomRectangle.y)
        visible: (image.source != "") && zoomRectangle.visible && (condicionX) && (condicionY)
        Image {
            id: imgZoom
            property int originalWidth: 0
            property int originalHeight: 0
            property int pixelsToShow: 0

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: (parent.width-2*parent.border.width)
            height: (parent.height-2*parent.border.width)
            source: image.source
            fillMode: Image.PreserveAspectCrop
            function recalcularArea()
            {
                var normalizedZoomRectX = (zoomRectangle.x > image.espacioHorizontal) ? (zoomRectangle.x - image.espacioHorizontal) : 0
                var x = imgZoom.originalWidth*normalizedZoomRectX/image.paintedWidth
                var normalizedZoomRectY = (zoomRectangle.y > image.espacioVertical) ? (zoomRectangle.y - image.espacioVertical) : 0
                var y = imgZoom.originalHeight*normalizedZoomRectY/image.paintedHeight
                imgZoom.sourceClipRect = Qt.rect(x, y, imgZoom.pixelsToShow, imgZoom.pixelsToShow)
            }
            Connections {
                target: zoomRectangle
                function onXChanged() {
                    imgZoom.recalcularArea()

                }
                function onYChanged() {
                    imgZoom.recalcularArea()
                }

            }
            Connections {
                target: image
                function onSourceChanged() {
                    imgZoom.originalWidth = imgZoom.sourceSize.width
                    imgZoom.originalHeight = imgZoom.sourceSize.height
                    imgZoom.pixelsToShow = imgZoom.sourceSize.width*zoomRectangle.width/image.paintedWidth
                    console.log("onSourceChanged() -> originalWidth = ", imgZoom.originalWidth, " horiginalHeight = ", imgZoom.originalHeight, ", pixelsToShow = ", imgZoom.pixelsToShow, ", zoomRectangle.width = ", zoomRectangle.width, ", image.paintedWidth = ", image.paintedWidth)
                }
            }
            Component.onCompleted: {
                originalWidth = sourceSize.width
                originalHeight = sourceSize.height
                pixelsToShow = sourceSize.width*zoomRectangle.width/image.paintedWidth
            }

        }
    }

    Column {
        id: ledButtonsColumn
        spacing: 9
        anchors.top: infoTexts.bottom
        anchors.left: parent.left
        anchors.leftMargin: root.borderMargin
        CommonButtonView {
            buttonViewModel: exposedViewModels.setLedOBCButton

        }
        Text {
            id: obcLedStatus
            text: "OBC Led Status: " + ((exposedViewModels.obcLedStatus === true) ? "ON" : "OFF")
            width: exposedViewModels.screenProperties.buttonWidth/2

        }
        CommonButtonView {
            buttonViewModel: exposedViewModels.setLedIASButton
        }
        Text {
            id: iasLedStatus
            text: "IAS Led Status: " + ((exposedViewModels.iasLedStatus === true) ? "ON" : "OFF")
            width: exposedViewModels.screenProperties.buttonWidth/2
        }
    }
}

