#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include <QObject>

#include "identifyable.h"
#include "shared/controllercmdtypes_qt.h"

class DeviceBase : public Identifyable
{
    Q_OBJECT
public:
    explicit DeviceBase(QString id, QObject *parent = nullptr);

    void updatePing();

private:
    qint64 m_lastPing = 0;

signals:

public slots:
};

#endif // DEVICEBASE_H
