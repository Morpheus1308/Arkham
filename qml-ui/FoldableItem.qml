import QtQuick 2.0

Rectangle
{

    id: root

    property real rotationAngle: 45

    transform: Rotation {
        id : rotation
        origin.x: 0;
        origin.y: 0;
        axis.x: 0;
        axis.y: 1;
        axis.z: 0;
        angle: root.rotationAngle
    }

    property real visibleWidth: root.width * Math.cos(rotation.angle / 180.0 * Math.PI);


    states: [
        State
        {
            name: "visible"
            PropertyChanges { target: loginForm; rotationAngle: 0}
            PropertyChanges { target: loginForm; opacity: 1.0}

        },
        State
        {
            name: "hidden"
            PropertyChanges { target: loginForm; rotationAngle: 90}
            PropertyChanges { target: loginForm; opacity: 0.0}
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "rotationAngle"; easing.type: Easing.InOutQuad ; duration: 300}
        NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad ; duration: 300}
    }

}

