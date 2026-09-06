#pragma once

#include <QObject>

#include "sharedlib.h"

#include "config/localconfig.h"
#include "shared/logging_categories_qt.h"

#include "macros.h"

class SHARED_LIB_EXPORT Identifyable
{
public:
    explicit Identifyable(QString id = "");

    static QLatin1String PROPERTY_ID;
    static QLatin1String PROPERTY_CLASSTYPE;
    static QLatin1String PROPERTY_VALUE_GROUP_ID;

    virtual QString id();

    virtual LogCat::LOGCAT logCat();

    QString logCatName();

    static QString getDeviceSerialId(LocalConfig* config);

    static QString generateDeviceSerialId();

protected:
    QString m_id;

signals:

public slots:
};

