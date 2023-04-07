QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        imagemagickthumnailmanager.cpp \
        imagemagickwrapper.cpp \
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


win32: IM_DIR='D:\Program Files\ImageMagick-7.1.1-Q16-HDRI'
unix: IM_DIR=/usr/lib


win32:CONFIG(release, debug|release): LIBS += -L$${IM_DIR}/lib -lCORE_RL_Magick++_
else:win32:CONFIG(debug, debug|release): LIBS += -L$${IM_DIR}/lib -lCORE_RL_Magick++_
else:unix: LIBS += -L$${IM_DIR}/lib/ -lCORE_RL_Magick++_

INCLUDEPATH += $${IM_DIR}/include
DEPENDPATH += $${IM_DIR}/include

HEADERS += \
    imagemagickthumnailmanager.h \
    imagemagickwrapper.h
