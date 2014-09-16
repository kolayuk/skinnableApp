// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 640
    // simple image contains skin background
    Image{
        //size of image component
        width: 360
        height: 640
        // size of skin element to request
        // dont forget to change it when u change image's size
        sourceSize.width: 360
        sourceSize.height: 640
        // image://skin - means we request skin element
        // 10005A26 - Major skin element id (IDLE background)
        // 1001 - minor skin element id (IDLE background)
        // ask theme/skin maker for more IDs
        source: "image://skin/10005A26/1001"
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
