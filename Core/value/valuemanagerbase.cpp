#include "valuemanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "value/valuemessage.h"

ValueManagerBase::ValueManagerBase(QObject *parent) : ManagerBase(parent)
{

}


void ValueManagerBase::publishValue(ValueBase* value) {
    qDebug() << Q_FUNC_INFO << value->fullId();

    CommunicationManagerBase* commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);
    ValueMessage valueMessage(value->valueGroup()->id(), value->id(), value->rawValue());
    commManager->sendMessage(valueMessage);
}
