#include <QCoreApplication>
#include <QDebug>

#include "config/localconfig.h"
#include "plaingpioreader.h"

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

    PlainGPIOReader reader(pinList);
    Q_ASSERT(inputCount > 0);

    QObject::connect(&reader, &GPIOReaderBase::stateChanged, [](quint8 index, bool state){
        qDebug() << index << state;
    });

    QObject::connect(&reader, &GPIOReaderBase::error, [](QString desc){
        qDebug() << desc;
    });

    reader.start();
    reader.enableDebug();

    return a.exec();
}
