#pragma once

#include <QByteArray>
#include <QList>
#include <QVariant>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "controller/controllermessage.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/integervalue.h"

class SMLSocketReader;

class SHARED_LIB_EXPORT OBISController3 : public ControllerBase
{
    Q_OBJECT
public:
    OBISController3(ControllerManager *manager, QString id, QObject *parent = nullptr);

    enum SML_INDEX {
        CONSUMPTION_TOTAL,
        PRODUCTION_TOTAL,
        COUNT
    };

    void init() override;
    void start() override;
    void handleMessage(ControllerMessage *msg) override;
    quint8 bindValue(ValueBase *value) override;

private Q_SLOTS:
    void onObisValueReceived(QByteArray obisCode, QVariant value);
    void onReaderError(QString message);

private:
    SMLSocketReader *m_smlSocketReader = nullptr;
    ValueManagerBase *m_valueManager = nullptr;
    ClientSystemWarningsManager *m_warnManager = nullptr;
    QList<ValueBase *> m_valueMappings;
};
