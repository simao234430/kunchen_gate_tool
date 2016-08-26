#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringListModel>
#include <mainwindow.h>
class StationData;
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = 0);
    //void insertRow(int row, const QModelIndex &parent = QModelIndex());
    //void addEntry(QString s);
    void addEntry(QString s,QString gateValue);
    void updateEntry(QString id_no,QString value);

    QPair<QString, StationData*> find(QString s);

    QList<QPair<QString, StationData*> >* getList();
    QList<QPair<QString, StationData*> > *listOfPairs;
    QStringListModel *model;
    QStringList *id_list;
    void destroy_data();
    void stop();
    MainWindow* parentWindow;

    //QMap<QString, StationData> *stationDataMap;
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool already_exist_station_id(QString s);
private:
public slots:
    void updataInterface();
};

#endif // TABLEMODEL_H
