import QtQuick 2.0

Item {

    id: root;

    property alias text: text.text
    signal clicked
    height: 20

    Text
    {
        id: text
        anchors.centerIn: parent;
        anchors.fill: parent
        color: "blue"
        font.underline: true;

        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                root.clicked()
            }

        }


    }


}

