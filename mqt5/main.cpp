#include <QApplication>
#include <QQmlApplicationEngine>
#include "mqtt/mqtt.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
     qmlRegisterType<MQTT>("mqtt", 1, 0, "MQTT");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
