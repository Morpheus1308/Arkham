import QtQuick 2.0

Rectangle {

    id: root;
    anchors.fill: parent;

    signal loggedIn()

    color: "khaki"


    Text{
        text: "Click....."
        anchors.centerIn: parent
        font.pixelSize : 30
        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                root.loggedIn()
            }
        }
    }

}

