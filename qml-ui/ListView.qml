import QtQuick 2.0

Rectangle
{

    signal loggedOut()

    id: root
    anchors.fill: parent;
    color: "white"



    FoldableItem
    {


        id: list;
        anchors.fill: parent
        rotationAngle: 0
        signal loggedOut()


        Column
        {
            anchors.fill: parent

            Text
            {
                id: header
                text : "Residents"
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true;
                font.pixelSize: 30
            }

            ListView
            {
                width: root.width
                height: root.height - logoutButton.height - header.height
                model: MyModel
                clip: true
                spacing: 1

                delegate: Rectangle {
                    id: residentDelegate
                    property int residentSanity: sanity
                    property string residentName: name
                    property string residentTitle: title

                    Text{
                        anchors.centerIn: parent;
                        text: title + " " + name
                        font.pixelSize: 15
                    }

                    width: parent.width;
                    color: "#eeeeee"
                    height: 40
                    MouseArea {
                        anchors.fill: parent;
                        onClicked:
                        {
                            residentDetails.name = residentDelegate.residentName
                            residentDetails.title = residentDelegate.residentTitle
                            residentDetails.sanity = residentDelegate.residentSanity
                            list.hide()
                        }
                    }
                }

            }


            Button
            {
                anchors.horizontalCenter: parent.horizontalCenter

                id: logoutButton
                width : parent.width * 0.9
                label : "Log out"
                onClicked:
                {
                    root.loggedOut();
                }
            }
        }

    }


    Rectangle
    {

        id: residentDetails
        MouseArea
        {
            anchors.fill: parent;
        }

        width:parent.width
        height:parent.height
        y: 0
        x   : list.visibleWidth


        property Item container: root
        property alias name  : name.text
        property alias title  : title.text
        property alias sanity : sanity.text

        color: "#eeeeee"

        Grid
        {
            columns: 2
            Text { text:"Name" }
            Text { id: name }

            Text { text:"Title" }
            Text { id: title }

            Text { text:"Sanity" }
            Text { id: sanity }

            Text
            {
                text : "X"
                MouseArea
                {
                    anchors.fill: parent;
                    onClicked:
                    {
                        list.show()
                    }
                }
            }

        }

    }

}

