#!/usr/bin/env bash

# @see osh.pro

function buildQtMqtt {
   cd "$OSH_ROOT/qtmqtt"
   echo "Building QtMqtt in $PWD"
   qmake
   make -j$MAKE_CORE_COUNT
   make install
}

function buildWiringPi {
   cd "$OSH_ROOT/WiringPi"
   echo "Building WiringPi in $PWD"
   ./build
}

function buildPjProject {
   cd "$OSH_ROOT/pjproject"
   echo "Configure PJ Project in $PWD"
   ./configure --disable-libwebrtc --enable-shared
   cd "$OSH_ROOT/pjproject"
   echo "Building PJ Project in $PWD"
   make dep
   make
}

function buildOSHLib {
    cd "$OSH_ROOT/$1"
    echo "Building lib in $PWD"
    qmake
    make -j$MAKE_CORE_COUNT
    make install
}

function buildOSHTarget {
   cd "$OSH_ROOT/$1"
   echo "Building target in $PWD"
   qmake
   make -j$MAKE_CORE_COUNT
}

function printInfos {
   echo "OSH Root: $OSH_ROOT"
   echo "Make cores: $MAKE_CORE_COUNT"
   echo "Building $BUILD_TARGET..."
}

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
	exit 1
fi

RPI_MODEL="$(tr -d '\0' </proc/device-tree/model)"
case $RPI_MODEL in
   *Zero*		)
      MAKE_CORE_COUNT=1
      ;;
   *			)
      MAKE_CORE_COUNT=4
      ;;
esac

OSH_ROOT="$(dirname "$(cd .. && pwd)")"
BUILD_TARGET="Unknown"

case "$1" in
   AudioService		)
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "AudioController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   CoreService		)
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreServer"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   CoreUI		)
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreServer"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   KMTronicRelayService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreSerial"
      buildOSHLib "KMTronicRelayController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   GPIOInputService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
	  buildWiringPi
      buildOSHLib "Core"
      buildOSHLib "GPIOInputController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   ShutterService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "ShutterController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   WBB12Service )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreSerial"
      buildOSHLib "WBB12Controller"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   OBISService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreSerial"
      buildOSHLib "OBISController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   RS485RelayService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreSerial"
      buildOSHLib "RS485RelayController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   RS485EnergyMeterService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "CoreSerial"
      buildOSHLib "RS485EnergyMeterController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   DoorAudioService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
	  buildPjProject
      buildOSHLib "PJSIPSupport"
      buildOSHLib "DoorAudioController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   DoorUnlockService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
	  buildWiringPi
      buildOSHLib "Core"
      buildOSHLib "DoorUnlockController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   DoorCameraService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "DoorCameraController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   GPIOWaterMeterService )
      BUILD_TARGET=$1
      printInfos
      buildQtMqtt
      buildOSHLib "Core"
      buildOSHLib "GPIOInputController"
      buildOSHLib "GPIOWaterMeterController"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHTarget $BUILD_TARGET
      ;;
   *			)
      ;;
esac

if [ "$BUILD_TARGET" = "Unknown" ]
   then
      echo "Invalid build target"
         exit 2
fi
