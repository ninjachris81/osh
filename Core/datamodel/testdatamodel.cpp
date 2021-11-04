#include "testdatamodel.h"

#include "value/booleanvalue.h"

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase(parent)
{
    ValueGroup* vg = new ValueGroup("relays");
    m_valueGroups.append(vg);

    m_values.append((new BooleanValue(vg, "rel0"))->withValueTimeout(ValueBase::VALUE_TIMEOUT_SHORT));
}
