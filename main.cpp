#include "mainwindow.h"

#include <QApplication>
#include <QCanBus>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QCanBusDevice *device = w.DeviceInit();
    QObject::connect(device, &QCanBusDevice::framesReceived, &w, &MainWindow::ReadMessage);
    w.show();
    return a.exec();
}
