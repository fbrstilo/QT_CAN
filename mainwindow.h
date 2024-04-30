#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCanBus>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QCanBusDevice* DeviceInit();

public slots:
    void ReadMessage();


private slots:
    void on_sendMessage_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
