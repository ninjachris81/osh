#-------------------------------------------------
#
# Project created by QtCreator 2021-11-15T23:04:39
#
#-------------------------------------------------

QT       += qml sql

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
        datamodel/server/datamodelbase.cpp \
        datamodel/server/datamodelloaderbase.cpp \
        datamodel/server/datamodelmanager.cpp \
        datamodel/server/dynamicdatamodel.cpp \
    datamodel/server/emptydatamodel.cpp \
    datamodel/server/filedatamodelloader.cpp \
        datamodel/server/httpdatamodelloader.cpp \
    datamodel/server/meta/knownroom.cpp \
        datamodel/server/testdatamodel.cpp \
        datamodel/server/testdatamodelloader.cpp \
        device/server/serverdevicediscoverymanager.cpp \
    processor/server/commonscripts.cpp \
    processor/server/localstorage.cpp \
    processor/server/scriptbase.cpp \
        time/server/systemtimemanager.cpp \
        value/server/environmentvaluemanager.cpp \
        value/server/servervaluemanager.cpp \
        device/server/devicediscoverymodelbridge.cpp \
        processor/server/modelprocessormanager.cpp \
        processor/server/processortask.cpp

HEADERS += \
        datamodel/server/datamodelbase.h \
        datamodel/server/datamodelloaderbase.h \
        datamodel/server/datamodelmanager.h \
        datamodel/server/dynamicdatamodel.h \
    datamodel/server/emptydatamodel.h \
    datamodel/server/filedatamodelloader.h \
        datamodel/server/httpdatamodelloader.h \
    datamodel/server/meta/knownroom.h \
        datamodel/server/testdatamodel.h \
        datamodel/server/testdatamodelloader.h \
        device/server/serverdevicediscoverymanager.h \
    processor/server/commonscripts.h \
    processor/server/localstorage.h \
    processor/server/scriptbase.h \
    sharedlib.h \
        time/server/systemtimemanager.h \
        value/server/environmentvaluemanager.h \
        value/server/servervaluemanager.h \
        device/server/devicediscoverymodelbridge.h \
        processor/server/modelprocessormanager.h \
        processor/server/processortask.h

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

RESOURCES +=
