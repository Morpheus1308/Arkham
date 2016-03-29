import QtQuick 2.5
import QtQuick.Window 2.2

Window {

    id: root
    visible: true
    height: 75
    width: 200

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
            root.width = 75
            root.height = 200
            loader.setSource("LoginForm.qml")
        }
    }

}
