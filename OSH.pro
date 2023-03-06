TEMPLATE = subdirs

SUBDIRS += \
    AudioController \
    AudioService \
    Core \
    CoreProcessorJS \
    CoreSerial \
    CoreServer \
    CoreService \
    CoreServiceSimulator \
    CoreSimulation \
    CoreUI \
    DoorUnlockController \
    DoorUnlockService \
    HomeConnectController \
    HomeConnectService \
    KMTronicRelayController \
    KMTronicRelayService \
    MCP23017InputController \
    MCP23017InputService \
    OBISController \
    OBISService \
    OnvifController \
    OnvifService \
    QMqttCommunicationManager \
    RS485RelayController \
    RS485RelayService \
    ShutterController \
    ShutterService \
    WBB12Controller \
    WBB12Service \
    qtmqtt

CoreService.depends = Core CoreServer QMqttCommunicationManager
CoreUI.depends = Core CoreServer CoreSimulation QMqttCommunicationManager
CoreServer.depends = Core
CoreSimulation.depends = Core CoreServer QMqttCommunicationManager
CoreServiceSimulator.depends = Core CoreServer CoreSimulation QMqttCommunicationManager

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

DoorUnlockController.depends = Core
DoorUnlockService.depends = Core DoorUnlockController QMqttCommunicationManager

OBISController.depends = Core CoreSerial
OBISService.depends = Core OBISController QMqttCommunicationManager

OnvifController.depends = Core
OnvifService.depends = Core OnvifController QMqttCommunicationManager

ShutterController.depends = Core
ShutterService.depends = Core ShutterController QMqttCommunicationManager

HomeConnectController.depends = Core
HomeConnectService.depends = Core HomeConnectController QMqttCommunicationManager
