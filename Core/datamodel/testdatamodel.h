#pragma once

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

