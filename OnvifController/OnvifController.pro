QT -= gui

TEMPLATE = lib
TARGET = OnvifController
DEFINES += MAKE_SHARED_LIB

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cams/cambase.cpp \
    cams/jidetech_p1_4x.cpp \
    deviceregistry.cpp \
    extender/analyticsserviceext.cpp \
    extender/deviceioserviceext.cpp \
    extender/deviceserviceext.cpp \
    extender/eventserviceext.cpp \
    extender/mediaserviceext.cpp \
    extender/ptzserviceext.cpp \
    onvifcontroller.cpp \
    onvifservercontroller.cpp \
    onvifserverthread.cpp \
    wrapper/analyticsservicewrapper.cpp \
    wrapper/deviceioservicewrapper.cpp \
    wrapper/deviceservicewrapper.cpp \
    wrapper/eventservicewrapper.cpp \
    wrapper/imagingservicewrapper.cpp \
    wrapper/mediaservicewrapper.cpp \
    wrapper/ptzservicewrapper.cpp

HEADERS += \
    cams/cambase.h \
    cams/jidetech_p1_4x.h \
    deviceregistry.h \
    extender/analyticsserviceext.h \
    extender/deviceioserviceext.h \
    extender/deviceserviceext.h \
    extender/eventserviceext.h \
    extender/mediaserviceext.h \
    extender/ptzserviceext.h \
    onvifcontroller.h \
    onvifservercontroller.h \
    onvifserverthread.h \
    wrapper/analyticsservicewrapper.h \
    wrapper/deviceioservicewrapper.h \
    wrapper/deviceservicewrapper.h \
    wrapper/eventservicewrapper.h \
    wrapper/imagingservicewrapper.h \
    wrapper/mediaservicewrapper.h \
    wrapper/ptzservicewrapper.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

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
