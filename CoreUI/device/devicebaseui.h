#ifndef DEVICEBASEUI_H
#define DEVICEBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "device/devicebase.h"

class DeviceBaseUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit DeviceBaseUI(Identifyable *parent = nullptr);

    Q_PROPERTY(QString fullId READ fullId NOTIFY fullIdChanged)
    Q_PROPERTY(QString serviceId READ serviceId NOTIFY serviceIdChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(qint64 lastPing READ lastPing NOTIFY lastPingChanged)
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY isOnlineChanged)

    QString fullId();
    QString serviceId();
    QString name();
    qint64 lastPing();
    bool isOnline();

protected:
    DeviceBase* m_device;

signals:
    void fullIdChanged();
    void serviceIdChanged();
    void nameChanged();
    void lastPingChanged();
    void isOnlineChanged();

public slots:
};

#endif // DEVICEBASEUI_H
