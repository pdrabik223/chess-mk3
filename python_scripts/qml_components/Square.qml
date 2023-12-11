import QtQuick
Item {
    id:square
    width: 80
    height: 80
    property alias squareColor: rectangle.color

        Rectangle {
            id: rectangle
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: container.clicked(container.id)
        }
    }