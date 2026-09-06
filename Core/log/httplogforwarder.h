#pragma once

#include <QObject>

#include "sharedlib.h"

#include "logforwarderbase.h"

class SHARED_LIB_EXPORT HttpLogforwarder : public LogForwarderBase
{
    Q_OBJECT
public:
    explicit HttpLogforwarder(QObject *parent = nullptr);

signals:

public slots:
};

