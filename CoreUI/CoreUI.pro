QT += quick

QT += mqtt

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += IS_OSH_UI

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        datamodel/datamodelbaseui.cpp \
        datamodel/datamodelmanagerui.cpp \
        device/devicebaseui.cpp \
        device/devicediscoverymanagerui.cpp \
        identifyableui.cpp \
        main.cpp \
        processor/processortaskui.cpp \
        value/valuemanagerui.cpp

RESOURCES += qml.qrc \
    qml_components.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

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

HEADERS += \
    datamodel/datamodelbaseui.h \
    datamodel/datamodelmanagerui.h \
    device/devicebaseui.h \
    device/devicediscoverymanagerui.h \
    identifyableui.h \
    processor/processortaskui.h \
    value/valuemanagerui.h