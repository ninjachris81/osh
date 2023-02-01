QT -= gui
QT += mqtt
QT += serialport
QT += serialbus

CONFIG += c++17 console
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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../OnvifController/release/ -lOnvifController
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../OnvifController/debug/ -lOnvifController
else:unix: LIBS += -L$$OUT_PWD/../OnvifController/ -lOnvifController

INCLUDEPATH += $$PWD/../OnvifController
DEPENDPATH += $$PWD/../OnvifController

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Release/OnvifPTZLib/release/ -lOnvifPTZLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifPTZLib/debug/ -lOnvifPTZLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifPTZLib/ -lOnvifPTZLib

INCLUDEPATH += $$PWD/../onviflibs/OnvifPTZLib
DEPENDPATH += $$PWD/../onviflibs/OnvifPTZLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifAnalyticsLib/release/ -lOnvifAnalyticsLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifAnalyticsLib/debug/ -lOnvifAnalyticsLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifAnalyticsLib/ -lOnvifAnalyticsLib

INCLUDEPATH += $$PWD/../onviflibs/OnvifAnalyticsLib
DEPENDPATH += $$PWD/../onviflibs/OnvifAnalyticsLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifMediaLib/release/ -lOnvifMediaLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifMediaLib/debug/ -lOnvifMediaLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifMediaLib/ -lOnvifMediaLib

INCLUDEPATH += $$PWD/../onviflibs/OnvifMediaLib
DEPENDPATH += $$PWD/../onviflibs/OnvifMediaLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifEventLib/release/ -lOnvifEventLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifEventLib/debug/ -lOnvifEventLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifEventLib/ -lOnvifEventLib

INCLUDEPATH += $$PWD/../onviflibs/onvifcore/OnvifEventLib
DEPENDPATH += $$PWD/../onviflibs/onvifcore/OnvifEventLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDeviceLib/release/ -lOnvifDeviceLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDeviceLib/debug/ -lOnvifDeviceLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDeviceLib/ -lOnvifDeviceLib

INCLUDEPATH += $$PWD/../onviflibs/onvifcore/OnvifDeviceLib
DEPENDPATH += $$PWD/../onviflibs/onvifcore/OnvifDeviceLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifDeviceIOLib/release/ -lOnvifDeviceIOLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifDeviceIOLib/debug/ -lOnvifDeviceIOLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifDeviceIOLib/ -lOnvifDeviceIOLib

INCLUDEPATH += $$PWD/../onviflibs/OnvifDeviceIOLib
DEPENDPATH += $$PWD/../onviflibs/OnvifDeviceIOLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifImagingLib/release/ -lOnvifImagingLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifImagingLib/debug/ -lOnvifImagingLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/OnvifImagingLib/ -lOnvifImagingLib

INCLUDEPATH += $$PWD/../onviflibs/OnvifImagingLib
DEPENDPATH += $$PWD/../onviflibs/OnvifImagingLib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDiscoveryLib/release/ -lOnvifDiscoveryLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDiscoveryLib/debug/ -lOnvifDiscoveryLib
else:unix: LIBS += -L$$PWD/../../build-OSH-Desktop_Qt_5_12_12_MinGW_64_bit-Debug/onvifcore/OnvifDiscoveryLib/ -lOnvifDiscoveryLib

INCLUDEPATH += $$PWD/../onviflibs/onvifcore/OnvifDiscoveryLib
DEPENDPATH += $$PWD/../onviflibs/onvifcore/OnvifDiscoveryLib
