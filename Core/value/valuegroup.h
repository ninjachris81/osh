#ifndef VALUEGROUP_H
#define VALUEGROUP_H

#include <QObject>

#include "serializableidentifyable.h"

class ValueGroup : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    ValueGroup();
    explicit ValueGroup(QString id, QObject *parent = nullptr);

    /*virtual*/ QString getClassName() override;

signals:

public slots:
};

#endif // VALUEGROUP_H
