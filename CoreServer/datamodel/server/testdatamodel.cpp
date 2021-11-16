#include "testdatamodel.h"

#include "value/booleanvalue.h"
#include "processor/server/processortask.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase("TestDatamodel", parent) {
    iDebug() << Q_FUNC_INFO;

    ValueGroup* vg = new ValueGroup("relays");
    m_valueGroups.insert(vg->id(), vg);

    BooleanValue* rel0 = new BooleanValue(vg, "rel0");
    rel0->withValueTimeout(ValueBase::VALUE_TIMEOUT_SHORT);

    m_values.insert(rel0->id(), rel0);

    KnownDevice* knownDevice = new KnownDevice("582645258", "GUI");
    m_knownDevices.insert(knownDevice->id(), knownDevice);

    ProcessorTask* processorNode = new ProcessorTask("testprocess0", "rel0.rawValue()==undefined");
    m_processorTasks.insert(processorNode->id(), processorNode);
}
