#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include <QObject>

#include "identifyable.h"
#include "shared/controllercmdtypes_qt.h"

class DeviceBase : public Identifyable
{
    Q_OBJECT
public:
    explicit DeviceBase(QString id, QString serviceId, QObject *parent = nullptr);

    QString serviceId();

    QString sessionId();

    void updatePing();

    void updateOnline(qint64 onlineTimeout);

    qint64 lastPing();

    bool isOnline();

private:
    bool m_isOnline = false;
    qint64 m_lastPing = 0;
    QString m_serviceId;

signals:
    void lastPingChanged();
    void isOnlineChanged();

public slots:
};

#endif // DEVICEBASE_H
