#ifndef GPIOWATERMETERCONTROLLER_H
#define GPIOWATERMETERCONTROLLER_H

#include <QObject>
#include <QTimer>

#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"
#include "mcpdebouncereader.h"

class SHARED_LIB_EXPORT GPIOWaterMeterController : public ControllerBase
{
    Q_OBJECT
public:

    explicit GPIOWaterMeterController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindValueManager(ClientValueManager *valueManager, DatamodelBase *datamodel);

    void onStateChanged(quint8 index, bool state);
    void onErrorOccurred();

    void retrieveStatus();

private:
    DoubleValue *getValue(uint8_t id);
    void increaseWaterLevel(uint8_t id);

    ClientSystemWarningsManager* m_warnManager;
    //QTimer m_statusTimer;
    uint8_t m_sensorCount;
    uint8_t m_dataOffset;
    float m_stepAmountML;
    MCPDebounceReader* m_debounceReader = nullptr;

    QList<DoubleValue*> m_valueMappings;

    ValueManagerBase* m_valueManager = nullptr;
    ValueGroup *m_valueGroup;



signals:

};

#endif // GPIOWATERMETERCONTROLLER_H
