#include "devicediscoverymanagerui.h"

#include <QDebug>

#include "macros.h"

#include "datamodel/server/datamodelmanager.h"

DeviceDiscoveryManagerUI * DeviceDiscoveryManagerUI::m_instance = nullptr;

DeviceDiscoveryManagerUI::DeviceDiscoveryManagerUI(QObject *parent) : DeviceDiscoveryManagerBase(parent)
{
    m_instance = this;
    m_modelBridge = new DeviceDiscoveryModelBridge(this);

    connect(m_modelBridge, &DeviceDiscoveryModelBridge::unknownDevicesChanged, this, &DeviceDiscoveryManagerUI::devicesChanged);
}

QObject* DeviceDiscoveryManagerUI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return m_instance;
}

QList<QObject*> DeviceDiscoveryManagerUI::devices() {
    m_devices.clear();

    QMapIterator<QString, DeviceBase*> it(m_modelBridge->unknownDevices());
    while(it.hasNext()) {
        it.next();
        m_devices.append(new DeviceBaseUI(it.value()));
    }

    QMapIterator<QString, KnownDevice*> it2(m_modelBridge->knownDevices());
    while(it2.hasNext()) {
        it2.next();
        m_devices.append(new DeviceBaseUI(it2.value()));
    }

    return m_devices;
}

void DeviceDiscoveryManagerUI::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    DeviceDiscoveryManagerBase::init(config);

    m_modelBridge->init(config);
}

MessageBase::MESSAGE_TYPE DeviceDiscoveryManagerUI::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY;
}

void DeviceDiscoveryManagerUI::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    DeviceDiscoveryMessage* ddMessage = static_cast<DeviceDiscoveryMessage*>(msg);

    m_modelBridge->handleReceivedMessage(ddMessage);
}
