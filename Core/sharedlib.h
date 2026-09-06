#pragma once

#include <QtCore/QtGlobal>

#ifndef QT_STATIC
    #if defined(MAKE_SHARED_LIB)
        #define SHARED_LIB_EXPORT Q_DECL_EXPORT
    #else
        #define SHARED_LIB_EXPORT Q_DECL_IMPORT
    #endif
#else
    #define SHARED_LIB_EXPORT
#endif

