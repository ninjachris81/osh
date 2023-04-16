#include "obiscontroller.h"

#include <QDebug>

#include "controller/controllermanager.h"
#include "helpers.h"

OBISController::OBISController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
}

void OBISController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_serialClient = new SerialPortClient(m_config->getString(this, "serial.port", "COM1"), QSerialPort::Baud9600);

    m_serialClient->setReadBufferSize(1);
    m_serialClient->setLineMode(false);
    m_serialClient->setReadDatagramSize(1);

    Helpers::safeConnect(m_serialClient, &SerialPortClient::connected, this, &OBISController::onSerialConnected, SIGNAL(connected()), SLOT(onSerialConnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::disconnected, this, &OBISController::onSerialDisconnected, SIGNAL(disconnected()), SLOT(onSerialDisconnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::dataReceived, this, &OBISController::onSerialDataReceived, SIGNAL(dataReceived(QByteArray)), SLOT(onSerialDataReceived(QByteArray)));

    Helpers::safeConnect(this, &OBISController::dataReceived, this, &OBISController::onDataReceived, SIGNAL(dataReceived()), SLOT(onDataReceived()));
}

void OBISController::start() {
    iDebug() << Q_FUNC_INFO;

    m_serialClient->start();
}

void OBISController::onSerialConnected() {
    iDebug() << Q_FUNC_INFO;

    Q_EMIT(controllerConnected());
}

void OBISController::onSerialDisconnected() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    Q_EMIT(controllerDisconnected());
}

double OBISController::value(SML_INDEX smlIndex) {
    return m_values[smlIndex];
}

void OBISController::onSerialDataReceived(QByteArray data) {
    iDebug() << Q_FUNC_INFO << data;

    if (data.size() == 1) {
        unsigned char dataByte = data.at(0);
        SmlParser::sml_states_t state = m_smlParser.smlState(dataByte);
        switch(state) {
        case SmlParser::SML_START:
            iDebug() << "SML start";
            for (int i = 0;i< SML_INDEX::COUNT;i++) {
                m_values[i] = -1;
            }
            m_startReceived = true;
            break;
        case SmlParser::SML_LISTEND:
            iDebug() << "SML data";
            if (m_smlParser.smlOBISCheck(SmlParser::SML_1_8_0)) {
                m_smlParser.smlOBISWh(m_values[SML_INDEX::CONSUMPTION_TOTAL]);
                iDebug() << "SML consumption" << m_values[SML_INDEX::CONSUMPTION_TOTAL];
            } else if (m_smlParser.smlOBISCheck(SmlParser::SML_2_8_0)) {
                m_smlParser.smlOBISWh(m_values[SML_INDEX::PRODUCTION_TOTAL]);
                iDebug() << "SML production" << m_values[SML_INDEX::PRODUCTION_TOTAL];
            } else {
                iDebug() << "Ignoring SML frame";
            }
            break;
        case SmlParser::SML_FINAL:
            // ok, publish values
            iDebug() << "SML final";
            Q_EMIT(dataReceived());
            break;
        case SmlParser::SML_CHECKSUM_ERROR:
            m_warnManager->raiseWarning("SML Checksum error");
            break;
        case SmlParser::SML_UNEXPECTED:
            if (m_startReceived) {
                m_warnManager->raiseWarning("SML Unexpected error");
            }
            break;
        default:
            break;
        }

    } else {
        m_warnManager->raiseWarning("Invalid response size " + QString::number(data.size()));
    }
}

void OBISController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

quint8 OBISController::bindValue(ValueBase *value) {
    if (m_valueMappings.size() >= SML_INDEX::COUNT) {
        iWarning() << "Cannot map more than" << SML_INDEX::COUNT << "values";
    } else {
        m_valueMappings.append(value);
    }

    return m_valueMappings.size();
}

void OBISController::onDataReceived() {
    iInfo() << Q_FUNC_INFO;

    for (quint8 i = 0; i<SML_INDEX::COUNT;i++) {
        if (m_valueMappings.size() >= i-1) {
            m_valueManager->updateAndPublishValue(m_valueMappings.at(i), m_values[i]);
        } else {
            iWarning() << "No mapping for value" << i;
        }
    }
}
