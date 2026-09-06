# osh
Open Smart Home

I hate to have individual ecosystems for each of my smart home peripherals.
This project is a central system which connects to all of my devices and feeds them into a single MQTT bus.

It's the underlying layer beneath logic layer like openHAB.

Frontends:
Android
Web-based for backend and datamodel
https://github.com/ninjachris81/osh_apps

Current HW setup:

Room Sensors (ESP32)
Heat pump (WBB12, Modbus TCP)
Relay (Chinese RS485 based)
Core Server (OrangePi)
Server Extensions (RPI Zero)
Surveillance Cam (Onvif based)
Energy meter (Mobis based)

Upcoming:
Home Connect devices
Solar Equipment


**********************
BUILDING
**********************

- Preconditions: CMake 3.16+, a C++17 compiler, and Qt 6.8 with the modules used by the project.
- Initialize the required submodules:

	`git submodule update --init --recursive`

- Build and install the Qt 6.8 qtmqtt submodule:

	`cmake -S qtmqtt -B qtmqtt-build -G Ninja -DCMAKE_PREFIX_PATH=D:/Qt2/6.8.3/mingw_64 -DCMAKE_INSTALL_PREFIX=$PWD/qtmqtt-install`

	`cmake --build qtmqtt-build --parallel`

	`cmake --install qtmqtt-build`

- Configure and build:

	`cmake -S . -B build`

	`cmake --build build --parallel`

	On Windows, set `CMAKE_PREFIX_PATH` to the installed Qt kit, for example:

	`cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=D:/Qt2/6.8.3/mingw_64`

	Install the Qt 6.8 `Multimedia`, `Mqtt`, `SerialBus`, and `SerialPort` add-on modules, and use the compiler shipped for the same Qt MinGW kit.
