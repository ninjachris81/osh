#include "event.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include "soap/onvifeventPullPointSubscriptionBindingProxy.h"
#include "soap/onvifevent.nsmap"


Event::Event()
{

}

Event::~Event()
{

}


void Event::getGetServiceCapabilities(QString devServiceURL) {

    qDebug() << "Event service test: getGetServiceCapabilities";

    PullPointSubscriptionBindingProxy d;

    _eventws__GetServiceCapabilities in;
    _eventws__GetServiceCapabilitiesResponse out;

    if (d.GetServiceCapabilities(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        if(out.Capabilities != NULL){
            if (out.Capabilities->MaxNotificationProducers != nullptr) qDebug() << *out.Capabilities->MaxNotificationProducers;
            if (out.Capabilities->MaxPullPoints != nullptr) qDebug() << *out.Capabilities->MaxPullPoints;
            if (out.Capabilities->PersistentNotificationStorage != nullptr) qDebug() << *out.Capabilities->PersistentNotificationStorage;
            if (out.Capabilities->WSSubscriptionPolicySupport != nullptr) qDebug() << *out.Capabilities->WSSubscriptionPolicySupport;
        }

    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return ;
}
