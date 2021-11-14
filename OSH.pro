TEMPLATE = subdirs

SUBDIRS += \
    Core \
    CoreSerial \
    CoreService \
    CoreUI \
    KMTronicRelayController \
    KMTronicRelayService \
    QMqttCommunicationManager \
    qmqtt

CoreService.depends = Core QMqttCommunicationManager
CoreUI.depends = Core QMqttCommunicationManager
QMqttCommunicationManager.depends = qmqtt Core
KMTronicRelayController.depends = Core CoreSerial
KMTronicRelayService.depends = Core CoreSerial KMTronicRelayController QMqttCommunicationManager
