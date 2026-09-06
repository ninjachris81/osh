cmake_minimum_required(VERSION 3.16)

project(OSH LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(OSH_QT_ROOT "D:/Qt2/5.15.2/mingw81_64" CACHE PATH "Qt 5 installation used by OSH")
if(EXISTS "${OSH_QT_ROOT}/lib/cmake/Qt5/Qt5Config.cmake")
    list(PREPEND CMAKE_PREFIX_PATH "${OSH_QT_ROOT}")
endif()

find_package(Qt5 5.12 REQUIRED COMPONENTS
    Core Multimedia Network Qml Quick SerialBus SerialPort Sql XmlPatterns
)
find_package(Qt5 5.12 QUIET COMPONENTS Mqtt)

include(cmake/OSHProject.cmake)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qtmqtt/CMakeLists.txt")
    add_subdirectory(qtmqtt)
elseif(NOT TARGET Qt5::Mqtt)
    message(FATAL_ERROR "Qt5::Mqtt is unavailable; initialize qtmqtt with git submodule update --init --recursive")
endif()

add_subdirectory(Core)
add_subdirectory(CoreProcessorJS)
add_subdirectory(CoreSerial)
add_subdirectory(CoreServer)
add_subdirectory(CoreSimulation)
add_subdirectory(CoreUI)
add_subdirectory(PJSIPSupport)
add_subdirectory(QMqttCommunicationManager)
add_subdirectory(onviflibs)

add_subdirectory(AudioController)
add_subdirectory(DoorAudioController)
add_subdirectory(DoorCameraController)
add_subdirectory(DoorUnlockController)
add_subdirectory(GPIOInputController)
add_subdirectory(GPIOWaterMeterController)
add_subdirectory(HomeConnectController)
add_subdirectory(KMTronicRelayController)
add_subdirectory(OBISController)
add_subdirectory(OnvifController)
add_subdirectory(RS232InputController)
add_subdirectory(RS232WaterMeterController)
add_subdirectory(RS485EnergyMeterController)
add_subdirectory(RS485RelayController)
add_subdirectory(ShutterController)
add_subdirectory(WBB12Controller)

add_subdirectory(AudioService)
add_subdirectory(CoreService)
add_subdirectory(CoreServiceSimulator)
add_subdirectory(DoorAudioService)
add_subdirectory(DoorCameraService)
add_subdirectory(DoorUnlockService)
add_subdirectory(GPIOInputService)
add_subdirectory(GPIOInputTest)
add_subdirectory(GPIOWaterMeterService)
add_subdirectory(HomeConnectService)
add_subdirectory(KMTronicRelayService)
add_subdirectory(OBISService)
add_subdirectory(OnvifService)
add_subdirectory(RS232InputService)
add_subdirectory(RS232WaterMeterService)
add_subdirectory(RS485EnergyMeterService)
add_subdirectory(RS485RelayService)
add_subdirectory(ScriptingTestService)
add_subdirectory(ShutterService)
add_subdirectory(TestService)
add_subdirectory(WBB12Service)

if(UNIX)
    install(TARGETS
        AudioController AudioService Core CoreProcessorJS CoreSerial CoreServer
        CoreService CoreServiceSimulator CoreSimulation CoreUI DoorAudioController
        DoorAudioService DoorCameraController DoorCameraService DoorUnlockController
        DoorUnlockService GPIOInputController GPIOInputService GPIOInputTest
        GPIOWaterMeterController GPIOWaterMeterService HomeConnectController
        HomeConnectService KMTronicRelayController KMTronicRelayService OBISController
        OBISService OnvifController OnvifService PJSIPSupport QMqttCommunicationManager
        RS232InputController RS232InputService RS232WaterMeterController
        RS232WaterMeterService RS485EnergyMeterController RS485EnergyMeterService
        RS485RelayController RS485RelayService ScriptingTestService ShutterController
        ShutterService TestService WBB12Controller WBB12Service
        OnvifAnalyticsLib OnvifDeviceIOLib OnvifDisplayLib OnvifImagingLib OnvifMediaLib
        OnvifPTZLib OnvifReceiverLib OnvifRecordingControlLib OnvifRecordingSearchLib
        OnvifReplayControlLib OnvifVideoAnalyticsDeviceLib OnvifDeviceLib
        OnvifDiscoveryLib OnvifEventLib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()