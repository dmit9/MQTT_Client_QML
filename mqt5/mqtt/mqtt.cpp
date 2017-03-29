#include "mqtt.h"
#include <QtNetwork>
#include <QString>


MQTT::MQTT(QObject *parent) :
    QObject(parent)
{
    // re-initialize connection whenever the
    // host or the port changes
    QObject::connect(this, SIGNAL(hostChanged(QString)),
            this, SLOT(initializeConnection()));
    QObject::connect(this, SIGNAL(portChanged(int)),
            this, SLOT(initializeConnection()));
    qDebug()<<"Rahr: testing";
    numberOfData =0;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(3000, QUdpSocket::ShareAddress);

    QObject::connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}

void MQTT::processPendingDatagrams()
{
//! [2]
  while (udpSocket->hasPendingDatagrams()) {

      QByteArray buf;
      buf.resize(udpSocket->pendingDatagramSize());
      QDataStream s(&buf, QIODevice::ReadOnly);
      udpSocket->readDatagram(buf.data(), buf.size());

      s >> dataGram.speed >> dataGram.gear >> dataGram.is >> dataGram.lka >> dataGram.fwc;
      qDebug()<<dataGram.speed <<" "<<dataGram.gear<<" "<<dataGram.lka<<" "<<dataGram.fwc;
      QMQTT::Message message;

      message.setTopic("speed");
      QString messagePayload= QString::number(dataGram.speed);
      message.setPayload(messagePayload.toLatin1());
      this->client->publish(message);

      message.setTopic("gear_pos");
      messagePayload= QString::number(dataGram.gear);
      message.setPayload(messagePayload.toLatin1());
      this->client->publish(message);

      message.setTopic("is_active");
      messagePayload= QString::number(dataGram.is);
      message.setPayload(messagePayload.toLatin1());
      this->client->publish(message);

      message.setTopic("fcw_active");
      messagePayload= QString::number(dataGram.fwc);
      message.setPayload(messagePayload.toLatin1());
      this->client->publish(message);

      message.setTopic("lka_active");
      messagePayload= QString::number(dataGram.lka);
      message.setPayload(messagePayload.toLatin1());
      this->client->publish(message);




}
//! [2]
}

void MQTT::initializeConnection()
{
    //Init UDP

    DEBUG;
    if(m_host.isEmpty() || !m_port || m_topic.isEmpty())
    {
        DEBUG << "Please define a host and a port and a topic";
        //disconnect();
        return;
    }
    this->client = new QMQTT::Client(m_host, m_port);
    this->client->setClientId(QString(QUuid::createUuid().toString()));
//    this->client->setUsername("user");
//    this->client->setPassword("password");
    this->client->connect();
    QObject::connect(this->client, SIGNAL(received(const QMQTT::Message&)),
            this, SLOT(processReceivedMessage(const QMQTT::Message&)));
    QObject::connect(this->client, SIGNAL(connacked(quint8)),
                     this, SLOT(subscribeToTopic(quint8)));
    QObject::connect(this->client, SIGNAL(subscribed(QString)),
                     this, SLOT(subscribedToTopic(QString)));
    QObject::connect(this->client, SIGNAL(disconnected()),
                     this, SIGNAL(disconnected()));
    QObject::connect(this->client, SIGNAL(connected()),
                     this, SIGNAL(connected()));
}

