#ifndef MANAGERREGISTRATION_H
#define MANAGERREGISTRATION_H

#include <QObject>

#include <QMap>

#include "config/localconfig.h"

class ManagerBase;      // fwd decl

class ManagerRegistration : public QObject
{
    Q_OBJECT
public:
    enum INSTANCE_ROLE {
        UNKNOWN,
        SERVER,
        CLIENT,
        GUI
    };

    explicit ManagerRegistration(INSTANCE_ROLE instanceRole, QObject *parent = nullptr);

    void registerManager(ManagerBase* manager);

    ManagerBase* getManager(QString name);

    void init(LocalConfig *config);

    QStringList managerNames();

    INSTANCE_ROLE instanceRole();

private:
    QMap<QString, ManagerBase*> m_managers;
    INSTANCE_ROLE m_instanceRole;

signals:

public slots:
};

#endif // MANAGERREGISTRATION_H
