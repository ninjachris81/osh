#include "testdatamodel.h"

#include "value/booleanvalue.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase(parent) {
    qDebug() << Q_FUNC_INFO;

    ValueGroup* vg = new ValueGroup("relays");
    m_valueGroups.insert("vg1", vg);

    m_values.insert("rel0", (new BooleanValue(vg, "rel0"))->withValueTimeout(ValueBase::VALUE_TIMEOUT_SHORT));

    m_knownDevices.insert("582645258", new KnownDevice("582645258", "GUI"));
}
