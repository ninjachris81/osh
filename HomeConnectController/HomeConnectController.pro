#-------------------------------------------------
#
# Project created by QtCreator 2021-11-02T12:47:15
#
#-------------------------------------------------

QT -= gui
QT += network
QT += xmlpatterns


TARGET = HomeConnectController
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += MAKE_SHARED_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    homeconnectcontroller.cpp

HEADERS += \
    homeconnectcontroller.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CoreSerial/release/ -lCoreSerial
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CoreSerial/debug/ -lCoreSerial
else:unix: LIBS += -L$$OUT_PWD/../CoreSerial/ -lCoreSerial

INCLUDEPATH += $$PWD/../CoreSerial
DEPENDPATH += $$PWD/../CoreSerial
