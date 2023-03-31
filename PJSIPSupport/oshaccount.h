#ifndef OSHACCOUNT_H
#define OSHACCOUNT_H

#include <QObject>

#ifdef PJ_USE_STUBS
    #include "pjstubs.h"
#else
    #include <pjsua2/account.hpp>
#endif

#include "oshcall.h"

using namespace pj;

class OshAccount : public QObject, public Account
{
    Q_OBJECT
public:
    explicit OshAccount(QString registrarIp, QString id, QString password, QObject *parent = nullptr);

    void startCall(QString id);

    void cancelCall();

    virtual void onRegState(OnRegStateParam &prm);

    virtual void onIncomingCall(OnIncomingCallParam &prm);

    OshCall* currentCall();

private:
    QString m_registrarIp;
    AccountConfig m_accountConfig;
    AuthCredInfo m_credInfo;

    OshCall *m_call = nullptr;

    void setNewCall(int callId);

signals:

};

#endif // OSHACCOUNT_H
