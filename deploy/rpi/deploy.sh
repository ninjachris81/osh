#!/usr/bin/env bash

function buildQMqtt {
   echo "Building QMqtt in $PWD"
   cd $OSH_ROOT/qmqtt
   qmake
   make -j$MAKE_CORE_COUNT
   make install
}

function buildOSHLib {
    cd $OSH_ROOT/$1
    echo "Building lib in $PWD"
    qmake
    #make -j$MAKE_CORE_COUNT
    #make install
}

function buildOSHTarget {
   cd $OSH_ROOT/$1
   echo "Building target in $PWD"
   qmake
   #make -j$MAKE_CORE_COUNT
}

function printInfos {
   echo "OSH Root: $OSH_ROOT"
   echo "Make cores: $MAKE_CORE_COUNT"
   echo "Building $BUILD_TARGET..."
}

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
	exit 1
fi

RPI_MODEL="$(tr -d '\0' </proc/device-tree/model)"
case $RPI_MODEL in
   *Zero*		)
      MAKE_CORE_COUNT=2
      ;;
   *			)
      MAKE_CORE_COUNT=4
      ;;
esac

OSH_ROOT="$(dirname "$(cd .. && pwd)")"
BUILD_TARGET="Unknown"

case "$1" in
   CoreService		)
      BUILD_TARGET=$1
      printInfos
      buildQMqtt
      buildOSHLib "Core"
      buildOSHLib "QMqttCommunicationManager"
      buildOSHLib "CoreServer"
      buildOSHTarget "CoreService"
      ;;
   *			)
      ;;
esac

if [ "$BUILD_TARGET" = "Unknown" ]
   then
      echo "Invalid build target"
         exit 2
fi
