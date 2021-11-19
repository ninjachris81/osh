#ifndef DEVICEDISCOVERYMANAGERUI_H
#define DEVICEDISCOVERYMANAGERUI_H

#include <QObject>
#include <QList>
#include <QQmlEngine>

#include "device/devicebaseui.h"
#include "device/devicediscoverymanagerbase.h"
#include "device/server/devicediscoverymodelbridge.h"

class DeviceDiscoveryManagerUI : public DeviceDiscoveryManagerBase
{
    Q_OBJECT
    Q_DISABLE_COPY(DeviceDiscoveryManagerUI)
public:
    explicit DeviceDiscoveryManagerUI(QString serviceId, QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> devices READ devices NOTIFY devicesChanged)

    QList<QObject *> devices();

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    static DeviceDiscoveryManagerUI* m_instance;

protected:
    DeviceDiscoveryModelBridge* m_modelBridge;
    QList<QObject*> m_devices;

signals:
    void devicesChanged();

public slots:

};

#endif // DEVICEDISCOVERYMANAGERUI_H
