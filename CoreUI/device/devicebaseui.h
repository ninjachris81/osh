#ifndef DEVICEBASEUI_H
#define DEVICEBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "device/devicebase.h"

class DeviceBaseUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit DeviceBaseUI(QObject *parent = nullptr);

    Q_PROPERTY(qint64 lastPing READ lastPing NOTIFY lastPingChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY isOnlineChanged)

    qint64 lastPing();
    QString name();
    bool isOnline();

protected:
    DeviceBase* m_device;

signals:
    void lastPingChanged();
    void nameChanged();
    void isOnlineChanged();

public slots:
};

#endif // DEVICEBASEUI_H
