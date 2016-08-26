#include "network.h"
#include <QUdpSocket>
#include <QMessageBox>
#include <QDebug>
#include <mainwindow.h>
#include <stationdata.h>
#include "tablemodel.h"

NetWork::NetWork(QObject *parent) : QObject(parent)
{
    this->parentWindow = reinterpret_cast<MainWindow*>(parent);
    port = 5555;
    count = 0;
}
void NetWork::write(QString ip,QString port,QString id_no,QString value)
{
    QByteArray tempSendData = QByteArray();
    tempSendData.append('S');
    tempSendData.append('T');
    tempSendData.append('=');
    tempSendData.append(0x66);
    qDebug() << value;
    char c = (char)id_no.toUInt(0,16);
    char id_temp = ((c & 0xf) + 1) << 4 | (c >> 4);
    tempSendData.append(id_temp);

    tempSendData.append((char)value.toUInt());
    tempSendData.append(0x77);
    udpSocket->writeDatagram(tempSendData,QHostAddress(ip), port.toInt());
}

void NetWork::dataReceived()
{
    while(udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        count++;
        process(datagram);
    }
}

void NetWork::process(QByteArray& datagram)
{
    quint8 need_process_station_no;
    QByteArray str(2,0xee);
    if(datagram.left(2) == str)
    {
        need_process_station_no = datagram.data()[2];
        for(quint8 i=0;i<need_process_station_no;i++)
        {
            QString id_no = QString(QByteArray(1,datagram.data()[3 + i*6 + 5]).toHex());
            QString gate_value = QString(QByteArray(1,datagram.data()[3 + i*6 + 4]).toHex());
            if( !(this->parentWindow->tableModel->already_exist_station_id(id_no)) )
            {
                this->parentWindow->tableModel->addEntry(id_no,gate_value);
                this->parentWindow->updateStation_list();
            }else {
                this->parentWindow->tableModel->updateEntry(id_no,gate_value);
            }
        }
    }
}

bool NetWork::start()
{
    udpSocket = new QUdpSocket(this);
    //sendudpSocket = new QUdpSocket(this);

    bool result = udpSocket->bind(port);

    if(!result) {
        emit networkeErrorsignal("udp socket create error!");
        return false;
    }
//    result = sendudpSocket->bind(QHostAddress("192.168.0.8"));
//    if(!result) {
//        emit sendnetworkeErrorsignal("本地ip需要设置为192.168.0.8");
//        return false;
//    }
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));
    return true;
}

void NetWork::stop()
{
    udpSocket->deleteLater();
    //sendudpSocket->deleteLater();
    disconnect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));
}
