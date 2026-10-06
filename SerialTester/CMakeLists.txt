cmake_minimum_required(VERSION 3.16)

project(SerialTester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatische MOC-Verarbeitung aktivieren
set(CMAKE_AUTOMOC ON)

# 1. Qt-Pakete suchen (funktioniert für Qt5 und Qt6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort)

add_executable(SerialTester main.cpp)

# 2. Bibliotheken linken
target_link_libraries(SerialTester PRIVATE 
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
)
