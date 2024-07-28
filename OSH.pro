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
    DoorAudioController \
    DoorAudioService \
    DoorCameraController \
    DoorCameraService \
    DoorUnlockController \
    DoorUnlockService \
    GPIOInputTest \
    GPIOWaterMeterController \
    GPIOWaterMeterService \
    HomeConnectController \
    HomeConnectService \
    KMTronicRelayController \
    KMTronicRelayService \
    GPIOInputController \
    GPIOInputService \
    OBISController \
    OBISService \
    OnvifController \
    OnvifService \
    PJSIPSupport \
    QMqttCommunicationManager \
    RS232WaterMeterController \
    RS232WaterMeterService \
    RS485EnergyMeterController \
    RS485EnergyMeterService \
    RS485RelayController \
    RS485RelayService \
    ScriptingTestService \
    ShutterController \
    ShutterService \
    TestService \
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

GPIOInputController.depends = Core
GPIOInputService.depends = Core GPIOInputController QMqttCommunicationManager
GPIOInputTest.depends = Core GPIOInputController QMqttCommunicationManager

AudioController.depends = Core
AudioService.depends = Core AudioController QMqttCommunicationManager

RS485RelayController.depends = Core CoreSerial
RS485RelayService.depends = Core RS485RelayController QMqttCommunicationManager

WBB12Controller.depends = Core CoreSerial
WBB12Service.depends = Core WBB12Controller QMqttCommunicationManager

DoorAudioController.depends = Core PJSIPSupport
DoorAudioService.depends = Core DoorAudioController PJSIPSupport QMqttCommunicationManager

DoorInputController.depends = Core
DoorInputService.depends = Core DoorInputController QMqttCommunicationManager

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

RS232WaterMeterController.depends = Core CoreSerial
RS232WaterMeterService.depends = Core CoreSerial RS232WaterMeterController QMqttCommunicationManager

RS485EnergyMeterController.depends = Core CoreSerial
RS485EnergyMeterService.depends = Core CoreSerial RS485EnergyMeterController QMqttCommunicationManager

DoorCameraController.depends = Core
DoorCameraService.depends = Core DoorCameraController QMqttCommunicationManager

GPIOWaterMeterController.depends = Core
GPIOWaterMeterService.depends = Core GPIOWaterMeterController QMqttCommunicationManager
