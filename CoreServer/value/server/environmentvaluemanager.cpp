#include "environmentvaluemanager.h"

#include <QDebug>
#include <QDateTime>

#include "macros.h"
#include "value/valuemanagerbase.h"
#include "value/valuegroup.h"

QLatin1String EnvironmentValueManager::MANAGER_ID = QLatin1String("EnvironmentValueManager");

EnvironmentValueManager::EnvironmentValueManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_valueTimer, &QTimer::timeout, this, &EnvironmentValueManager::updateValues);
}

LogCat::LOGCAT EnvironmentValueManager::logCat() {
    return LogCat::VALUE;
}

void EnvironmentValueManager::init(LocalConfig* config) {
    Q_UNUSED(config)

    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManagerBase);

    ValueManagerBase* valueManager = getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);


    ValueGroup* envGroup = new ValueGroup("env");
    m_systemTime = new LongValue(envGroup, "unixtime_sec", VALTYPE_TIMESTAMP);

    valueManager->registerValue(m_systemTime);

    m_valueTimer.start(1000);
}

QString EnvironmentValueManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE EnvironmentValueManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void EnvironmentValueManager::handleReceivedMessage(MessageBase* msg) {
    Q_UNUSED(msg)
}

void EnvironmentValueManager::updateValues() {
    m_systemTime->updateValue(QDateTime::currentSecsSinceEpoch());
}
