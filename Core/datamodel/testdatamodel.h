#ifndef TESTDATAMODEL_H
#define TESTDATAMODEL_H

#include <QObject>

#include "datamodelbase.h"

class TestDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit TestDatamodel(ProcessorTaskFactory *processorTaskFactory, QObject *parent = nullptr);

signals:

public slots:
};

#endif // TESTDATAMODEL_H
