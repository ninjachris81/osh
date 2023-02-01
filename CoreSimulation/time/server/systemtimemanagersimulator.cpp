#include "systemtimemanagersimulator.h"
#include "time/systemtimemessage.h"

#include <QDebug>
#include <QDateTime>
#include "shared/time.h"

#include "macros.h"

SystemtimeManagerSimulator::SystemtimeManagerSimulator(QObject *parent) : SystemtimeManager(parent)
{
    SystemtimeManagerSimulator::MANAGER_ID = QLatin1String("SystemtimeManagerSimulator");
}

void SystemtimeManagerSimulator::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;
    SystemtimeManager::init(config);
}

qint64 SystemtimeManagerSimulator::_getSystemTime() {
    return QDateTime::currentSecsSinceEpoch();
}
