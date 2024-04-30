#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCanBus>
#include <QDebug>

QCanBusDevice *device = nullptr;

QCanBusDevice* MainWindow::DeviceInit(){
    if(device) return device; //CAN device already connected

    //device not connected
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
        // plugin available
        QString errorString;
        QCanBusDevice *device = QCanBus::instance()->createDevice(
            QStringLiteral("socketcan"), QStringLiteral("vcan0"), &errorString);
        if (!device) {
            qDebug() << errorString;
        } else {
            device->connectDevice();
            return device;
        }
    }
    return nullptr; // :(
}

void MainWindow::ReadMessage(){
    QCanBusFrame frame;
    if(device == nullptr){
        device = DeviceInit();
    }
    while(device->framesAvailable()){
        frame = device->readFrame();
        ui->recievedTextBox->append(frame.toString());
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendMessage_clicked()
{
    if(device == nullptr){
        device = DeviceInit();
    }
    QCanBusFrame frame;
    frame.setFrameId(ui->messageID->text().toInt());
    QByteArray payload(ui->messageData->text().toUtf8());
    frame.setPayload(payload);
    device->writeFrame(frame);
}


