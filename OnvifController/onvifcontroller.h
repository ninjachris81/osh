#ifndef ONVIFCONTROLLER_H
#define ONVIFCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/controllerbase.h"

#include "wrapper/deviceservicewrapper.h"
#include "wrapper/ptzservicewrapper.h"
#include "wrapper/eventservicewrapper.h"
#include "wrapper/mediaservicewrapper.h"
#include "wrapper/imagingservicewrapper.h"
#include "wrapper/analyticsservicewrapper.h"
#include "wrapper/deviceioservicewrapper.h"

#include "onvif/media.h"
#include "onvif/device.h"
#include "onvif/ptz.h"
#include "onvif/event.h"
#include "onvif/analytics.h"

#include "onvif/discoveryobj.h"

#include "deviceregistry.h"

class SHARED_LIB_EXPORT OnvifController : public ControllerBase
{
    Q_OBJECT
public:
    explicit OnvifController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    /*virtual*/ quint8 bindValue(ValueBase* value) override;

    DeviceRegistry* deviceRegistry();

    int sendProb();

    PTZ::PtzStatusInfo getPTZStatus(QString deviceId);
    bool relativeMove(QString deviceId, float x, float y, QString profileToken = "");
    bool continuousMove(QString deviceId, float x, float y, QString profileToken = "");
    bool stop(QString deviceId);

    QString getStreamUrl(QString deviceId, QString profileToken = "");

    bool subscribeMotionEvent(QString deviceId);

private:
    DeviceServiceWrapper* m_deviceSW;
    PTZServiceWrapper* m_ptzSW;
    EventServiceWrapper* m_eventSW;
    AnalyticsServiceWrapper* m_analyticsSW;
    MediaServiceWrapper* m_mediaSW;

    DeviceRegistry m_deviceRegistry;

private slots:
    void onDiscoveredDevice(DescDevice dev);

private:
    DiscoveryObj* m_discoveryObj;

Q_SIGNALS:
    void deviceAdded(QString deviceId);

};

#endif // ONVIFCONTROLLER_H
