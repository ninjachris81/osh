QT -= gui

QT += mqtt qml sql

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

DEFINES += IS_OSH_CORE_SERVICE

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreServer/release/ -lCoreServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreServer/debug/ -lCoreServer
else:unix: LIBS += -L$$OUT_PWD/../CoreServer/ -lCoreServer

INCLUDEPATH += $$PWD/../CoreServer
DEPENDPATH += $$PWD/../CoreServer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreSimulation/release/ -lCoreSimulation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreSimulation/debug/ -lCoreSimulation
else:unix: LIBS += -L$$OUT_PWD/../CoreSimulation/ -lCoreSimulation

INCLUDEPATH += $$PWD/../CoreSimulation
DEPENDPATH += $$PWD/../CoreSimulation

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/release/ -lQMqttCommunicationManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/debug/ -lQMqttCommunicationManager
else:unix: LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/ -lQMqttCommunicationManager

INCLUDEPATH += $$PWD/../QMqttCommunicationManager
DEPENDPATH += $$PWD/../QMqttCommunicationManager
