#ifndef SHARED_LIB_GLOBAL_H
#define SHARED_LIB_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined MAKE_SHARED_LIB
    #define SHARED_LIB_EXPORT Q_DECL_EXPORT
#else
    #define SHARED_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SHARED_LIB_GLOBAL_H
