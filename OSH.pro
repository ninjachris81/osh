TEMPLATE = subdirs

SUBDIRS += \
    AudioController \
    AudioService \
    Core \
    CoreSerial \
    CoreServer \
    CoreService \
    CoreUI \
    KMTronicRelayController \
    KMTronicRelayService \
    MCP23017InputController \
    MCP23017InputService \
    OBISController \
    OBISService \
    QMqttCommunicationManager \
    RS485RelayController \
    RS485RelayService \
    WBB12Controller \
    WBB12Service \
    qtmqtt

CoreService.depends = Core CoreServer QMqttCommunicationManager
CoreUI.depends = Core CoreServer QMqttCommunicationManager
CoreServer.depends = Core

QMqttCommunicationManager.depends = qtmqtt Core

KMTronicRelayController.depends = Core CoreSerial
KMTronicRelayService.depends = Core CoreSerial KMTronicRelayController QMqttCommunicationManager

MCP23017InputController.depends = Core
MCP23017InputService.depends = Core MCP23017InputController QMqttCommunicationManager

AudioController.depends = Core
AudioService.depends = Core AudioController QMqttCommunicationManager

RS485RelayController.depends = Core CoreSerial
RS485RelayService.depends = Core RS485RelayController QMqttCommunicationManager

WBB12Controller.depends = Core CoreSerial
WBB12Service.depends = Core WBB12Controller QMqttCommunicationManager

OBISController.depends = Core CoreSerial
OBISService.depends = Core OBISController QMqttCommunicationManager
