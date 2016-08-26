#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTableView>
class NetWork;
class QTimer;
namespace Ui {
class MainWindow;
}
class Config;
class StationData;
class TableModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //QList<QPair<QString, StationData> >* listOfPairs;
    //QMap<QString, StationData> *stationDataMap;
    TableModel *tableModel;
    Ui::MainWindow *ui;
    void init();
    void initInput();
    void initModel();
    void updateStation_list();
    void updateInterface();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void timeout_handler();
    void clickStartButton();
    void clickWriteGateButton();
    void receiveNetworkConstructError();
    void sendNetworkConstructError();
    void destroy_data();
private:

    NetWork *netWork;
    bool isStarted;
    Config *inputModel;
    QTimer* interfaceTimer;



};

#endif // MAINWINDOW_H
