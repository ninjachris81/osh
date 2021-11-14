#include "devicediscoverymanagerserver.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"
#include "datamodel/datamodelmanager.h"
#include "device/devicediscoverymanagerbase.h"

#include "macros.h"

DeviceDiscoveryManagerServer::DeviceDiscoveryManagerServer(QObject *parent) : DeviceDiscoveryManagerBase(parent)
{
    m_modelBridge = new DeviceDiscoveryModelBridge(this);
}

void DeviceDiscoveryManagerServer::init(LocalConfig *config) {
    m_modelBridge->init(config);
}

MessageBase::MESSAGE_TYPE DeviceDiscoveryManagerServer::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY;
}

void DeviceDiscoveryManagerServer::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;
    DeviceDiscoveryMessage* ddMessage = static_cast<DeviceDiscoveryMessage*>(msg);

    DeviceBase* device = m_modelBridge->handleReceivedMessage(ddMessage);
}
