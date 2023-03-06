#ifndef HOMECONNECTCONTROLLER_H
#define HOMECONNECTCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class SHARED_LIB_EXPORT HomeConnectController : public ControllerBase
{
Q_OBJECT

public:
    struct SessionInfos {
        QString accessToken = "";
        QString refreshToken = "";
    } m_sessionInfos;

    HomeConnectController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void acquireAccessToken();
    void submitLoginForm(QString sessionId, QString sessionData);
    void submitLoginFormPassword();

protected slots:
    void onMaintenance();

private:
    ClientSystemWarningsManager* m_warnManager;
    QTimer m_statusTimer;
    QNetworkAccessManager m_nam;

    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUrl;
    QString m_scope;
    QString m_baseServerUrl;
    QString m_email;
    QString m_password;



};

#endif // HOMECONNECTCONTROLLER_H
