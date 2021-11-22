#ifndef COMMONSCRIPTS_H
#define COMMONSCRIPTS_H

#include <QObject>
#include <QJSValue>
#include "processor/server/scriptbase.h"
#include "value/valuebase.h"

class CommonScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit CommonScripts(QObject *parent = nullptr);

    Q_INVOKABLE bool ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant actualInvalid, QJSValue function);

signals:

public slots:
};

#endif // COMMONSCRIPTS_H
