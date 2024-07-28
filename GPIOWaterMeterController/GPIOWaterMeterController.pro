QT -= gui

TARGET = GPIOWaterMeterController
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += MAKE_SHARED_LIB

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gpiowatermetercontroller.cpp

HEADERS += \
    gpiowatermetercontroller.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GPIOInputController/release/ -lGPIOInputController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GPIOInputController/debug/ -lGPIOInputController
else:unix: LIBS += -L$$OUT_PWD/../GPIOInputController/ -lGPIOInputController

INCLUDEPATH += $$PWD/../GPIOInputController
DEPENDPATH += $$PWD/../GPIOInputController

# wiringpi will not be maintained any longer
unix: LIBS += -I/usr/local/include -L/usr/local/lib -lwiringPi

