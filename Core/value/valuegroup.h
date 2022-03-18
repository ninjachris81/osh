#ifndef VALUEGROUP_H
#define VALUEGROUP_H

#include <QObject>

#include "serializableidentifyable.h"

class ValueGroup : public SerializableIdentifyable
{
    Q_OBJECT
public:
    ValueGroup();
    explicit ValueGroup(QString id, QObject *parent = nullptr);

signals:

public slots:
};

#endif // VALUEGROUP_H
