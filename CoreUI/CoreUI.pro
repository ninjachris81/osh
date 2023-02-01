QT += quick

QT += mqtt

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += MAKE_SHARED_LIB

DEFINES += IS_OSH_UI

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        actor/actorbaseui.cpp \
        connectoritembase.cpp \
        datamodel/datamodelbaseui.cpp \
        datamodel/datamodelmanagerui.cpp \
        datamodel/server/meta/knownroomui.cpp \
        device/devicebaseui.cpp \
        device/devicediscoverymanagerui.cpp \
        identifyableui.cpp \
        log/logentryui.cpp \
        log/logmanagerui.cpp \
        main.cpp \
        processor/modelprocessormanagerui.cpp \
        processor/processortaskui.cpp \
        value/valuebaseui.cpp \
        value/valuemanagerui.cpp \
        visualitembase.cpp

HEADERS += \
    actor/actorbaseui.h \
    connectoritembase.h \
    datamodel/datamodelbaseui.h \
    datamodel/datamodelmanagerui.h \
    datamodel/server/meta/knownroomui.h \
    device/devicebaseui.h \
    device/devicediscoverymanagerui.h \
    identifyableui.h \
    log/logentryui.h \
    log/logmanagerui.h \
    processor/modelprocessormanagerui.h \
    processor/processortaskui.h \
    value/valuebaseui.h \
    value/valuemanagerui.h \
    visualitembase.h

RESOURCES += qml.qrc \
    images.qrc \
    js.qrc \
    qml_components.qrc \
    ui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += qml
QML2_IMPORT_PATH += qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH += qml

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
