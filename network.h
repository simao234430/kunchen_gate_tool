#ifndef NETWORK_H
#define NETWORK_H
#include "tablemodel.h"
#include <QObject>
#include <vector>
class QUdpSocket;
class MainWindow;
class StastionData;
class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork(QObject *parent = 0);
    bool start();
    void stop();
    void flushLog();
    void write(QString ip,QString port,QString id_no,QString value);
    QUdpSocket *udpSocket;
    TableModel* tableModel;
    //QUdpSocket *sendudpSocket;
signals:
    void networkeErrorsignal(const QString&);
    void sendIDlistsignal(const QString&);
    void sendnetworkeErrorsignal(const QString&);
public slots:
    void dataReceived();
private:
    int port;
    int count;

    void process(QByteArray& datagram);
    std::ofstream ofs;

    //MainWindow* parentWindow;
    //MainWindow *parentWidget;
    //bool isStarted;@

};

#endif // NETWORK_H
