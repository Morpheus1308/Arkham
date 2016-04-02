import QtQuick 2.0

Rectangle
{
    property real rotationAngle: 45
    property real visibleWidth: root.width * Math.cos(rotation.angle / 180.0 * Math.PI);

    function hide()
    {
        state = "hidden"
    }

    function show()
    {
        state = "visible"
    }

    id: root

    transform: Rotation {
        id : rotation
        origin.x: 0;
        origin.y: 0;
        axis.x: 0;
        axis.y: 1;
        axis.z: 0;
        angle: root.rotationAngle
    }



    states: [
        State
        {
            name: "visible"
            PropertyChanges { target: root; rotationAngle: 0}
            PropertyChanges { target: root; opacity: 1.0}

        },
        State
        {
            name: "hidden"
            PropertyChanges { target: root; rotationAngle: 90}
            PropertyChanges { target: root; opacity: 0.0}
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "rotationAngle"; easing.type: Easing.InOutQuad ; duration: 300}
        NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad ; duration: 300}
    }

}

