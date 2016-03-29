import QtQuick 2.0

BorderImage {
    id: root;

    property alias label: textLabel.text;
    property bool password: false

    signal clicked

    height: 40
    source: "borderimage.png"
    border.left: 20; border.top: 20
    border.right: 20; border.bottom: 20

    Text
    {
        id: textLabel
        anchors.centerIn: parent
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: root.clicked()
    }



}
