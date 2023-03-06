#include "homeconnectcontroller.h"

#include <QDebug>
#include <QNetworkReply>
#include <QXmlQuery>

#include "controller/controllermanager.h"
#include "qhttpmultipart.h"
#include "qurlquery.h"

HomeConnectController::HomeConnectController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &HomeConnectController::onMaintenance);
}

void HomeConnectController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_baseServerUrl = m_config->getString(this, "baseServerUrl", "http://api.home-connect.com");
    m_clientId = m_config->getString(this, "clientId", "");
    m_clientSecret = m_config->getString(this, "clientSecret", "");
    m_redirectUrl = m_config->getString(this, "redirectUri", "http://localhost:8881");
    m_scope = m_config->getString(this, "scope", "IdentifyAppliance Monitor");
    m_email = m_config->getString(this, "email", "");
    m_password = m_config->getString(this, "password", "");
}

void HomeConnectController::start() {
    iDebug() << Q_FUNC_INFO;

    m_statusTimer.start();
}

void HomeConnectController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO;
}

void HomeConnectController::onMaintenance() {
    if (m_sessionInfos.accessToken.isEmpty()) {

    }
}

void HomeConnectController::acquireAccessToken() {
    iInfo() << Q_FUNC_INFO;

    QUrl url(m_baseServerUrl + "/security/oauth/authorize?response_type=code&client_id=" + m_clientId + "&client_secret=" + m_clientSecret + "&redirect_uri=" + m_redirectUrl + "&scope=" + m_scope);
    QNetworkRequest req(url);

    QNetworkReply *reply = m_nam.get(req);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        if (reply->error() == QNetworkReply::NoError) {
            QString content = reply->readAll();

            QXmlQuery query;
            query.setQuery(content, QUrl("/descendant-or-self::form[@id='login_form']/input[@type='hidden' and @name='sessionId']/@value"));
            QString sessionId;
            query.evaluateTo(&sessionId);

            QString sessionData;
            query.setQuery(content, QUrl("/descendant-or-self::form[@id='login_form']/input[@type='hidden' and @name='sessionData']/@value"));
            query.evaluateTo(&sessionData);

            submitLoginForm(sessionId, sessionData);
        } else {
            iWarning() << reply->errorString();
        }

        reply->deleteLater();
    });
}

void HomeConnectController::submitLoginForm(QString sessionId, QString sessionData) {
    iInfo() << Q_FUNC_INFO;

    QUrl url(m_baseServerUrl + "/security/oauth/login");
    QNetworkRequest req(url);

    QUrlQuery postData;
    postData.addQueryItem("sessionId", sessionId);
    postData.addQueryItem("sessionData", sessionData);
    postData.addQueryItem("aborted", "false");
    postData.addQueryItem("client_id", m_clientId);
    postData.addQueryItem("email", m_email);
    postData.addQueryItem("region", "EU");
    postData.addQueryItem("environment", "PROD");
    postData.addQueryItem("lookup", "true");

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    QNetworkReply *reply = m_nam.post(req, postData.toString(QUrl::FullyEncoded).toUtf8());

    connect(reply, &QNetworkReply::finished, [this, reply](){
        if (reply->error() == QNetworkReply::NoError) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            submitLoginFormPassword();
        } else {
            iWarning() << reply->errorString();
        }

        reply->deleteLater();
    });
}

void HomeConnectController::submitLoginFormPassword() {
    iInfo() << Q_FUNC_INFO;


}
