#pragma once

#include <QObject>

#include "sharedlib.h"

class SHARED_LIB_EXPORT LogForwarderBase : public QObject
{
    Q_OBJECT
public:
    explicit LogForwarderBase(QObject *parent = nullptr);

signals:

public slots:
};

