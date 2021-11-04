#ifndef IDENTIFYABLE_H
#define IDENTIFYABLE_H

#include <QObject>

#include "config/localconfig.h"

class Identifyable : public QObject
{
    Q_OBJECT
public:
    explicit Identifyable(QString id, QObject *parent = nullptr);

    QString id();

    static QString getDeviceSerialId(LocalConfig* config);

    static QString generateDeviceSerialId();

protected:
    QString m_id;

signals:

public slots:
};

#endif // IDENTIFYABLE_H
