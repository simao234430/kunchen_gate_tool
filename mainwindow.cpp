#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QStandardItemModel>
#include <QMessageBox>
#include <network.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    init();
    connect(netWork, SIGNAL(networkeErrorsignal(const QString&)), this, SLOT(receiveNetworkConstructError()));
    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(clickStartButton()));
    connect(ui->WriteGateButton, SIGNAL(clicked()), this, SLOT(clickWriteGateButton()));
}

void MainWindow::initInput()
{
    ui->Input_ip->setText(tr("127.0.0.1"));
    ui->Input_port->setText(tr("8888"));
    ui->Input_time->setText(tr("60"));
    ui->Input_time_step->setText(tr("1"));
    ui->input_gate_value->setText(tr("100"));
}

void MainWindow::init()
{

    initInput();
    netWork = new NetWork();
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(4);

    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("基站号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("状态"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("门限"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("次数"));
    for(int i=1;i<40;i++){
        QStandardItem* item1 = new QStandardItem(tr(""));
        QStandardItem* item2 = new QStandardItem(tr(""));
        QStandardItem* item3 = new QStandardItem(tr(""));
        QStandardItem* item4 = new QStandardItem(tr(""));
        item1->setEditable(false);
        item2->setEditable(false);
        item3->setEditable(false);
        item4->setEditable(false);
        QList<QStandardItem*> item;
        item << item1 << item2 << item3 << item4;
        model->appendRow(item);
    }

    ui->tableView->setModel(model);
}

void MainWindow::clickStartButton()
{
    if(false == isStarted) {
        ui->StartButton->setText(tr("停止"));
        isStarted = true;
        netWork->start();
    }
    else {
        ui->StartButton->setText(tr("开始"));
        isStarted = false;
        netWork->stop();
    }

}

void MainWindow::clickWriteGateButton()
{
    QMessageBox::information(this, "My Tittle", "write World!");
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
