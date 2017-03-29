import QtQuick 2.5
import QtQuick.Controls 1.4
import mqtt 1.0

ApplicationWindow {
    id: wind
    visible: true
    width: 300
    height: 200
    title: qsTr("MQTT")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MQTT {
        id: _MQTT
        host: "192.168.1.231"
        port: 1883
        topic: "/IoTmanager/dev03-Energ/Energ/Watt"

        onConnected: {
        _MQTT.subscribe("/IoTmanager/dev03-Energ/Energ/Volt", 0)
        _MQTT.subscribe("/IoTmanager/dev03-Energ/Energ/Tok", 0)
        _MQTT.subscribe("/IoTmanager/dev03-Energ/Energ/Power", 0)
        _MQTT.subscribe("/IoTmanager/dev03-Energ/Energ/Data", 0)
        }

        onMessageReceived: {                // обработка полученных сообщений

                switch (topic){
                     case ("/IoTmanager/dev03-Energ/Energ/Power"):{
                         label_Power_msg.text = message}
                     case ("/IoTmanager/dev03-Energ/Energ/Watt"):{
                         label_Watt_msg.text = message}
                     case ("/IoTmanager/dev03-Energ/Energ/Tok"):{
                         label_Tok_msg.text = message}
                     case ("/IoTmanager/dev03-Energ/Energ/Volt"):{
                         label_Volt_msg.text = message}
                }
        }
    }

    Label {
        id: label_Watt_topic
        x: 3
        y: 9
        height: 20
        text: qsTr("Watt - ")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Label {
        id: label_Watt_msg
        text: qsTr("Watt")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        color: "red"
        x: 50
        y: 9
        height: 20
    }

    Label {
        id: label_Volt_topic
        x: 3
        y: 40
        text: qsTr("Volt -")
    }

    Label {
        id: label_Volt_msg
        x: 50
        y: 40
        text: qsTr("Volt")
    }

    Label {
        id: label_Tok_topic
        x: 3
        y: 66
        text: qsTr("Tok -")
    }

    Label {
        id: label_Power_topic
        x: 3
        y: 94
        text: qsTr("Power -")
    }

    Label {
        id: label_Tok_msg
        x: 50
        y: 66
        text: qsTr("Tok")
    }

    Label {
        id: label_Power_msg
        x: 50
        y: 94
        text: qsTr("Power")
    }
    Button {
        id: button
        x: 11
        y: 137
        text: qsTr("Button")
        onClicked: {
            _MQTT.subscribe("/IoTmanager/dev03-Energ/Energ/Volt", 0)
        }
    }

}
