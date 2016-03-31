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
                console.log("No such user")
                return;
            }
            if ( ! resident.matchesPassword(password) )
            {
                console.log("Wrong password")
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


}
