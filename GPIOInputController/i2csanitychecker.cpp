#include "i2csanitychecker.h"
#include <QProcess>
#include <QDebug>

I2CSanityChecker::I2CSanityChecker(QObject *parent)
    : QObject{parent}
{
    connect(&m_Timer, &QTimer::timeout, this, &I2CSanityChecker::onCheckBusses);
    m_Timer.setInterval(I2C_CHECK_INTERVAL);
}

void I2CSanityChecker::setBus(int i2cBus) {
    this->m_i2cBus = i2cBus;
}

void I2CSanityChecker::setDevList(QList<int> devList) {
    this->m_devList = devList;
}

void I2CSanityChecker::start() {
    if (!m_devList.isEmpty()) {
        m_Timer.start();
    }
}

void I2CSanityChecker::onCheckBusses() {
    QProcess proc;
    proc.setProgram("/usr/sbin/i2cdetect");
    QStringList args;

    args << "-y";
    args << QString::number(this->m_i2cBus);

    proc.setReadChannel(QProcess::StandardOutput);
    proc.setArguments(args);

    proc.start(QIODevice::ReadOnly);
    proc.waitForFinished(5000);

    QString result = proc.readAllStandardOutput();
    QStringList lines = result.split("\n", QString::SkipEmptyParts);

    QList<int> foundDevs;

    for (int i = 1;i<lines.size();i++) {
        QStringList devices = lines[i].mid(4).split(" ", QString::SkipEmptyParts);

        for (QString dev : devices) {
            if (dev != "--") {
                if (m_devList.contains(dev.toInt())) {
                    foundDevs.append(dev.toInt());
                }
            }
        }
    }

    if (foundDevs.size() != m_devList.size()) {
        qWarning() << "Detected:" << foundDevs << "Required" << m_devList;
        Q_EMIT(i2cNotDetected());
    }
}
