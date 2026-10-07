#include "obiscontroller3.h"

#include <QDebug>

#include "controller/controllermanager.h"
#include "helpers.h"
#include "smlsocketreader.h"

OBISController3::OBISController3(ControllerManager *manager, QString id, QObject *parent)
    : ControllerBase(manager, id, parent)
{
}

void OBISController3::init()
{
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(
        ClientSystemWarningsManager::MANAGER_ID);

    const QString port = m_config->getString(this, "serial.port", "COM1");
    m_smlSocketReader = new SMLSocketReader(port, this);

    Helpers::safeConnect(m_smlSocketReader, &SMLSocketReader::obisValueReceived,
                         this, &OBISController3::onObisValueReceived,
                         SIGNAL(obisValueReceived(QByteArray,QVariant)),
                         SLOT(onObisValueReceived(QByteArray,QVariant)));
    Helpers::safeConnect(m_smlSocketReader, &SMLSocketReader::readerError,
                         this, &OBISController3::onReaderError,
                         SIGNAL(readerError(QString)), SLOT(onReaderError(QString)));
}

void OBISController3::start()
{
    iDebug() << Q_FUNC_INFO;

    if (m_smlSocketReader->start()) {
        Q_EMIT(controllerConnected());
    } else {
        Q_EMIT(controllerDisconnected());
    }
}

void OBISController3::handleMessage(ControllerMessage *msg)
{
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

quint8 OBISController3::bindValue(ValueBase *value)
{
    if (m_valueMappings.size() >= SML_INDEX::COUNT) {
        iWarning() << "Cannot map more than" << SML_INDEX::COUNT << "values";
    } else {
        m_valueMappings.append(value);
    }

    return static_cast<quint8>(m_valueMappings.size());
}

void OBISController3::onObisValueReceived(QByteArray obisCode, QVariant value)
{
    if (obisCode.size() < 6) {
        iWarning() << "Ignoring SML entry with invalid OBIS code" << obisCode.toHex();
        return;
    }

    const auto byte = [&obisCode](qsizetype index) {
        return static_cast<unsigned char>(obisCode.at(index));
    };

    SML_INDEX index;
    if (byte(0) == 0x01 && byte(1) == 0x00 && byte(2) == 0x01
        && byte(3) == 0x08 && byte(4) == 0x00 && byte(5) == 0xff) {
        index = CONSUMPTION_TOTAL;
    } else if (byte(0) == 0x01 && byte(1) == 0x00 && byte(2) == 0x02
               && byte(3) == 0x08 && byte(4) == 0x00 && byte(5) == 0xff) {
        index = PRODUCTION_TOTAL;
    } else {
        return;
    }

    if (index >= m_valueMappings.size() || !m_valueMappings.at(index)) {
        iWarning() << "No value bound for OBIS index" << index;
        return;
    }

    ValueBase *mappedValue = m_valueMappings.at(index);
    if (mappedValue->updateValue(value, false)) {
        m_valueManager->publishValue(mappedValue);
    }
}

void OBISController3::onReaderError(QString message)
{
    iWarning() << "SML reader error:" << message;
    m_warnManager->raiseWarning("SML reader error: " + message, QtWarningMsg);
}
