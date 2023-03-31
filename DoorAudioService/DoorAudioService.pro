QT -= gui
QT += mqtt sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/release/ -lQMqttCommunicationManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/debug/ -lQMqttCommunicationManager
else:unix: LIBS += -L$$OUT_PWD/../QMqttCommunicationManager/ -lQMqttCommunicationManager

INCLUDEPATH += $$PWD/../QMqttCommunicationManager
DEPENDPATH += $$PWD/../QMqttCommunicationManager

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PJSIPSupport/release/ -lPJSIPSupport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PJSIPSupport/debug/ -lPJSIPSupport
else:unix: LIBS += -L$$OUT_PWD/../PJSIPSupport/ -lPJSIPSupport

INCLUDEPATH += $$PWD/../PJSIPSupport
DEPENDPATH += $$PWD/../PJSIPSupport

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DoorAudioController/release/ -lDoorAudioController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DoorAudioController/debug/ -lDoorAudioController
else:unix: LIBS += -L$$OUT_PWD/../DoorAudioController/ -lDoorAudioController

INCLUDEPATH += $$PWD/../DoorAudioController
DEPENDPATH += $$PWD/../DoorAudioController

win32: DEFINES += PJ_USE_STUBS


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
