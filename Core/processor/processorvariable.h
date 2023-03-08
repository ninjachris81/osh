#ifndef PROCESSORVARIABLE_H
#define PROCESSORVARIABLE_H

#include <QObject>

#include "sharedlib.h"

#include "serializableidentifyable.h"

class SHARED_LIB_EXPORT ProcessorVariable : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:

    static QLatin1String PROPERTY_VALUE;
    static QLatin1String VARIABLE_PREFIX;

    ProcessorVariable();
    explicit ProcessorVariable(QString id, QString value, QObject *parent = nullptr);

    QString value();

    /*virtual*/ QString getClassName() override;

    QString variableId();

    void replaceScriptCode(QString &scriptCode);

private:
    QString m_value;

signals:

};

#endif // PROCESSORVARIABLE_H
