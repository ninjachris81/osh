# osh
Open Smart Home

I hate to have individual ecosystems for each of my smart home peripherals.
This project is a central system which connects to all of my devices and feeds them into a single MQTT bus.

Frontends:
Android
Web-based for backend and datamodel (TBD)

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

- check preconditions (Qt5.12+)
- clone
- git submodule update --init
