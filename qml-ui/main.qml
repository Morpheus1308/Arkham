import QtQuick 2.5
import QtQuick.Window 2.2
import dk.winkler.morten.Arkham 1.0

Window {

    id: root
    visible: true
    height: 400
    width: 300

    Loader
    {
        id: loader
        anchors.fill: parent;
        source: "LoginForm.qml"
    }

    Connections {
        target: loader.item
        onTestCredentials:
        {
            var success = true;
            var resident = MyModel.model().getResidentByEmail(email);
            if ( ! resident )
            {
                success = false;
            }
            if ( success && ! resident.matchesPassword(password) )
            {
                success = false;
            }
            if( ! success )
            {
                messageBox.show("Could not login", "Your email and password could not be matched.")
                return;
            }            loader.setSource("ListView.qml")
            MyModel.setViewingResident(resident);
        }
        onLoggedOut:
        {
            loader.setSource("LoginForm.qml")
        }
    }

    Rectangle
    {
        id: messageBox
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
            anchors.margins: messageBox.margin*2
            onClicked: messageBox.hide();
        }
        transitions: Transition {
            PropertyAnimation { properties: "y, opacity"; easing.type: Easing.InOutQuad ; }
        }

        states :
            [
            State {
                name: "hidden"
                PropertyChanges { target: messageBox; y:-height }
                PropertyChanges { target: messageBox; opacity: 0 }
            },
            State {
                name: "visible"
                PropertyChanges { target: messageBox; y: margin }
                PropertyChanges { target: messageBox; opacity: 0.98 }
            }

        ]
    }


}
