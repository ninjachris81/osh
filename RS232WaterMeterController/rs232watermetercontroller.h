#ifndef RS232WATERMETERCONTROLLER_H
#define RS232WATERMETERCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"
#include "serialportclient.h"

class SHARED_LIB_EXPORT RS232WaterMeterController : public ControllerBase
{
    Q_OBJECT
public:

#define EVENT_HEARTBEAT 0
#define EVENT_DATA      1
#define EVENT_ERROR     99

    explicit RS232WaterMeterController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindValueManager(ClientValueManager *valueManager, DatamodelBase *datamodel);

protected slots:
    void onSerialConnected();
    void onSerialDisconnected();
    void onSerialDataReceived(QByteArray data);

    void onStateChanged();
    void onErrorOccurred();

    void retrieveStatus();

private:
    DoubleValue *getValue(uint8_t id);
    void increaseWaterLevel(uint8_t id);

    SerialPortClient *m_serialClient = nullptr;
    ClientSystemWarningsManager* m_warnManager;
    //QTimer m_statusTimer;
    uint8_t m_sensorCount;
    uint8_t m_dataOffset;
    float m_stepAmountML;

    QList<DoubleValue*> m_valueMappings;

    ValueManagerBase* m_valueManager = nullptr;
    ValueGroup *m_valueGroup;



signals:

};

#endif // RS232WATERMETERCONTROLLER_H
