﻿#include "stationdata.h"
#include <qdebug.h>
#include <QTimer>
#include <QDateTime>

const int DEFAULT_TIMEOUT = 5000;

StationData::StationData(QString& idNo,TableModel* model)
    //:QObject(parent)
{
    this->parentModel = model;
    this->idNo = idNo;
    qDebug() << this->idNo << "init ";
    gateValue = QString('0');
    status = actived;
    receive_count = 0;
    off_line_count = 0;
//    updateTimer = new QTimer(this);
//    updateTimer->start(DEFAULT_TIMEOUT);
//    connect(updateTimer, SIGNAL(timeout()), this, SLOT(timeout_handler()));
    //connect(this, SIGNAL(timeout_updataInterface()), this->parentModel, SLOT(updateInterface()));

}



void StationData::init()
{

}

void StationData::update(QString value)
{
    this->receive_count++;
    this->gateValue = value;
    if(this->status == disactived){
        this->status = actived;
        //updateTimer->start(DEFAULT_TIMEOUT);
    }
    *(this->lastUpdateTime) = QDateTime::currentDateTime();
    //updateTimer->start(DEFAULT_TIMEOUT);
}


void StationData::timeout_handler()
{
    //qDebug() << this->idNo << "time out";
    this->status = disactived;
    //this->updateTimer->stop();
    this->timeout_updateInterface();
    //updateInterface();
}

StationData::~StationData()
{

}
