QT -= gui
QT += serialport
QT += serialbus


TARGET = WBB12Controller
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += MAKE_SHARED_LIB

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    wbb12controller.cpp

HEADERS += \
    wbb12controller.h

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

