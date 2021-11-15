TEMPLATE = subdirs

SUBDIRS += \
    Core \
    CoreSerial \
    CoreServer \
    CoreService \
    CoreUI \
    KMTronicRelayController \
    KMTronicRelayService \
    QMqttCommunicationManager \
    qmqtt

CoreService.depends = Core CoreServer QMqttCommunicationManager
CoreUI.depends = Core CoreServer QMqttCommunicationManager
QMqttCommunicationManager.depends = qmqtt Core
KMTronicRelayController.depends = Core CoreSerial
KMTronicRelayService.depends = Core CoreSerial KMTronicRelayController QMqttCommunicationManager
CoreServer.depends = Core
