#ifndef ACTOR_H
#define ACTOR_H

#ifdef QT_VERSION
    #ifndef USES_ACTOR_QT
        #error Should use Qt version
    #endif
#endif

#define ACTOR_ON    1
#define ACTOR_OFF   2
#define ACTOR_UP    3
#define ACTOR_DOWN  4
#define ACTOR_START 5
#define ACTOR_STOP  6
#define ACTOR_PAUSE 7
#define ACTOR_TOGGLE 8
#define ACTOR_SET_VALUE 9

// specific ones
#define ACTOR_SHUTTER_HALF_CLOSE        40      // half, but closed
#define ACTOR_SHUTTER_HALF_OPEN         41      // half, but shutters open (see-thru)
#define ACTOR_SHUTTER_FULL_OPEN         42      // full closed & shutters open (see-thru)
#define ACTOR_SHUTTER_TURN_OPEN         43
#define ACTOR_SHUTTER_TURN_CLOSE        44

#endif // ACTOR_H
