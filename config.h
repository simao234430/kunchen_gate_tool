#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{

    Q_OBJECT

    QString ip;
    QString port;
    QString time; //统计时长
    QString time_setp; //显示间隔
public:
    explicit Model(QObject *parent = 0);

signals:

public slots:
};

#endif // MODEL_H
