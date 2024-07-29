#ifndef GPIOWATERMETERCONTROLLER_H
#define GPIOWATERMETERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMutex>

#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"
#include "mcpreader.h"

class SHARED_LIB_EXPORT GPIOWaterMeterController : public ControllerBase
{
    Q_OBJECT
public:

    explicit GPIOWaterMeterController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void onStateChanged(quint8 index, bool state);
    void onErrorOccurred();

    void retrieveStatus();

private slots:
    void onCalculateFlow();

private:
    void bindValueManager(ClientValueManager *valueManager, DatamodelBase *datamodel);

    QMutex m_flowCounterMutex;
    QTimer m_flowTimer;

    QString m_waterLevelValueGroupId;
    QString m_waterFlowValueGroupId;

    ClientSystemWarningsManager* m_warnManager;
    //QTimer m_statusTimer;
    uint8_t m_sensorCount;
    uint8_t m_dataOffset;
    float m_stepAmountML;
    GPIOReaderBase* m_reader = nullptr;

    QList<DoubleValue*> m_waterLevelMappings;
    QList<DoubleValue*> m_waterFlowMappings;

    ValueManagerBase* m_valueManager = nullptr;
    ValueGroup *m_waterLevelValueGroup;
    ValueGroup *m_waterFlowValueGroup;

    QList<quint16> m_waterFlows;

signals:

};

#endif // GPIOWATERMETERCONTROLLER_H
