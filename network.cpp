#include "network.h"
#include <QUdpSocket>
#include <QMessageBox>
#include <QDebug>
NetWork::NetWork(QObject *parent) : QObject(parent)
{
    //this->parentWidget = parent;
    //isStarted = false;
    port = 5555;
//    udpSocket = new QUdpSocket(this);
//    bool result = udpSocket->bind(port);
//    if(!result) {
////        QMessageBox::information(this->parentWidget, tr("error"),
////                                 tr("udp socket create error!"));
////        return ;
//        emit networkeErrorsignal("udp socket create error!");
//    }
//    if(isStarted){
//        connect(udpSocket, SIGNAL(readyRead()),
//            this, SLOT(dataReceived()));
//    }
}


void NetWork::dataReceived()
{
    while(udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString s = datagram;
        qDebug() << datagram.toHex();
        //showText->insertPlainText(datagram.data());
    }
}

void NetWork::start()
{
    udpSocket = new QUdpSocket(this);
    bool result = udpSocket->bind(port);
    //if(true) {
    if(!result) {
        emit networkeErrorsignal("udp socket create error!");
    }
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(dataReceived()));
}

void NetWork::stop()
{
    udpSocket->deleteLater();
    //disconnect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));
}
