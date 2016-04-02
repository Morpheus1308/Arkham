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
            }
            loader.setSource("ListView.qml")
            MyModel.setViewingResident(resident);
        }
        onLoggedOut:
        {
            loader.setSource("LoginForm.qml")
        }
    }


    MessageBox
    {
        id: messageBox;
    }


    Component.onCompleted:
    {
        MyModel.setViewingResident(MyModel.model().getResidentByEmail("a@a.a"));
    }
}
