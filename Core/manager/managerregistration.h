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
    explicit ManagerRegistration(QObject *parent = nullptr);

    void registerManager(ManagerBase* manager);

    ManagerBase* getManager(QString name);

    void init(LocalConfig *config);

    QStringList managerNames();

private:
    QMap<QString, ManagerBase*> m_managers;

signals:

public slots:
};

#endif // MANAGERREGISTRATION_H
