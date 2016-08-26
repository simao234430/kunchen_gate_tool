#include "tablemodel.h"
#include <QDebug>
#include <stationdata.h>
QString Status_str[3] = {"inited","actived","disactived"};
TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << "TableModel init";
    id_list = new QStringList();
    model = new QStringListModel();
    //id_list = new QStringList();
    //model->setStringList(*id_list);

}
void TableModel::stop()
{
    for(QPair<QString, StationData*> e:*listOfPairs) {
        e.second->updateTimer->stop();
    }
}

void TableModel::destroy_data()
{
    qDebug() << "tableModel->destroy_data()";
    //delete id_list;
    //id_list->clear();
    //foreach(QPair<QString, StationData*> e ,*listOfPairs) {
    for(QPair<QString, StationData*> e:*listOfPairs) {
        delete e.second;
        listOfPairs->removeOne(e);
    }
    emit dataChanged(QModelIndex(),QModelIndex());

    this->id_list->clear();
    model->setStringList(*id_list);
    //delete model;
    //delete listOfPairs;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug() << "headerData";
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QStringLiteral("基站号");
            case 1:
                return QStringLiteral("状态");
            case 2:
                return QStringLiteral("门限值");
            case 3:
                return QStringLiteral("状态接收次数统计");
            case 4:
                return QStringLiteral("保留1");
            case 5:
                return QStringLiteral("保留2");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return listOfPairs->size();
    //return stationDataMap->count();

    // FIXME: Implement me!
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    //qDebug() << "columnCount";
    return 6;

    // FIXME: Implement me!
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QPair<QString, StationData*> pair = listOfPairs->at(index.row());
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPairs->size() || index.row() < 0)
        return QVariant();
    if (role == Qt::BackgroundColorRole) {
        if (index.column() == 1){
            if(pair.second->status == 1){
                return QColor(QString("green"));
            }else{
                return QColor(QString("red"));
            }
        }
    }

    if (role == Qt::DisplayRole) {
        bool ok = false;

        if (index.column() == 0)
            return pair.first;
        else if (index.column() == 1)
            return Status_str[pair.second->status];
        else if (index.column() == 2)
            return QString(pair.second->gateValue).toInt(&ok,16);
        else if (index.column() == 3)
            return pair.second->receive_count;
    }
    return QVariant();
}

QPair<QString, StationData*> TableModel::find(QString s)
{

    QList< QPair<QString, StationData*> >::iterator i;
    for(i=this->listOfPairs->begin(); i!=this->listOfPairs->end(); ++i)
    {

        if(QString::compare(s,i->first) ==0){

            return *i;
        }
    }
    return QPair<QString, StationData*>("unfind",0);
}

bool TableModel::already_exist_station_id(QString s)
{
    QPair<QString, StationData*> result = find(s);
    if(result.first == "unfind"){
        return false;
    }else{
        return true;
    }

}
bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);


    endInsertRows();
    return true;
}
void TableModel::updateEntry(QString id_no,QString value)
{
    QPair<QString, StationData*> result = find(id_no);
    result.second->update(value);

    emit dataChanged(QModelIndex(),QModelIndex());
    // todo
}

void TableModel::updataInterface(){
    emit dataChanged(QModelIndex(),QModelIndex());
}

void TableModel::addEntry(QString s,QString gateValue)
{
    StationData* tempData = new StationData(s,this);
    //tempData->init();
    tempData->receive_count = 1;
    tempData->gateValue = gateValue;

    QList<QPair<QString, StationData*> >* list = getList();
    QPair<QString, StationData*> pair(s, tempData);
    this->listOfPairs->append(pair);
    this->insertRows(0, 1, QModelIndex());
    emit dataChanged(QModelIndex(),QModelIndex());

    //this->model->stringList().append("ss");

    this->model->insertRow(0,QModelIndex());

    *this->id_list << s;
    model->setStringList(*id_list);


}

QList< QPair<QString, StationData*> >* TableModel::getList()
{
    return listOfPairs;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{


    return false;
}
