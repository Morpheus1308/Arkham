import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    height: 300
    width: 500

    Rectangle
    {
        id: root
        anchors.fill: parent;
        color: "yellow"

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

        Rectangle
        {

            id: residentDetails

            width:0
            height:0
            x: 0
            y: 0

            opacity: 0

            property alias name  : name.text
            property alias title  : title.text
            property alias sanity : sanity.text

            property int originX
            property int originY

            function show(x,y)
            {
                originX = x
                originY = y
                width = parent.width
                height = parent.height
                x = root.x
                y = root.y
                opacity = 1

            }

            function hide()
            {
                width = 0
                height = 0
                x = originX
                y = originY
                opacity = 0
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
                        }
                    }
                }

            }
        }

    }


}
