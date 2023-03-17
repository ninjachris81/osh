#include "onvifcontroller.h"

#include "controller/controllermessage.h"

OnvifController::OnvifController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{

}

void OnvifController::init() {
    iDebug() << Q_FUNC_INFO;

    struct soap *soap = soap_new();
    m_deviceSW = new DeviceServiceWrapper(soap);
    m_ptzSW = new PTZServiceWrapper(soap);
    m_eventSW = new EventServiceWrapper(soap);
    m_analyticsSW = new AnalyticsServiceWrapper(soap);
    m_mediaSW = new MediaServiceWrapper(soap);

    int  _metadataVersion = 1;
    /*
    char* _xaddr="http://192.168.1.100/service";
    char* _type="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
    char* _scope="onvif://www.onvif.org/type/ptz";
    char* _endpoint="http://192.168.1.100/service/device";
    */
    char _xaddr[]="http://192.168.1.100/service";
    char _type[]="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
    char _scope[]="onvif://www.onvif.org/type/ptz";
    char _endpoint[]="http://192.168.1.100/service/device";


    iDebug() << "new discovery obj";

    m_discoveryObj = new DiscoveryObj(DiscoveryMode::CLIENT_MODE, _metadataVersion, _xaddr, _type, _scope, _endpoint);
    connect(m_discoveryObj, SIGNAL(discoveredDevice(DescDevice)), this, SLOT(onDiscoveredDevice(DescDevice)));
}

void OnvifController::start() {
    iDebug() << Q_FUNC_INFO;

    sendProb();
}

void OnvifController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

quint8 OnvifController::bindValue(ValueBase *value) {
    return 0;
}

DeviceRegistry* OnvifController::deviceRegistry() {
    return &m_deviceRegistry;
}

int OnvifController::sendProb() {
    iDebug() << Q_FUNC_INFO;

    //int res = m_discoveryObj->sendProb("", "onvif://www.onvif.org/type/NetworkVideoTransmitter", "tdn:NetworkVideoTransmitter");
    m_discoveryObj->sendBye();
    int res = m_discoveryObj->sendProb();
    iDebug() << "prob" << res;
    return res;
}

void OnvifController::onDiscoveredDevice(DescDevice dev) {
    qDebug() << "\n**********************On dev found********************";
    qDebug() << "Dev found = " << dev.xAddrs;
    qDebug() << "Dev found scope = " << dev.scopes;

    QString deviceId = m_deviceRegistry.registerDevice(DeviceRegistry::extractId(dev.xAddrs));

    Device::DeviceInfo deviceInfo = Device::getDeviceInformation(dev.xAddrs);
    m_deviceRegistry.addDeviceInfo(deviceId, deviceInfo);

    QList<Device::DeviceServiceInfo> deviceServices = Device::getServices(dev.xAddrs);
    m_deviceRegistry.addDeviceServiceInfo(deviceId, deviceServices);

    QStringList profileTokens = Media::getProfileTokens(dev.xAddrs);
    m_deviceRegistry.addProfileTokens(deviceId, profileTokens);

    Q_EMIT(deviceAdded(deviceId));
}

PTZ::PtzStatusInfo OnvifController::getPTZStatus(QString deviceId) {
    qDebug() << "Sending get status";

    QString ptzServiceUrl = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::PTZ_SERVICE);
    QStringList profileTokens = m_deviceRegistry.getProfileTokens(deviceId);

    PTZ::PtzStatusInfo statusInfo = PTZ::getStatus(ptzServiceUrl, profileTokens.at(0));

    return statusInfo;
}

bool OnvifController::relativeMove(QString deviceId, float x, float y, QString profileToken) {
    iDebug() << Q_FUNC_INFO << deviceId << x << y;

    QStringList profileTokens = m_deviceRegistry.getProfileTokens(deviceId);
    QString deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::PTZ_SERVICE);
    int index = profileTokens.indexOf(profileToken);

    if (index == -1) index = 0;         // take first
    return PTZ::relativeMove(deviceId, profileTokens.at(index), x, y);
}

bool OnvifController::continuousMove(QString deviceId, float x, float y, QString profileToken) {
    iDebug() << Q_FUNC_INFO << deviceId << x << y;

    QStringList profileTokens = m_deviceRegistry.getProfileTokens(deviceId);
    int index = profileTokens.indexOf(profileToken);
    if (index == -1) index = 0;         // take first

    QString deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::PTZ_SERVICE);
    return PTZ::continuousMove(deviceServiceId, profileTokens.at(index), x, y);
}

bool OnvifController::stop(QString deviceId) {
    iDebug() << Q_FUNC_INFO << deviceId;

    QString deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::PTZ_SERVICE);
    return PTZ::stop(deviceServiceId);
}

QString OnvifController::getStreamUrl(QString deviceId, QString profileToken) {
    iDebug() << Q_FUNC_INFO << deviceId << profileToken;

    QStringList profileTokens = m_deviceRegistry.getProfileTokens(deviceId);
    int index = profileTokens.indexOf(profileToken);
    if (index == -1) index = 0;         // take first

    QString deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::MEDIA_SERVICE);
    return Media::GetStreamUri(deviceServiceId, profileToken);
}

bool OnvifController::subscribeMotionEvent(QString deviceId) {
    iDebug() << Q_FUNC_INFO << deviceId;

    QString deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::EVENT_SERVICE);
    Event::getGetServiceCapabilities(deviceServiceId);

    deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::ANALYTICS_SERVICE);
    Analytics::getGetServiceCapabilities(deviceServiceId);

    deviceServiceId = m_deviceRegistry.getServiceUrl(deviceId, DeviceRegistry::ANALYTICS_SERVICE);
    Analytics::getAnalyticsModules(deviceServiceId);

    return true;
}
