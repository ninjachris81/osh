#ifndef IDENTIFYABLE_H
#define IDENTIFYABLE_H

#include <QObject>

#include "config/localconfig.h"
#include "shared/logging_categories_qt.h"

#include "macros.h"

class Identifyable : public QObject
{
    Q_OBJECT
public:
    explicit Identifyable(QString id = "", QObject *parent = nullptr);

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

#endif // IDENTIFYABLE_H
