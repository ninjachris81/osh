#ifndef OSHENDPOINT_H
#define OSHENDPOINT_H

#include <QObject>

#ifdef PJ_USE_STUBS
    #include "pjstubs.h"
#else
    #include <pjsua2/endpoint.hpp>
#endif

#include "sharedlib.h"

using namespace pj;

class SHARED_LIB_EXPORT OshEndpoint : public QObject, public Endpoint
{
    Q_OBJECT
public:
    explicit OshEndpoint(QObject *parent = nullptr);

    void init();

signals:

};

#endif // OSHENDPOINT_H
