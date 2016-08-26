#include "network.h"
#include <QUdpSocket>
#include <QMessageBox>
#include <QDebug>
#include <mainwindow.h>
#include <stationdata.h>
#include "tablemodel.h"

NetWork::NetWork(QObject *parent) : QObject(parent)
{
    //this->parentWidget = parent;
    //isStarted = false;
    this->parentWindow = reinterpret_cast<MainWindow*>(parent);
    port = 5555;
    count = 0;
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
void NetWork::write(QString ip,QString port,QString id_no,QString value)
{
//    char buf[5] = {'0', 'x', id_no[0], id_no[1].toAscii(), 0};
//    char buf1[5] = {'0', 'x', value[0], value[1], 0};
//    char endptr;
//    char temp = strtol(buf, &endptr, 0);
//    char temp1 = strtol(buf1, &endptr, 0);
    qDebug() << "write";
    QByteArray tempSendData = QByteArray();
    tempSendData.append('S');
    tempSendData.append('T');
    tempSendData.append('=');
    tempSendData.append(0x66);
    tempSendData.append(0x31);
    //tempSendData.append((char)id_no.toUInt(0,16));
    char c = (char)value.toUInt();
    char id_temp = ((c & 0xf) + 1) << 4 | (c >> 4);
    tempSendData.append(id_temp);
    //tempSendData.append(temp1);
    //tempSendData.append( QString::number(value.toInt(),16) );
    tempSendData.append(0x77);

    //QString tempSendData("test");
    sendudpSocket->writeDatagram(tempSendData,QHostAddress(ip), port.toInt());
}

void NetWork::dataReceived()
{
    while(udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        count++;
        //qDebug() << datagram.toHex();
        //QString s = datagram;
        process(datagram);

        //showText->insertPlainText(datagram.data());
    }
}

void NetWork::process(QByteArray& datagram)
{
    //quint8 id_no;
    //quint8 gateValue;
    quint8 need_process_station_no;
    QByteArray str(2,0xee);
    QString s;
    //qint32 flag = 0xeeee;
    //qDebug() << datagram.left(4).toHex();
    if(datagram.left(2) == str)
//    if( (datagram.data()[0] == 0xee)
//            &&
//            (datagram.data()[1] == 0xee) )
    {
        //need_process_station_no = datagram.left(3).right(1).toUInt();
        need_process_station_no = datagram.data()[2];
        //qDebug() << need_process_station_no;
        //while()
        //qDebug() << "-------";
        //qDebug() << need_process_station_no;
        //qDebug() << datagram.toHex();
        for(quint8 i=0;i<need_process_station_no;i++)
        {
            //qDebug() << datagram.left(3 + (i+1)*6).right(6).toHex();
            QString s = QString(QByteArray(1,datagram.data()[3 + i*6 + 5]).toHex());
            //qDebug() << s;
            //判断基站id s是否存在
//            if( this->parentWindow->stationDataMap->contains(s) == false)
            if( !(this->parentWindow->tableModel->already_exist_station_id(s)) )
            {
                //qDebug() << "创建对象" << s;
                this->parentWindow->tableModel->addEntry(s,QString(QByteArray(1,datagram.data()[3 + i*6 + 4]).toHex()));
                this->parentWindow->updateStation_list();
            }else {
                //qDebug() << "已经存在";
                this->parentWindow->tableModel->updateEntry(s,QString(QByteArray(1,datagram.data()[3 + i*6 + 4]).toHex()));

                //QPair<QString, StationData*> result = this->parentWindow->tableModel->find(s);
                //result.second->update(QString(QByteArray(1,datagram.data()[3 + i*6 + 4]).toHex()));
            }
            //qDebug() <<"count" ;//<< this->parentWindow->stationDataMap->count();
//            QMap<QString, StationData>::iterator it = this->parentWindow->stationDataMap->find(s);
//            if(it != this->parentWindow->stationDataMap->end()) {
//                it.value().update(datagram.data()[3 + i*6 + 4]);
//            }else{
//                qDebug() << "程序出错";
//            }

            //(*(this->parentWindow->stationDataMap)).find(s).update(datagram.data()[3 + (i-1)*6 + 4]);
            //qDebug() << QByteArray(1,datagram.data()[3 + (i-1)*6 + 4]).toHex();

//            qDebug("  %c ",datagram.data()[3 + (i-1)*6 + 4]);
//            qDebug("  %c ",datagram.data()[3 + (i-1)*6 + 5]);
        }
        //qDebug() <<  s(need_process_station_no);
    }
}

bool NetWork::start()
{
    udpSocket = new QUdpSocket(this);
    sendudpSocket = new QUdpSocket(this);
    //sendudpSocket->bind(QHostAddress("192.168.0.8"));
    bool result = udpSocket->bind(port);
    //if(true) {
    if(!result) {
        emit networkeErrorsignal("udp socket create error!");
        return false;
    }
    result = sendudpSocket->bind(QHostAddress("192.168.0.8"));
    if(!result) {
        emit sendnetworkeErrorsignal("本地ip需要设置为192.168.0.8");
        return false;
    }
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));
    return true;
}

void NetWork::stop()
{
    udpSocket->deleteLater();
    sendudpSocket->deleteLater();
    disconnect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));
}
