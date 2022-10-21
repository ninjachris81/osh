QT -= gui
QT += serialport
QT += serialbus


TARGET = OBISController
TEMPLATE = lib
CONFIG += staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    obiscontroller.cpp \
    smlparser.cpp



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

HEADERS += \
    obiscontroller.h \
    smlparser.h
