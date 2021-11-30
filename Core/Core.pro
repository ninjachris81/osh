#-------------------------------------------------
#
# Project created by QtCreator 2021-11-02T12:37:06
#
#-------------------------------------------------

QT      -= gui
QT      += qml

TARGET = Core
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += IS_OSH_CORE_SERVICE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        actor/actorbase.cpp \
        actor/actormessage.cpp \
        actor/audioplaybackactor.cpp \
        actor/client/clientactormanager.cpp \
        actor/digitalactor.cpp \
        communication/communicationmanagerbase.cpp \
        controller/controllermanager.cpp \
        controller/controllermessage.cpp \
        controller/digitalinputcontrollerbase.cpp \
        controller/filegpiocontroller.cpp \
        device/client/clientdevice.cpp \
        device/client/clientdevicemanager.cpp \
        communication/messagebase.cpp \
        communication/mqtt/mqttcommunicationmanagerbase.cpp \
        device/devicediscoverymanagerbase.cpp \
        device/knowndevice.cpp \
        log/httplogforwarder.cpp \
        log/logforwarderbase.cpp \
        log/logmanager.cpp \
        log/logmessage.cpp \
        processor/scriptresultmessage.cpp \
        time/client/clientsystemtimemanager.cpp \
        time/systemtimemessage.cpp \
        value/client/clientvaluemanager.cpp \
        value/longvalue.cpp \
        value/redundantvalue.cpp \
        value/valuemanagerbase.cpp \
        value/valuemessage.cpp \
        config/localconfig.cpp \
        controller/controllerbase.cpp \
        controller/relaycontrollerbase.cpp \
        device/devicebase.cpp \
        device/devicediscoverymessage.cpp \
        identifyable.cpp \
        manager/managerbase.cpp \
        manager/managerregistration.cpp \
        value/booleanvalue.cpp \
        value/doublevalue.cpp \
        value/enumvalue.cpp \
        value/integervalue.cpp \
        value/stringvalue.cpp \
        value/valuebase.cpp \
        value/valuegroup.cpp \
        warn/client/clientsystemwarningsmanager.cpp \
        warn/systemwarningmessage.cpp \
        warn/systemwarningsmanager.cpp

HEADERS += \
        actor/actorbase.h \
        actor/actormessage.h \
        actor/audioplaybackactor.h \
        actor/client/clientactormanager.h \
        actor/digitalactor.h \
        communication/communicationmanagerbase.h \
        controller/controllermanager.h \
        controller/controllermessage.h \
        controller/digitalinputcontrollerbase.h \
        controller/filegpiocontroller.h \
        device/client/clientdevice.h \
        device/client/clientdevicemanager.h \
        communication/messagebase.h \
        communication/mqtt/mqttcommunicationmanagerbase.h \
        device/devicediscoverymanagerbase.h \
        device/knowndevice.h \
        log/httplogforwarder.h \
        log/logforwarderbase.h \
        log/logmanager.h \
        log/logmessage.h \
        macros.h \
        processor/scriptresultmessage.h \
        shared/actor.h \
        shared/actor_qt.h \
        shared/controllercmdtypes.h \
        shared/controllercmdtypes_qt.h \
        shared/device.h \
        shared/log.h \
        shared/logging_categories.h \
        shared/logging_categories_qt.h \
        shared/mqtt_qt.h \
        shared/time.h \
        time/client/clientsystemtimemanager.h \
        time/systemtimemessage.h \
        value/client/clientvaluemanager.h \
        value/longvalue.h \
        value/redundantvalue.h \
        value/valuemanagerbase.h \
        value/valuemessage.h \
        config/localconfig.h \
        controller/controllerbase.h \
        controller/relaycontrollerbase.h \
        device/devicebase.h \
        device/devicediscoverymessage.h \
        identifyable.h \
        manager/managerbase.h \
        manager/managerregistration.h \
        shared/constants.h \
        shared/mqtt.h \
        value/booleanvalue.h \
        value/doublevalue.h \
        value/enumvalue.h \
        value/integervalue.h \
        value/stringvalue.h \
        value/valuebase.h \
        value/valuegroup.h \
        warn/client/clientsystemwarningsmanager.h \
        warn/systemwarningmessage.h \
        warn/systemwarningsmanager.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
