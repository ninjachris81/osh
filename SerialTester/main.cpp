#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QSerialPort serialPort;
    
    // 1. NUR den Namen zuweisen. Keine automatischen Infos laden!
    serialPort.setPortName("ttyUSB0"); 

    qDebug() << "Versuche /dev/ttyUSB0 im rohen Zustand zu öffnen...";

    // 2. Direkt öffnen. Falls Qt6 hier "Invalid Argument" wirft, 
    //    liegt es an den Standard-Initialisierungsflags des Linux-Treibers.
    if (serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Port erfolgreich geöffnet!";
        
        // 3. Nun die Parameter einzeln setzen und jeden Rückgabewert prüfen.
        // Bei manchen Treibern schlägt das Setzen VOR dem Open fehl, bei anderen DANACH.
        if (!serialPort.setBaudRate(QSerialPort::Baud115200)) {
            qWarning() << "Baudrate-Fehler:" << serialPort.errorString();
        }
        if (!serialPort.setDataBits(QSerialPort::Data8)) {
            qWarning() << "DataBits-Fehler:" << serialPort.errorString();
        }
        if (!serialPort.setParity(QSerialPort::NoParity)) {
            qWarning() << "Parity-Fehler:" << serialPort.errorString();
        }
        if (!serialPort.setStopBits(QSerialPort::OneStop)) {
            qWarning() << "StopBits-Fehler:" << serialPort.errorString();
        }
        if (!serialPort.setFlowControl(QSerialPort::NoFlowControl)) {
            qWarning() << "FlowControl-Fehler:" << serialPort.errorString();
        }

        qDebug() << "Hardware-Konfiguration abgeschlossen.";
    } else {
        qCritical() << "Fehler beim Öffnen von ttyUSB0:" << serialPort.errorString();
        qCritical() << "Interner Qt-Fehlercode:" << serialPort.error();
        return 1;
    }

    QObject::connect(&serialPort, &QSerialPort::readyRead, [&serialPort]() {
        qDebug() << "Daten erhalten:" << serialPort.readAll().toHex();
    });

    return a.exec();
}
