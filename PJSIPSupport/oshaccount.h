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
#include "oshstatecallback.h"

using namespace pj;

class SHARED_LIB_EXPORT OshAccount : public QObject, public Account, public OshStateCallback
{
    Q_OBJECT
public:

    explicit OshAccount(OshStateCallback* stateCallback, QString registrarIp, QString id, QString password, QObject *parent = nullptr);

    void startCall(QString id);

    void cancelCall();

    void changeState(OshCall::OshCallState newState);

    virtual void onRegState(OnRegStateParam &prm);

    virtual void onIncomingCall(OnIncomingCallParam &prm);

    OshCall* currentCall();

private:
    OshStateCallback* m_stateCallback;
    QString m_registrarIp;
    AccountConfig m_accountConfig;
    AuthCredInfo m_credInfo;

    OshCall *m_call = nullptr;

    void setNewCall(int callId);

private slots:
    //void onCallStateChanged(OshCall::OshCallState state);

signals:
    // signals dont work
    //void stateChanged(OshCall::OshCallState state);

};

#endif // OSHACCOUNT_H
