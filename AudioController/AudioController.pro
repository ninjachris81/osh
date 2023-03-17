QT -= gui
QT += multimedia

TARGET = AudioController
TEMPLATE = lib
#CONFIG += staticlib

DEFINES += MAKE_SHARED_LIB

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        amixervolumewrapper.cpp \
        aplayprocesswrapper.cpp \
        audiocontroller.cpp \
        audiocontroller2.cpp \
        audiofiledevice.cpp \
        audiooutputwrapper.cpp \
        audioplaylistdevice.cpp \
        audioprocesswrapperbase.cpp \
        audiostreamdevice.cpp \
        mpg123processwrapper.cpp

HEADERS += \
    amixervolumewrapper.h \
    aplayprocesswrapper.h \
    audiocontroller.h \
    audiocontroller2.h \
    audiofiledevice.h \
    audiooutputwrapper.h \
    audioplaylistdevice.h \
    audioprocesswrapperbase.h \
    audiostreamdevice.h \
    mpg123processwrapper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

