#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTableView>
class NetWork;
namespace Ui {
class MainWindow;
}
class Model;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void init();
    void initInput();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void clickStartButton();
    void clickWriteGateButton();
    void receiveNetworkConstructError();
private:
    Ui::MainWindow *ui;
    NetWork *netWork;
    bool isStarted;
    Model *inputModel;


};

#endif // MAINWINDOW_H
