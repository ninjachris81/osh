#ifndef VALUEMANAGERBASE_H
#define VALUEMANAGERBASE_H

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "valuebase.h"
#include "valuemessage.h"

class ValueManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerBase(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    virtual void handleReceivedMessage(ValueMessage* msg) = 0;

    void publishValue(ValueBase* value);

    virtual void registerValue(ValueBase* value);

protected:
    ValueBase* getValue(QString fullId);
    ValueBase* getValue(QString valueGroupId, QString valueId);

    QMap<QString, ValueBase*> m_knownValues;

private:
    QTimer m_signalRateTimer;

private slots:
    void onUpdateSignalRates();

signals:
    void updateSignalRates();

public slots:
};

#endif // VALUEMANAGERBASE_H
