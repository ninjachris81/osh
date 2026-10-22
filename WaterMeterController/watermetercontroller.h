#pragma once

#include <QObject>
#include <QTimer>
#include <QMutex>

#include "datamodel/datamodelbase.h"
#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

class SHARED_LIB_EXPORT WaterMeterController : public ControllerBase
{
    Q_OBJECT
public:

    explicit WaterMeterController(ControllerManager* manager, QString id, QString inputSensorGroupId, QString waterFlowValueGroupId, QString waterLevelValueGroupId, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void onStateChanged(quint8 index, bool state);

    void bindValueManager(ClientValueManager *valueManager, DatamodelBase *datamodel);

private slots:
    void onCalculateFlow();

private:

    QMutex m_flowCounterMutex;
    QTimer m_flowTimer;

    QString m_inputSensorGroupId;
    QString m_waterLevelValueGroupId;
    QString m_waterFlowValueGroupId;

    ClientSystemWarningsManager* m_warnManager;
    //QTimer m_statusTimer;
    uint8_t m_inputSensorCount;
    uint8_t m_inputSensorOffset;
    uint8_t m_waterLevelOffset;
    uint8_t m_waterFlowOffset;
    float m_stepAmountML;
    uint64_t m_startedAtMs;
    uint16_t m_initialLevelTimeoutMs{5000};

    QList<BooleanValue*> m_inputSensorMappings;
    QList<DoubleValue*> m_waterLevelMappings;
    QList<DoubleValue*> m_waterFlowMappings;
    QList<bool> m_waterLevelInitialized;

    ValueManagerBase* m_valueManager = nullptr;
    ValueGroup *m_inputSensorGroup;
    ValueGroup *m_waterLevelValueGroup;
    ValueGroup *m_waterFlowValueGroup;

    QList<quint16> m_waterFlows;

signals:

};
