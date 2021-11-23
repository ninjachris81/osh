#include "testdatamodel.h"

#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "processor/server/processortask.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase("TestDatamodel", parent) {
    iDebug() << Q_FUNC_INFO;


    KnownDevice* serverDevice = new KnownDevice("349785676", "CoreServer", "Server");
    m_knownDevices.insert(serverDevice->fullId(), serverDevice);

    KnownDevice* guiDevice = new KnownDevice("582645258", "CoreUI", "GUI");
    m_knownDevices.insert(guiDevice->fullId(), guiDevice);

    KnownDevice* deviceNodeEGInputService = new KnownDevice("66403375", "InputService", "Node EG Input");
    m_knownDevices.insert(deviceNodeEGInputService->fullId(), deviceNodeEGInputService);

    KnownDevice* deviceNodeEGRelayService = new KnownDevice("66403375", "RelayService", "Node EG Relay");
    m_knownDevices.insert(deviceNodeEGRelayService->fullId(), deviceNodeEGRelayService);

    ValueGroup* nodeEGRelays = new ValueGroup("egRelays0");
    for (quint8 i = 0;i<8;i++) {
        DigitalActor* relayActor = new DigitalActor(nodeEGRelays, QString::number(i), true);
        relayActor->withValueTimeout(ValueBase::VALUE_TIMEOUT_MID);
        m_actors.insert(relayActor->id(), relayActor);
    }

    ValueGroup* nodeEGInputs = new ValueGroup("egInputs0");
    for (quint8 i = 0;i<16;i++) {
        BooleanValue* inputValue = new BooleanValue(nodeEGInputs, QString::number(i));
        inputValue->withValueTimeout(ValueBase::VALUE_TIMEOUT_MID);
        m_values.insert(inputValue->id(), inputValue);
    }


    ProcessorTask* processorNode1 = new ProcessorTask("egRelays0", "values_egRelays0_0.rawValue()");
    m_processorTasks.insert(processorNode1->id(), processorNode1);

    ProcessorTask* processorNode2 = new ProcessorTask("egInputs0", "values_egInputs0_0.rawValue()");
    m_processorTasks.insert(processorNode2->id(), processorNode2);

    ProcessorTask* logicNode1 = new ProcessorTask("logicproc1", "CommonScripts.ensureState(values_egInputs0_0, values_egInputs0_0, false, function(expected) {values_egRelays0_0.triggerCmd(expected ? C.ACTOR_CMD_ON : C.ACTOR_CMD_OFF )} );");
    //ProcessorTask* logicNode1 = new ProcessorTask("logicproc1", "CommonScripts.test()");
    m_processorTasks.insert(logicNode1->id(), logicNode1);
}
