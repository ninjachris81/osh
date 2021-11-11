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

#endif // ACTOR_H
