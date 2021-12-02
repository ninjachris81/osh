#include "testdatamodel.h"

#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "value/doublevalue.h"
#include "processor/server/processortask.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase("TestDatamodel", parent) {
    iDebug() << Q_FUNC_INFO;

    addKnownDevice("349785676", "CoreServer", "Server");
    addKnownDevice("582645258", "CoreUI", "GUI");
    addKnownDevice("66403375", "InputService", "Node EG Input");
    addKnownDevice("66403375", "RelayService", "Node EG Relay");
    addKnownDevice("00001", "THService1", "Sensor EG TH");

    ValueGroup* nodeEGRelays = addValueGroup("egRelays0");
    for (quint8 i = 0;i<8;i++) {
        addDigitalActor(nodeEGRelays, QString::number(i), true, ValueBase::VALUE_TIMEOUT_MID);
    }

    ValueGroup* nodeEGInputs = addValueGroup("egInputs0");
    for (quint8 i = 0;i<16;i++) {
        addBooleanValue(nodeEGInputs, QString::number(i), ValueBase::VALUE_TIMEOUT_MID);
    }

    ValueGroup* nodeEGTemps = addValueGroup("egTemps0");
    addDoubleValue(nodeEGTemps, "0", UT_DEGREES, ValueBase::VALUE_TIMEOUT_MID);

    ValueGroup* nodeEGHums = addValueGroup("egHums0");
    addDoubleValue(nodeEGHums, "0", UT_DEGREES, ValueBase::VALUE_TIMEOUT_MID);

    addProcessorTask("egRelays0", "values_egRelays0_0.rawValue()");
    addProcessorTask("egInputs0", "values_egInputs0_0.rawValue()");
    addProcessorTask("logicproc1", "CommonScripts.ensureState(values_egRelays0_0, values_egInputs0_0, false, function(expected) {values_egRelays0_0.triggerCmd(expected ? C.ACTOR_CMD_ON : C.ACTOR_CMD_OFF )} );");
}
