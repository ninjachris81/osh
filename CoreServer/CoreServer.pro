#-------------------------------------------------
#
# Project created by QtCreator 2021-11-15T23:04:39
#
#-------------------------------------------------

#DEFINES += PROCESSOR_JS_SUPPORT

QT       += sql
QT       += network
QT       -= gui

TARGET = CoreServer
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += MAKE_SHARED_LIB

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
    actor/server/togglecontroller.cpp \
    device/server/serverdevicediscoverymanager.cpp \
    processor/server/3rdparty/sunset.cpp \
    processor/server/advancedscripts.cpp \
    processor/server/basicscripts.cpp \
    processor/server/commonscripts.cpp \
    processor/server/localstorage.cpp \
    processor/server/nativeprocessorexecutor.cpp \
    processor/server/nativeprocessortask.cpp \
    processor/server/processorexecutorbase.cpp \
    processor/server/scriptbase.cpp \
    time/server/systemtimemanager.cpp \
    value/server/environmentvaluemanager.cpp \
    value/server/servervaluemanager.cpp \
    device/server/devicediscoverymodelbridge.cpp \
    processor/server/modelprocessormanager.cpp

HEADERS += \
    actor/server/togglecontroller.h \
    device/server/serverdevicediscoverymanager.h \
    processor/server/3rdparty/sunset.h \
    processor/server/advancedscripts.h \
    processor/server/basicscripts.h \
    processor/server/commonscripts.h \
    processor/server/localstorage.h \
    processor/server/nativeprocessorexecutor.h \
    processor/server/nativeprocessortask.h \
    processor/server/processorexecutorbase.h \
    processor/server/scriptbase.h \
    processor/server/threadsafeqjsengine.h \
    sharedlib.h \
    time/server/systemtimemanager.h \
    value/server/environmentvaluemanager.h \
    value/server/servervaluemanager.h \
    device/server/devicediscoverymodelbridge.h \
    processor/server/modelprocessormanager.h

contains(DEFINES, PROCESSOR_JS_SUPPORT) {
    QT       += qml

    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreProcessorJS/release/ -lCoreProcessorJS
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreProcessorJS/debug/ -lCoreProcessorJS
    else:unix: LIBS += -L$$OUT_PWD/../CoreProcessorJS/ -lCoreProcessorJS

    INCLUDEPATH += $$PWD/../CoreProcessorJS
    DEPENDPATH += $$PWD/../CoreProcessorJS
}


unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

