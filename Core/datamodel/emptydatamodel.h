#ifndef EMPTYDATAMODEL_H
#define EMPTYDATAMODEL_H

#include <QObject>

#include "sharedlib.h"

#include "datamodel/datamodelbase.h"

class SHARED_LIB_EXPORT EmptyDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit EmptyDatamodel(QObject *parent = nullptr);

signals:

};

#endif // EMPTYDATAMODEL_H
