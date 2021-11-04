#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QList>
#include "value/valuegroup.h"
#include "value/valuebase.h"

class DatamodelBase : public QObject
{
    Q_OBJECT
public:
    explicit DatamodelBase(QObject *parent = nullptr);

    QList<ValueBase*> values();

protected:
    QList<ValueGroup*> m_valueGroups;
    QList<ValueBase*> m_values;

signals:

public slots:
};

#endif // DATAMODELBASE_H
