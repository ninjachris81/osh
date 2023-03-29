#include "valuegroup.h"

ValueGroup::ValueGroup() : SerializableIdentifyable() {

}

ValueGroup::ValueGroup(QString id, QObject *parent) : QObject(parent), SerializableIdentifyable (id)
{
}

QString ValueGroup::getClassName() {
    return staticMetaObject.className();
}
