QT -= gui
QT += mqtt serialport


CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../KMTronicRelayController/release/ -lKMTronicRelayController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../KMTronicRelayController/debug/ -lKMTronicRelayController
else:unix: LIBS += -L$$OUT_PWD/../KMTronicRelayController/ -lKMTronicRelayController

INCLUDEPATH += $$PWD/../KMTronicRelayController
DEPENDPATH += $$PWD/../KMTronicRelayController

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreSerial/release/ -lCoreSerial
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreSerial/debug/ -lCoreSerial
else:unix: LIBS += -L$$OUT_PWD/../CoreSerial/ -lCoreSerial

INCLUDEPATH += $$PWD/../CoreSerial
DEPENDPATH += $$PWD/../CoreSerial

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreSerial/release/libCoreSerial.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreSerial/debug/libCoreSerial.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreSerial/release/CoreSerial.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CoreSerial/debug/CoreSerial.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CoreSerial/libCoreSerial.a
