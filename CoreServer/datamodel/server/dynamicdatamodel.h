#ifndef DYNAMICDATAMODEL_H
#define DYNAMICDATAMODEL_H

#include <QObject>
#include "datamodelbase.h"

class DynamicDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit DynamicDatamodel(QObject *parent = nullptr);

    QByteArray serialize();

    void deserialize(QByteArray data);

signals:

public slots:
};

#endif // DYNAMICDATAMODEL_H
