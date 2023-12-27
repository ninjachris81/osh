#include "obiscontroller2.h"

#include <QDebug>
#include <QFile>

#include "controller/controllermanager.h"
#include "helpers.h"

OBISController2::OBISController2(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
}

OBISController2::~OBISController2() {
    m_serverProcess.terminate();
}

void OBISController2::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    QString devPath = m_config->getString(this, "serial.port", "COM1");
    QString exec = m_config->getString(this, "server.path", "/etc/osh/libsml/examples/sml_server");

    if (QFile::exists(exec)) {
         m_serverProcess.setProgram(exec);
         m_serverProcess.setArguments(QStringList() << devPath);

         Helpers::safeConnect(&m_serverProcess, &QProcess::started, this, &OBISController2::onProcessStarted, SIGNAL(started()), SLOT(onProcessStarted()));
         //Helpers::safeConnect(&m_serverProcess, &QProcess::finished, this, &OBISController2::onProcessFinished, SIGNAL(finished(int)), SLOT(onProcessFinished(int)));

         Helpers::safeConnect(&m_serverProcess, &QProcess::readyReadStandardOutput, this, &OBISController2::onDataReceived, SIGNAL(readyReadStandardOutput()), SLOT(onDataReceived()));
    } else {
        iWarning() << "File does not exist" << exec;
    }

    Helpers::safeConnect(this, &OBISController2::dataReceived, this, &OBISController2::onDataReceived, SIGNAL(dataReceived()), SLOT(onDataReceived()));
}

void OBISController2::start() {
    iDebug() << Q_FUNC_INFO;

    m_serverProcess.start();
}

void OBISController2::onProcessStarted() {
    iDebug() << Q_FUNC_INFO;

    Q_EMIT(controllerConnected());
}

void OBISController2::onProcessFinished(int exitCode) {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Server process terminated " + QString::number(exitCode));
    Q_EMIT(controllerDisconnected());
}

void OBISController2::onDataReceived() {
    iDebug() << Q_FUNC_INFO;

    while (m_serverProcess.canReadLine()) {
        QString lineData = m_serverProcess.readLine();

        iDebug() << lineData;

        SML_DATA data;
        if (parseData(lineData, data)) {
            if (m_valueMappings.at(data.index)->updateValue(data.value, false)) {
                m_valueManager->publishValue(m_valueMappings.at(data.index));
            }
        }
    }
}

bool OBISController2::parseData(QString lineData, OBISController2::SML_DATA &data) {
    int pos = lineData.indexOf(":");
    lineData = lineData.mid(pos + 1);

    QString id = lineData.left(lineData.indexOf("*"));
    if (data.setIndex(id)) {
        pos = lineData.indexOf("#");
        lineData = lineData.mid(pos + 1);

        QString value = lineData.left(lineData.indexOf("#"));
        data.setValue(value);
        return true;
    }

    return false;
}

void OBISController2::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

quint8 OBISController2::bindValue(ValueBase *value) {
    if (m_valueMappings.size() >= SML_INDEX::COUNT) {
        iWarning() << "Cannot map more than" << SML_INDEX::COUNT << "values";
    } else {
        m_valueMappings.append(value);
    }

    return m_valueMappings.size();
}
