#ifndef OSHACCOUNT_H
#define OSHACCOUNT_H

#include <QObject>

#ifdef PJ_USE_STUBS
    #include "pjstubs.h"
#else
    #include <pjsua2/account.hpp>
#endif

#include "oshcall.h"
#include "sharedlib.h"

using namespace pj;

class SHARED_LIB_EXPORT OshAccount : public QObject, public Account
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

private slots:
    void onCallStateChanged(OshCall::OshCallState state);

signals:
    void stateChanged(OshCall::OshCallState state);

};

#endif // OSHACCOUNT_H
