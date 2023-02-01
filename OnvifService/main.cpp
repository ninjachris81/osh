#include <QCoreApplication>
#include <QLoggingCategory>

#include "manager/managerregistration.h"
#include "qmqttcommunicationmanager.h"
#include "onvifservercontroller.h"
#include "onvifcontroller.h"
#include "controller/controllermanager.h"
#include "device/client/clientdevicemanager.h"
#include "time/client/clientsystemtimemanager.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/client/clientvaluemanager.h"
#include "actor/actormanager.h"
#include "value/doublevalue.h"
#include "shared/mqtt_qt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false"));

    ManagerRegistration managerRegistration(ManagerRegistration::CLIENT);

    QMqttCommunicationManager commManager;
    ControllerManager controllerManager;
    ClientDeviceDiscoveryManager clientManager("OnvifService");
    ClientSystemtimeManager systimeManager;
    ClientSystemWarningsManager syswarnManager;
    ClientValueManager valueManager;
    ActorManager actorManager;

    commManager.setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);

    managerRegistration.registerManager(&commManager);
    managerRegistration.registerManager(&controllerManager);
    managerRegistration.registerManager(&clientManager);
    managerRegistration.registerManager(&systimeManager);
    managerRegistration.registerManager(&syswarnManager);
    managerRegistration.registerManager(&valueManager);
    managerRegistration.registerManager(&actorManager);

    //OnvifServerController onvifServerController(&controllerManager, "OnvifServer");
    OnvifController onvifController(&controllerManager, "OnvifClient");

    //controllerManager.registerController(&onvifServerController);
    controllerManager.registerController(&onvifController);

    QString staticCam = onvifController.deviceRegistry()->registerDevice("192.168.1.101");
    QList<Device::DeviceServiceInfo> staticCamServiceInfo;
    Device::DeviceServiceInfo serviceInfo;

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver10/device/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/device_service";
    staticCamServiceInfo.append(serviceInfo);

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver10/events/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/event_service";
    staticCamServiceInfo.append(serviceInfo);

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver10/analytics/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/analytics_service";
    staticCamServiceInfo.append(serviceInfo);

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver10/media/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/media_service";
    staticCamServiceInfo.append(serviceInfo);

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver20/ptz/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/ptz_service";
    staticCamServiceInfo.append(serviceInfo);

    serviceInfo.deviceNamespace = "http://www.onvif.org/ver20/media/wsdl";
    serviceInfo.deviceXAddr = "http://192.168.1.100:8080/onvif/media2_service";
    staticCamServiceInfo.append(serviceInfo);

    onvifController.deviceRegistry()->addDeviceServiceInfo(staticCam, staticCamServiceInfo);

    QObject::connect(&onvifController, &OnvifController::deviceAdded, [&onvifController](QString deviceId) {
        qDebug() << "Device added" << deviceId;
        //PTZ::PtzStatusInfo status = onvifController.getPTZStatus(deviceId);
        //qDebug() << status.panTiltX << status.panTiltY << status.zoomX;

        //bool res = onvifController.continuousMove(deviceId, 0.5, 0);
        //bool res = onvifController.subscribeMotionEvent(deviceId);
        //Debug() << "continuous move" << res;

        //PTZ::PtzStatusInfo status2 = onvifController.getPTZStatus(deviceId);
        //qDebug() << status2.panTiltX << status2.panTiltY << status2.zoomX;
    });

    managerRegistration.init(&config);

    controllerManager.start();

    bool res = onvifController.subscribeMotionEvent(staticCam);

    qDebug() << "RUNNING";

    return a.exec();
}
