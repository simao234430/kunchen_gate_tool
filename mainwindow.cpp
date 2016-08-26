#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QStandardItemModel>
#include <QMessageBox>
#include <network.h>
#include <QTimer>
#include <QDebug>
#include "tablemodel.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //listOfPairs = new QList<QPair<QString, StationData> >();
    //stationDataMap = new QMap<QString, StationData>();
    ui->setupUi(this);
    init();
    connect(netWork, SIGNAL(networkeErrorsignal(const QString&)), this, SLOT(receiveNetworkConstructError()));
    connect(netWork, SIGNAL(sendnetworkeErrorsignal(const QString&)), this, SLOT(sendNetworkConstructError()));
    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(clickStartButton()));
    connect(ui->WriteGateButton, SIGNAL(clicked()), this, SLOT(clickWriteGateButton()));
}

void MainWindow::initInput()
{
    ui->Input_ip->setText(tr("127.0.0.1"));
    ui->Input_port->setText(tr("8888"));
    ui->Input_time->setText(tr("-1"));
    ui->Input_time_step->setText(tr("1"));
    ui->input_gate_value->setText(tr("100"));
}

void MainWindow::updateInterface()
{
    //qDebug() << "stationDataMap->count()" << QString::number(stationDataMap->count(), 10);
    qDebug() << "updateInterface";
    //tableModel->dataChanged();
}

void MainWindow::initModel()
{
    tableModel = new TableModel();
    tableModel->parentWindow = this;
    tableModel->listOfPairs = new QList<QPair<QString, StationData*> >();
    qDebug() << "listOfPairs address:" << tableModel->listOfPairs;
    ui->tableView->setModel(tableModel);
    ui->station_list->setModel(tableModel->model);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

void MainWindow::destroy_data(){
    tableModel->destroy_data();
    qDebug() << "MainWindow->destroy_data()";
}

void MainWindow::init()
{
    initInput();
    initModel();
    qDebug() << "init";
    netWork = new NetWork(this);
    //updateInterface();
}

void MainWindow::timeout_handler()
{
    //interfaceTimer->stop();
    //qDebug() << "stop";
    this->clickStartButton();

}

void MainWindow::clickStartButton()
{
    if(false == isStarted) {
        bool result = netWork->start();
        if(result == true){
            ui->StartButton->setText(tr("停止"));
            isStarted = true;
        }
        int stop_time = ui->Input_time->text().toUInt();
        if(stop_time >0){
            //qDebug() <<"stop_time >0";
            //interfaceTimer = new QTimer(this);
            //interfaceTimer->start(stop_time*1000);
            QTimer::singleShot(stop_time*1000, this, SLOT(timeout_handler()));
            //connect(interfaceTimer, SIGNAL(timeout()), this, SLOT(timeout_handler()));
        }
        this->destroy_data();
    }
    else {
        netWork->stop();
        ui->StartButton->setText(tr("开始"));
        isStarted = false;
        tableModel->stop();
    }

}

void MainWindow::clickWriteGateButton()
{
    //QString tempSendData("test");
    QString ip = ui->Input_ip->text();
    QString port = ui->Input_port->text();
    QString gate_value = ui->input_gate_value->text();
    QString id_no = ui->station_list->currentText();

    int value = gate_value.toInt();
    if(value > 255 || value < 0){
        QMessageBox::information(this, "My Tittle", "门限值需在0到255范围之间");
        return;
    }
    //QString id = ui->i->text();
    //qDebug() << ip << port << gate_value;
    if(isStarted == true){
        netWork->write(ip,port,id_no,gate_value);
        qDebug() << ip << port << gate_value << id_no;
    }else{
        QMessageBox::information(this, "My Tittle", "需要先建立连接");
    }

//    netWork->udpSocket->writeDatagram(
//                     tempSendData, tempSendData.length(),
//                     QHostAddress("192.168.0.102"), 5555);
    //QMessageBox::information(this, "My Tittle", "write World!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::receiveNetworkConstructError()
{
    QMessageBox::information(this, tr("error"),
                                     tr("udp socket create error!"));

}
void MainWindow::sendNetworkConstructError()
{
    QMessageBox::information(this, tr("error"),
                                     tr("本地ip需要设置为192.168.0.8!"));

}
void MainWindow::updateStation_list(){
    ui->station_list->setCurrentIndex(0);
}
