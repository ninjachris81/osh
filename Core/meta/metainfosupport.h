#ifndef METAINFOSUPPORT_H
#define METAINFOSUPPORT_H

#include "meta/itemmetainfo.h"

#include "sharedlib.h"

class SHARED_LIB_EXPORT MetaInfoSupport
{
public:

    ItemMetaInfo* metaInfo();

    ItemMetaInfo m_metaInfo;

};

#endif // METAINFOSUPPORT_H
