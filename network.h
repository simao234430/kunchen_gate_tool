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
    void start();
    void stop();

signals:
    void networkeErrorsignal(const QString&);
public slots:
    void dataReceived();
private:
    int port;
    QUdpSocket *udpSocket;
    //MainWindow *parentWidget;
    //bool isStarted;
    QMap<QString, StastionData> *map;
};

#endif // NETWORK_H
