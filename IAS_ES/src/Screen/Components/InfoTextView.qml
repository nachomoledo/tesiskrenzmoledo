import QtQuick 2.11
import QtQuick.Controls 2.2
import ViewModels 1.0

Text {
    id: root
    property InfoTextViewModel infoTextViewModel
    text: infoTextViewModel ? (infoTextViewModel.title + ": " + infoTextViewModel.value) : ""
    wrapMode: Text.WordWrap
}
