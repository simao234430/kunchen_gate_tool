#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class config : public QObject
{
    Q_OBJECT
public:
    explicit config(QObject *parent = 0);

signals:

public slots:
};

#endif // CONFIG_H