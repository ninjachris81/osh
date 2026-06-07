#ifndef DYNAMICDATAMODEL_H
#define DYNAMICDATAMODEL_H

#include <QObject>

#include "sharedlib.h"

#include "datamodel/datamodelbase.h"

class SHARED_LIB_EXPORT DynamicDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit DynamicDatamodel(QObject *parent = nullptr);

    void addActor(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties);
    void addValue(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties);

private:

signals:

public slots:
};

#endif // DYNAMICDATAMODEL_H
