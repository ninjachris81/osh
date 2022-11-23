#ifndef SYSTEMTIMEMANAGERSIMULATOR_H
#define SYSTEMTIMEMANAGERSIMULATOR_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "time/server/systemtimemanager.h"

class SystemtimeManagerSimulator : public SystemtimeManager
{
    Q_OBJECT
public:
    explicit SystemtimeManagerSimulator(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config) override;

protected:
    /*virtual*/ qint64 _getSystemTime() override;

signals:

public slots:
};

#endif // SYSTEMTIMEMANAGERSIMULATOR_H
