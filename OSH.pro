TEMPLATE = subdirs

SUBDIRS += \
    Core \
    CoreSerial \
    CoreServer \
    CoreService \
    CoreUI \
    KMTronicRelayController \
    KMTronicRelayService \
    MCP23017InputController \
    MCP23017InputService \
    QMqttCommunicationManager \
    qtmqtt

CoreService.depends = Core CoreServer QMqttCommunicationManager
CoreUI.depends = Core CoreServer QMqttCommunicationManager
CoreServer.depends = Core

QMqttCommunicationManager.depends = qtmqtt Core

KMTronicRelayController.depends = Core CoreSerial
KMTronicRelayService.depends = Core CoreSerial KMTronicRelayController QMqttCommunicationManager

MCP23017InputController.depends = Core
MCP23017InputService.depends = Core MCP23017InputController QMqttCommunicationManager
