import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: root
    visible: true
    height: 300
    width: 500

    Rectangle
    {
        anchors.centerIn: parent;
        color: "yellow"
        border.width: 1
        border.color: "black"
        width: 400
        height: 200
        ListView
        {
            id: view;
            anchors.fill: parent
            model: MyModel

            delegate: Text {

                text: title + " " + name
            }

            Component.onCompleted:
            {
                console.log(model);
            }
        }

    }

}
