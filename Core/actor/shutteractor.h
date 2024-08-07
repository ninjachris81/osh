#ifndef SHUTTERACTOR_H
#define SHUTTERACTOR_H

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"
#include "shared/actor_qt.h"
#include "value/integervalue.h"

class SHARED_LIB_EXPORT ShutterActor : public ActorBase
{
    Q_OBJECT
public:
    #define SHUTTER_OPENED 0
    #define SHUTTER_CLOSED 100

    #define SHUTTER_TILT_OPENED 0
    #define SHUTTER_TILE_CLOSED 100

    #define SHUTTER_OPERATION_MODE_AUTO     0
    #define SHUTTER_OPERATION_MODE_MANUAL   1

    static QLatin1String PROPERTY_TILT_SUPPORT;
    static QLatin1String PROPERTY_FULL_CLOSE_DURATION;
    static QLatin1String PROPERTY_FULL_TILT_DURATION;

    static QLatin1String CONFIG_OPERATION_MODE;

    explicit ShutterActor();
    explicit ShutterActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, bool tiltSupport, int fullCloseDuration, int fullTiltDuration, QObject *parent = nullptr);

    /*virtual*/ bool cmdSupported(actor::ACTOR_CMDS cmd);

    /*virtual*/ QVariant _updateValue(QVariant newValue);

    /*virtual*/ bool isAsync();

    // 0 = open, 100 = closed
    void updateClosePattern(unsigned char closeState);
    // 0 = open, 100 = closed
    void updateTiltPattern(unsigned char tiltState);

    unsigned char closeState();
    unsigned char tiltState();

    bool tiltSupport();
    int fullCloseDuration();
    int fullTiltDuration();

protected:
    /*virtual*/ void _triggerCmd(actor::ACTOR_CMDS cmd);

    int setState(unsigned char closeState, unsigned char tiltState);
    int setCloseState(int state, unsigned char closeState);
    int setTiltState(int state, unsigned char tiltState);
    unsigned char getCloseState(int state);
    unsigned char getTiltState(int state);

    bool m_tiltSupport = false;
    int m_fullCloseDuration = 20000;
    int m_fullTiltDuration = 2000;


signals:

};

#endif // SHUTTERACTOR_H
