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
            root.height = 500
            root.width = 300
            var resident = MyModel.model().getResidentByEmail(email);
            if ( ! resident )
            {
                messageBox.show("No such user")
                return;
            }
            if ( ! resident.matchesPassword(password) )
            {
                messageBox.show("Wrong password")
                return;
            }

            loader.setSource("ListView.qml")
            MyModel.setViewingResident(resident);
        }
        onLoggedOut:
        {
            root.width = 300
            root.height = 400
            loader.setSource("LoginForm.qml")
        }
    }

    Rectangle
    {
        id: messageBox
        width: parent.width
        height: parent.height
        x: 0
        y: -height

        color: "red";

        property alias message: label.text


        function hide()
        {
            messageBox.y = -height
        }

        function show(m)
        {
            messageBox.y = 0;
            message = m;
        }

        Text
        {
            id: label;
            color : "yellow"
            anchors.centerIn: parent;
        }

        Rectangle
        {
            width: 0.8*parent.width
            height: 20;
            color : "silver"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            MouseArea
            {
                anchors.fill: parent;
                onClicked:
                {
                    messageBox.hide();
                }
            }
        }
    }


}
