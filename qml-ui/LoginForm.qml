import QtQuick 2.0
Item
{
    id: root;
    signal testCredentials(var email, var password)

    Rectangle
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
                value: "a@a.a"
            }

            InputField
            {
                id: password
                password: true
                label: "Password:"
                value: "aaa"
            }

            Button
            {
                label: "Log in..."
                onClicked:
                {

                    console.log("Logs in");
                    root.testCredentials(userid.value, password.value)
                }
            }
        }
    }
}
