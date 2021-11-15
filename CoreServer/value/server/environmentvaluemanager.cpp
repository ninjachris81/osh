#include "environmentvaluemanager.h"

#include <QDebug>
#include <QDateTime>

#include "macros.h"
#include "value/valuemanagerbase.h"
#include "value/valuegroup.h"

QString EnvironmentValueManager::MANAGER_NAME = QStringLiteral("EnvironmentValueManager");

EnvironmentValueManager::EnvironmentValueManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_valueTimer, &QTimer::timeout, this, &EnvironmentValueManager::updateValues);
}

void EnvironmentValueManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ValueManagerBase);

    ValueManagerBase* valueManager = getManager<ValueManagerBase>(ValueManagerBase::MANAGER_NAME);


    ValueGroup* envGroup = new ValueGroup("env");
    m_systemTime = new LongValue(envGroup, "unixtime_sec");

    valueManager->registerValue(m_systemTime);

    m_valueTimer.start(1000);
}

QString EnvironmentValueManager::getName() {
    return MANAGER_NAME;
}

MessageBase::MESSAGE_TYPE EnvironmentValueManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void EnvironmentValueManager::handleReceivedMessage(MessageBase* msg) {
}

void EnvironmentValueManager::updateValues() {
    m_systemTime->updateValue(QDateTime::currentSecsSinceEpoch());
}
