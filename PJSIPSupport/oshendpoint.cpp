#include "oshendpoint.h"

#include <QDebug>

OshEndpoint::OshEndpoint(QObject *parent)
    : QObject(parent), Endpoint()
{
}

void OshEndpoint::init() {
    libCreate();

    // Initialize endpoint
    EpConfig ep_cfg;
    libInit( ep_cfg );

    // Create SIP transport. Error handling sample is shown
    TransportConfig tcfg;
    tcfg.port = 5060;
    try {
        transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        qWarning() << QString::fromStdString(err.info());
    }

    // Start the library (worker threads etc)
    libStart();
}
