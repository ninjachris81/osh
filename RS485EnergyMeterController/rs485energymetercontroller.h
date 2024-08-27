#ifndef RS485ENERGYMETERCONTROLLER_H
#define RS485ENERGYMETERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QModbusRtuSerialMaster>

#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "orno.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class SHARED_LIB_EXPORT RS485EnergyMeterController : public ControllerBase
{
Q_OBJECT

public:
    RS485EnergyMeterController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindValueManager(ValueManagerBase* valueManager, DatamodelBase* datamodel);

    struct RetrieveValue {
        QVariant::Type type;
        double multiplier;
        QString mqttName;
        bool twoByte;
    };

protected slots:
    void onStateChanged();
    void onErrorOccurred();
    void onDataReceived();

    void retrieveStatus();

private:
    void registerInput(int reg, QVariant::Type type, double multiplier, bool twoByte);
    void _readInput(int reg, RetrieveValue val);
    QVariant parseValue(QVector<quint16> values, QVariant::Type targetType, double multiplier, bool twoByte);

    ClientSystemWarningsManager* m_warnManager;
    ValueManagerBase* m_valueManager = nullptr;
    QModbusRtuSerialMaster m_modbusClient;
    QTimer m_statusTimer;

    QMap<int, RetrieveValue> m_inputRegisters;
    QMap<int, ValueBase*> m_inputMappings;

    ValueGroup* m_valueGroup;

    int m_slaveId = 1;

    OrnoWe::OrnoTypes m_type = OrnoWe::WE514;

};

#endif // RS485ENERGYMETERCONTROLLER_H
