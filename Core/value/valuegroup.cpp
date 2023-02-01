#include "valuegroup.h"

ValueGroup::ValueGroup() : SerializableIdentifyable() {

}

ValueGroup::ValueGroup(QString id, QObject *parent) : SerializableIdentifyable (id), QObject(parent)
{
}

QString ValueGroup::getClassName() {
    return staticMetaObject.className();
}
