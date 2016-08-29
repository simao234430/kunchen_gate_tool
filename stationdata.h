#ifndef STATIONDATA_H
#define STATIONDATA_H

#include <QString>
#include <QTimer>
#include "tablemodel.h"
enum statu_value {
    inited = 0,
    actived = 1,
    disactived = 2
};

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
    int off_line_count;
    bool off_line;
    //QTimer* updateTimer;
    TableModel* parentModel;
    QDateTime* lastUpdateTime;
signals:
    void timeout_updateInterface();
private:

};

#endif // STATIONDATA_H
