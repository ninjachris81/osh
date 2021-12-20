#ifndef EMPTYDATAMODEL_H
#define EMPTYDATAMODEL_H

#include <QObject>

#include "datamodel/server/datamodelbase.h"

class EmptyDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit EmptyDatamodel(QObject *parent = nullptr);

signals:

};

#endif // EMPTYDATAMODEL_H
