import QtQuick 2.5

Rectangle
{
    id: root
    width: parent.width - 2*margin
    height: parent.height -2*margin
    x: margin
    y: -height
    opacity: 0.98

    property int margin : 10;

    color: "#444444";


    function hide()
    {
        state = "hidden"
    }

    function show(title, message)
    {
        state = "visible"
        messageBody.text = message;
        headline.text = title;
    }


    Column
    {

        x:0
        y: 40
        width:  parent.width
        spacing: 10
        Text
        {
            id: headline;
            color : "white"
            font.bold: true;
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.Wrap
            font.pixelSize: messageBody.font.pixelSize*2
        }

        Text
        {
            id: messageBody;
            color : "white"
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.Wrap
            width: parent.width*0.8

        }

    }
    Button
    {
        width: 0.8*parent.width
        label: "Whatever..."
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom:  parent.bottom
        anchors.margins: root.margin*2
        onClicked: root.hide();
    }
    transitions: Transition {
        PropertyAnimation { properties: "y, opacity"; easing.type: Easing.InOutQuad ; }
    }

    states :
        [
        State {
            name: "hidden"
            PropertyChanges { target: root; y:-height }
            PropertyChanges { target: root; opacity: 0 }
        },
        State {
            name: "visible"
            PropertyChanges { target: root; y: margin }
            PropertyChanges { target: root; opacity: 0.98 }
        }

    ]
}
