QT -= gui


TARGET = PJSIPSupport
TEMPLATE = lib
#CONFIG += staticlib

CONFIG += c++17
CONFIG -= app_bundle

DEFINES += MAKE_SHARED_LIB

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
    oshaccount.h \
    oshcall.h \
    oshendpoint.h \
    oshstatecallback.h \
    pjstubs.h

SOURCES += \
    oshaccount.cpp \
    oshcall.cpp \
    oshendpoint.cpp



unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

unix:!macx: DEFINES+=PJ_AUTOCONF=1
unix:!macx: PJ_BASE_DIR = /home/pi/pjproject

win32: DEFINES -= UNICODE
win32: PJ_BASE_DIR = ../../pjproject
win32: DEFINES += PJ_USE_STUBS

message($${PJ_BASE_DIR})

unix:!macx {
    LIBS += -L$${PJ_BASE_DIR}/pjsip/lib/ -lpjsip
    LIBS += -L$${PJ_BASE_DIR}/pjsip/lib/ -lpjsip-simple
    LIBS += -L$${PJ_BASE_DIR}/pjsip/lib/ -lpjsua2
    LIBS += -L$${PJ_BASE_DIR}/pjsip/lib/ -lpjsua
    LIBS += -L$${PJ_BASE_DIR}/pjsip/lib/ -lpjsip-ua
    LIBS += -L$${PJ_BASE_DIR}/pjlib/lib/ -lpj
    LIBS += -L$${PJ_BASE_DIR}/pjlib-util/lib/ -lpjlib-util
    LIBS += -L$${PJ_BASE_DIR}/pjmedia/lib/ -lpjmedia
    LIBS += -L$${PJ_BASE_DIR}/pjmedia/lib/ -lpjmedia-audiodev
    LIBS += -L$${PJ_BASE_DIR}/pjmedia/lib/ -lpjmedia-codec
    LIBS += -L$${PJ_BASE_DIR}/pjnath/lib/ -lpjnath

    LIBS += -L$${PJ_BASE_DIR}/third_party/lib/ -lsrtp
    LIBS += -L$${PJ_BASE_DIR}/third_party/lib/ -lresample
    LIBS += -L$${PJ_BASE_DIR}/third_party/lib/ -lspeex
    LIBS += -L$${PJ_BASE_DIR}/third_party/lib/ -lgsmcodec
    LIBS += -L$${PJ_BASE_DIR}/third_party/lib/ -lilbccodec
}

INCLUDEPATH += $${PJ_BASE_DIR}/pjsip/include
INCLUDEPATH += $${PJ_BASE_DIR}/pjlib/include
INCLUDEPATH += $${PJ_BASE_DIR}/pjlib-util/include
INCLUDEPATH += $${PJ_BASE_DIR}/pjmedia/include
INCLUDEPATH += $${PJ_BASE_DIR}/pjnath/include

INCLUDEPATH += $${PJ_BASE_DIR}/third_party/include

unix:!macx {
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjsip/lib/libpjsip.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjsip/lib/libpjsip-simple.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjsip/lib/libpjsua2.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjsip/lib/libpjsua.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjsip/lib/libpjsip-ua.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjlib/lib/libpj.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjlib-util/lib/libpjlib-util.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjmedia/lib/libpjmedia.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjmedia/lib/libpjmedia-audiodev.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjmedia/lib/libpjmedia-codec.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/pjnath/lib/libpjnath.so

    PRE_TARGETDEPS += $${PJ_BASE_DIR}/third_party/lib/libsrtp.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/third_party/lib/libresample.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/third_party/lib/libspeex.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/third_party/lib/libgsmcodec.so
    PRE_TARGETDEPS += $${PJ_BASE_DIR}/third_party/lib/libilbccodec.so
}
