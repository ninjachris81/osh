#ifndef VALUEMANAGERUI_H
#define VALUEMANAGERUI_H

#include <QObject>
#include <QQmlEngine>

#include "value/valuemanagerbase.h"

class ValueManagerUI : public ValueManagerBase
{
    Q_OBJECT
    Q_DISABLE_COPY(ValueManagerUI)
public:
    explicit ValueManagerUI(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg);

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    Q_INVOKABLE QString unitTypeToSuffix(unit::UNIT_TYPE unitType);

protected:
    void valueReceived(ValueBase* value, QVariant newValue);
    void valueReceived(QString valueGroupId, QString valueId, QVariant newValue);

private:
    static ValueManagerUI* m_qmlInstance;

signals:

public slots:
};

#endif // VALUEMANAGERUI_H
