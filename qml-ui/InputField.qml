import QtQuick 2.5

BorderImage {
    id: root;

    property alias label: textLabel.text;
    property bool password: false
    property alias value: input.text

    height: 40
    source: "borderimage.png"
    border.left: 20; border.top: 20
    border.right: 20; border.bottom: 20

    Text
    {
        x: 15
        anchors.verticalCenter: parent.verticalCenter
        id: textLabel
        color: "white"
    }

    TextInput {
        id: input
        color: "white"
        anchors.top: textLabel.top
        x: textLabel.width+textLabel.x+12
        width: root.width-(40+textLabel.width)
        height: parent.height/2
        passwordCharacter: "\u2022"
        echoMode: root.password ? TextInput.Password : TextInput.Normal;
        passwordMaskDelay: 1000
        clip: true

    }


}
