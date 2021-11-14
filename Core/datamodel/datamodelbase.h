#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QMap>
#include "device/knowndevice.h"
#include "value/valuegroup.h"
#include "value/valuebase.h"

class DatamodelBase : public QObject
{
    Q_OBJECT
public:
    explicit DatamodelBase(QObject *parent = nullptr);

    QMap<QString, ValueBase*> values();
    QMap<QString, KnownDevice *> knownDevices();

protected:
    QMap<QString, KnownDevice*> m_knownDevices;
    QMap<QString, ValueGroup*> m_valueGroups;
    QMap<QString, ValueBase*> m_values;

signals:

public slots:
};

#endif // DATAMODELBASE_H
