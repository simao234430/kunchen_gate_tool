#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
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
    void write(QString ip,QString port,QString id_no,QString value);
    QUdpSocket *udpSocket;
    QUdpSocket *sendudpSocket;
signals:
    void networkeErrorsignal(const QString&);
    void sendnetworkeErrorsignal(const QString&);
public slots:
    void dataReceived();
private:
    int port;
    int count;

    void process(QByteArray& datagram);

    MainWindow* parentWindow;
    //MainWindow *parentWidget;
    //bool isStarted;@

};

#endif // NETWORK_H
