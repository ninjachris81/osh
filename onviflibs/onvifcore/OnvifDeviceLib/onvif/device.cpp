#include "device.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include "soap/onvifdeviceDeviceBindingProxy.h"
#include "soap/onvifdevice.nsmap"


Device::Device()
{

}

Device::~Device()
{

}


Device::DeviceInfo Device::getDeviceInformation(QString devServiceURL) {

    qDebug() << "device manager service test: getDeviceInformation";

    DeviceBindingProxy d;

    _devicews__GetDeviceInformation in;
    _devicews__GetDeviceInformationResponse out;

    DeviceInfo deviceInfo;

    if (d.GetDeviceInformation(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << (char*)out.soap->data;

        deviceInfo.deviceFirmwareVersion = QString::fromStdString(out.FirmwareVersion.data());
        deviceInfo.deviceSerialNumber = QString::fromStdString(out.SerialNumber.data());
        deviceInfo.deviceHardwareId = QString::fromStdString(out.HardwareId.data());
        deviceInfo.deviceManufacturer = QString::fromStdString(out.Manufacturer.data());
    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return deviceInfo;
}

void Device::getUsers(QString devServiceURL) {

    qDebug() << "device manager service test: getUses";

    DeviceBindingProxy d;

    _devicews__GetUsers in;
    _devicews__GetUsersResponse out;


    if (d.GetUsers(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        std::vector<tt__User *> users = out.User;

        qDebug() << users.size();
        for(int i = 0; i< users.size(); i++){
            tt__User * u = users.at(i);
            qDebug() << u->Username.data();
            qDebug() << u->Password;
        }

    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return ;
}

QList<Device::DeviceServiceInfo> Device::getServices(QString devServiceURL) {
    qDebug() << "device manager service test: getServices";
    QList<DeviceServiceInfo> returnList;

    DeviceBindingProxy d;

    _devicews__GetServices in;
    _devicews__GetServicesResponse out;


    if (d.GetServices(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        std::vector<devicews__Service *> services = out.Service;

        qDebug() << services.size();
        for(int i = 0; i<services.size(); i++){
            devicews__Service *s = services.at(i);

            qDebug() << s->XAddr.data();
            qDebug() << s->Namespace.data();

            DeviceServiceInfo info;

            info.deviceXAddr = QString::fromStdString(s->XAddr.data());
            info.deviceNamespace = QString::fromStdString(s->Namespace.data());

            returnList.append(info);

        }

    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return returnList;
}
