#-------------------------------------------------
#
# Project created by QtCreator 2021-11-02T12:37:06
#
#-------------------------------------------------

QT      -= gui
QT      += mqtt qml sql

TARGET = CoreSimulation
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += IS_OSH_CORE_SERVICE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller/audiocontrollersimulator.cpp \
        controller/digitalinputcontrollersimulator.cpp \
        controller/relaycontrollersimulator.cpp \
        simulation/simulator.cpp \
        time/client/clientsystemtimemanagersimulator.cpp \
        time/server/systemtimemanagersimulator.cpp

HEADERS += \
        controller/audiocontrollersimulator.h \
        controller/digitalinputcontrollersimulator.h \
        controller/relaycontrollersimulator.h \
        simulation/simulator.h \
        time/client/clientsystemtimemanagersimulator.h \
        time/server/systemtimemanagersimulator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Core/release/libCore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Core/debug/libCore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Core/release/Core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Core/debug/Core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Core/libCore.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreServer/release/ -lCoreServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreServer/debug/ -lCoreServer
else:unix: LIBS += -L$$OUT_PWD/../CoreServer/ -lCoreServer

INCLUDEPATH += $$PWD/../CoreServer
DEPENDPATH += $$PWD/../CoreServer

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreServer/release/libCoreServer.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreServer/debug/libCoreServer.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreServer/release/CoreServer.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreServer/debug/CoreServer.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CoreServer/libCoreServer.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/release/ -lQMqttCommunicationManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/debug/ -lQMqttCommunicationManager
else:unix: LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/ -lQMqttCommunicationManager

INCLUDEPATH += $$PWD/../QMqttCommunicationManager
DEPENDPATH += $$PWD/../QMqttCommunicationManager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QMqttCommunicationManager/release/libQMqttCommunicationManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QMqttCommunicationManager/debug/libQMqttCommunicationManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QMqttCommunicationManager/release/QMqttCommunicationManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QMqttCommunicationManager/debug/QMqttCommunicationManager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QMqttCommunicationManager/libQMqttCommunicationManager.a
