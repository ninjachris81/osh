#include <QCoreApplication>
#include <QDebug>

#include "config/localconfig.h"
#include "gpioinputcontroller.h"
#include "plaingpioreader.h"
#include "mcpreader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    QString pins = config.getString("pins", "");       // e.g. "3 21 33"
    QList<int> pinList;

    for (QString pin : pins.split(" ", QString::SkipEmptyParts)) {
        pinList << pin.toInt();
    }
    int inputCount = pinList.count();
    qDebug() << "pins:" << pinList;
    Q_ASSERT(inputCount > 0);

    QString gpioType = config.getString("gpioType", GPIOInputController::GPIO_TYPE_PLAIN);

    GPIOReaderBase *reader = nullptr;

    if (gpioType == GPIOInputController::GPIO_TYPE_PLAIN) {
        reader = new PlainGPIOReader(pinList);
    } else if (gpioType == GPIOInputController::GPIO_TYPE_MCP) {
        int pinBase = config.getInt("mcp.pinBase", 65);
        int addr = config.getInt("mcp.addr", 0x20);
        int pinOffset = config.getInt("mcp.pinOffset", 0);

        reader = new MCPReader(inputCount, addr, pinBase, pinOffset, true);
    } else {
        qWarning() << "No gpioType specified";
        exit(-1);
    }

    QObject::connect(reader, &GPIOReaderBase::stateChanged, [](quint8 index, bool state){
        qDebug() << "State" << index << state;
    });

    QObject::connect(reader, &GPIOReaderBase::error, [](QString desc){
        qDebug() << desc;
    });

    reader->enableDebug();
    reader->start();


    return a.exec();
}
