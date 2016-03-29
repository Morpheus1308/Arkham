import QtQuick 2.5
import QtQuick.Window 2.2

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
        onLoggedIn:
        {
            root.height = 500
            root.width = 300
            loader.setSource("ListView.qml")
        }
        onLoggedOut:
        {
            root.width = 300
            root.height = 400
            loader.setSource("LoginForm.qml")
        }
    }


}
