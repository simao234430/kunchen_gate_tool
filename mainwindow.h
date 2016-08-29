#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>
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


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateInterface();
    void timeout_handler();
    void clickStartButton();
    void clickWriteGateButton();
    void receiveNetworkConstructError();
    void sendNetworkConstructError();
    void destroy_data();
    void updateStation_list();
private:

    NetWork *netWork;
    bool isStarted;
    Config *inputModel;
    QTimer* interfaceTimer;
    QTimer* stepshowTimer;




};

#endif // MAINWINDOW_H
