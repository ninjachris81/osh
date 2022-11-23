#ifndef MANAGERBASE_H
#define MANAGERBASE_H

#include <QObject>
#include <QLoggingCategory>

#include "config/localconfig.h"
#include "manager/managerregistration.h"
#include "communication/messagebase.h"
#include "shared/logging_categories_qt.h"
#include "identifyable.h"

class ManagerBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit ManagerBase(QObject *parent = nullptr);

    void setManagerRegistration(ManagerRegistration* managerRegistration);

    void setInitialized();

    virtual QString id() = 0;

    virtual void init(LocalConfig* config) = 0;

    virtual void postInit() {}

    virtual bool isPriorityManager() {
        return false;
    }

    virtual MessageBase::MESSAGE_TYPE getMessageType() = 0;

    virtual void handleReceivedMessage(MessageBase* msg) = 0;

    template<class MANAGER_TYPE> MANAGER_TYPE* getManager(QString id) {
        MANAGER_TYPE* returnVal = static_cast<MANAGER_TYPE*>(managerRegistration()->getManager(id));
        Q_ASSERT(returnVal != nullptr);
        return returnVal;
    }

private:
    ManagerRegistration *m_managerRegistration;

protected:
    ManagerRegistration* managerRegistration();
    bool m_isInitialized = false;

signals:

public slots:
};

#endif // MANAGERBASE_H
