import QtQuick 2.0
Item
{
    id: root;
    signal loggedIn()

    FoldableItem
    {
        id: loginForm

        color: "#fafafa";
        state: "visible"
        anchors.fill: parent;


        Column
        {
            anchors.horizontalCenter: parent.horizontalCenter;
            spacing: 10

            Image
            {
                source: "arkham.png"
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            InputField
            {
                id: userid
                label: "Email:"
            }

            InputField
            {
                id: password
                password: true
                label: "Password:"
            }

            Button
            {
                label: "Log in..."
                onClicked:
                {

                    console.log("Logs in");
                    root.loggedIn()
                }
            }

            Row
            {
                width: parent.width

                Text
                {
                    text:"Forgot your password?"
                    width: parent.width*0.5
                    horizontalAlignment: Text.AlignHCenter
                }

                Link
                {
                    text:"Create Account..."
                    width: parent.width*0.5
                    onClicked:
                    {

                        console.log("Link click")
                        loginForm.state = "hidden"
                    }
                }
            }


        }


    }


    Rectangle
    {
        id: registerForm
        height:root.height
        width: root.width
        x: loginForm.visibleWidth
        anchors.top: root.top
        color: "#000000";

        Text {
            anchors.centerIn: parent;
            color: "white"
            text :"Done"

            MouseArea
            {
                anchors.fill: parent;
                onClicked:
                {
                    loginForm.state = "visible"
                }
            }
        }
    }

}
