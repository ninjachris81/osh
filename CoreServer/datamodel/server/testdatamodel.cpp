#include "testdatamodel.h"

#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "processor/server/processortask.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase("TestDatamodel", parent) {
    iDebug() << Q_FUNC_INFO;

    ValueGroup* vg = new ValueGroup("test");
    m_valueGroups.insert(vg->id(), vg);

    BooleanValue* rel0 = new BooleanValue(vg, "somebool");
    rel0->withValueTimeout(ValueBase::VALUE_TIMEOUT_SHORT);

    m_values.insert(rel0->id(), rel0);

    KnownDevice* guiDevice = new KnownDevice("582645258", "GUI");
    m_knownDevices.insert(guiDevice->id(), guiDevice);

    KnownDevice* relay0Device = new KnownDevice("66403375", "KMTronic Relay 0");
    m_knownDevices.insert(relay0Device->id(), relay0Device);

    ValueGroup* kmTronicRelay = new ValueGroup("66403375");
    for (quint8 i = 0;i<8;i++) {
        DigitalActor* relayActor = new DigitalActor(kmTronicRelay, QString::number(i), true);
        m_actors.insert(relayActor->id(), relayActor);
    }

    //ProcessorTask* processorNode = new ProcessorTask("testprocess0", "values_test_somebool.rawValue()");
    //m_processorTasks.insert(processorNode->id(), processorNode);

    ProcessorTask* processorNode2 = new ProcessorTask("testprocess1", "values_66403375_0.rawValue()");
    m_processorTasks.insert(processorNode2->id(), processorNode2);
}
