#include "valuegroup.h"

ValueGroup::ValueGroup() : Identifyable() {

}

ValueGroup::ValueGroup(QString id, QObject *parent) : QObject(parent), Identifyable (id)
{
}
