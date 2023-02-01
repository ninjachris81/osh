QT -= gui
QT += mqtt sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DoorUnlockController/release/ -lDoorUnlockController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DoorUnlockController/debug/ -lDoorUnlockController
else:unix: LIBS += -L$$OUT_PWD/../WBB12Controller/ -lDoorUnlockController

INCLUDEPATH += $$PWD/../DoorUnlockController
DEPENDPATH += $$PWD/../DoorUnlockController

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/release/ -lQMqttCommunicationManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/debug/ -lQMqttCommunicationManager
else:unix: LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/ -lQMqttCommunicationManager

INCLUDEPATH += $$PWD/../QMqttCommunicationManager
DEPENDPATH += $$PWD/../QMqttCommunicationManager

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DoorUnlockController/release/ -lDoorUnlockController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DoorUnlockController/debug/ -lDoorUnlockController
else:unix: LIBS += -L$$OUT_PWD/../DoorUnlockController/ -lDoorUnlockController

INCLUDEPATH += $$PWD/../DoorUnlockController
DEPENDPATH += $$PWD/../DoorUnlockController
