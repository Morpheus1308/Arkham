import QtQuick 2.0

Rectangle
{
    id: root
    anchors.fill: parent;
    color: "yellow"

    signal loggedOut()
    ListView
    {
        id: view;
        anchors.fill: parent
        model: MyModel
        clip: true

        delegate: Text {
            id: residentDelegate
            property int ssanity: sanity
            property string nname: name
            property string ttitle: title

            text: title + " " + name
            MouseArea {
                anchors.fill: parent;
                onClicked:
                {
                    var point = mapToItem(root, mouseX, mouseY)
                    var x = point.x
                    var y = point.y

                    residentDetails.name = residentDelegate.nname
                    residentDetails.title = residentDelegate.ttitle
                    residentDetails.sanity = residentDelegate.ssanity
                    residentDetails.show(x,y)

                }
            }
        }

    }

    Text
    {
        x: 0
        y: 300
        text : "Log out"
        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                root.loggedOut();
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

        width:0
        height:0
        x: 0
        y: 0

        opacity: 0

        property Item container: root
        property alias name  : name.text
        property alias title  : title.text
        property alias sanity : sanity.text

        anchors.fill: parent;

        property int originX
        property int originY


        enabled: false;
        function show(x,y)
        {
            opacity = 1
            enabled = true;

        }

        function hide()
        {
            opacity = 0
            enabled = false;
        }

        color:  "silver"

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
                        residentDetails.hide();
                        console.log(residentDetails.container)
                    }
                }
            }

        }

    }

}

