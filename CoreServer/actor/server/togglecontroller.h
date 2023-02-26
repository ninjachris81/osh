#ifndef TOGGLECONTROLLER_H
#define TOGGLECONTROLLER_H

#include <QObject>
#include "actor/actormanager.h"
#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "controller/controllermessage.h"

class SHARED_LIB_EXPORT ToggleController : public ControllerBase
{
    Q_OBJECT
public:
    explicit ToggleController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    void init() override;

    void start() override;

    void handleMessage(ControllerMessage *msg)  override;

    void bindManager(ActorManager* actorManager, ValueManagerBase* valueManager);

private:
    ValueManagerBase* valueManager = nullptr;

protected slots:
    void onRequestToggle();

signals:

};

#endif // TOGGLECONTROLLER_H
