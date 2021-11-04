TEMPLATE = subdirs

SUBDIRS += \
    Core \
    CoreSerial \
    CoreService \
    KMTronicRelayController \
    KMTronicRelayService \
    QMqttCommunicationManager \
    qmqtt

CoreService.depends = Core QMqttCommunicationManager
QMqttCommunicationManager.depends = qmqtt Core
KMTronicRelayController.depends = Core CoreSerial
KMTronicRelayService.depends = Core CoreSerial KMTronicRelayController QMqttCommunicationManager
