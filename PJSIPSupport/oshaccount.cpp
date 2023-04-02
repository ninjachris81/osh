#include "oshaccount.h"

#include <QDebug>
#include <QThread>
#include "helpers.h"

OshAccount::OshAccount(QObject *parentController, QString registrarIp, QString id, QString password, QObject *parent)
    : QObject{parent}, Account(), m_parentController(parentController), m_registrarIp(registrarIp)
{
    m_accountConfig.idUri = QString("sip:" + id + "@" + registrarIp).toStdString();
    m_accountConfig.regConfig.registrarUri = QString("sip:" + registrarIp).toStdString();
    m_credInfo.scheme = "digest";
    m_credInfo.realm = "*";
    m_credInfo.dataType = 0;
    m_credInfo.username = id.toStdString();
    m_credInfo.data = password.toStdString();
    m_accountConfig.sipConfig.authCreds.push_back(m_credInfo);

    qDebug() << "Adding account" << id << "to" << registrarIp;

    create(m_accountConfig);
}

void OshAccount::onRegState(OnRegStateParam &prm) {
    qDebug() << Q_FUNC_INFO;

    //AccountInfo ai = getInfo();
    //qDebug() << (ai.regIsActive? "RRR:" : "URRR:") << " code=" << prm.code;
}

void OshAccount::onIncomingCall(OnIncomingCallParam &prm) {
    qDebug() << Q_FUNC_INFO << prm.callId;

    //qDebug() << QString::fromStdString(prm.rdata.info);

    setNewCall(prm.callId);

    m_call->accept();
}

void OshAccount::setNewCall(int callId) {
    qDebug() << Q_FUNC_INFO;
    cancelCall();
    m_call = new OshCall(this, *this, callId);
    //Helpers::safeConnect(m_call, &OshCall::stateChanged, this, &OshAccount::onCallStateChanged, SIGNAL(stateChanged(OshCall::OshCallState)), SLOT(onCallStateChanged(OshCall::OshCallState)));
}

OshCall* OshAccount::currentCall() {
    return m_call;
}

void OshAccount::startCall(QString id) {
    qDebug() << Q_FUNC_INFO;

    setNewCall(-1);
    CallOpParam prm(true);
    m_call->makeCall(QString("sip:" + id + "@" + m_registrarIp).toStdString(), prm);
}

void OshAccount::cancelCall() {
    qDebug() << Q_FUNC_INFO;
    if (m_call != nullptr) {
        qWarning() << "Terminating existing call" << m_call->getId();
        m_call->kill();
        delete m_call;
    }
}

void OshAccount::changeState(OshCall::OshCallState newState) {
    qDebug() << Q_FUNC_INFO << newState << QThread::currentThreadId();
    int state = newState;
    QMetaObject::invokeMethod(m_parentController, "onCallStateChanged", Qt::AutoConnection, Q_ARG(int, state));
}
