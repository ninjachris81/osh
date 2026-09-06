#pragma once

#include <QObject>

#include "sharedlib.h"

#include "identifyable.h"

class SHARED_LIB_EXPORT ProcessorVariable : public QObject, public Identifyable
{
    Q_OBJECT
public:

    static QLatin1String PROPERTY_VALUE;
    static QLatin1String VARIABLE_PREFIX;

    ProcessorVariable();
    explicit ProcessorVariable(QString id, QString value, QObject *parent = nullptr);

    QString value();

    QString variableId();

    void replaceScriptCode(QString &scriptCode);

private:
    QString m_value;

signals:

};

