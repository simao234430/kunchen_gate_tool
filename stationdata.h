#ifndef STATIONDATA_H
#define STATIONDATA_H

#include <QString>
#include <QTimer>
#include "tablemodel.h"
class StationData: public QObject
{
    Q_OBJECT
public slots:
    void timeout_handler();
public:
    StationData(QString& idNo,TableModel* model);
    ~StationData();

    void update(QString value);
    void init();

    QString idNo;
    QString gateValue;
    int status;
    int receive_count;
    bool off_line;
    QTimer* updateTimer;
    TableModel* parentModel;
signals:
    void timeout_updataInterface();
private:





};

#endif // STATIONDATA_H
