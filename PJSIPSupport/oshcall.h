#ifndef OSHCALL_H
#define OSHCALL_H

#include <QObject>

#ifdef PJ_USE_STUBS
    #include "pjstubs.h"
#else
    #include <pjsua2/account.hpp>
    #include <pjsua2/siptypes.hpp>
    #include <pjsua2/call.hpp>
    #include <pjsua2/endpoint.hpp>
#endif


class OshAccount;

using namespace pj;

class OshCall : public QObject, public Call
{
    Q_OBJECT
public:
    explicit OshCall(OshAccount &account, int callId, QObject *parent = nullptr);

    void accept();

    void kill();

    void muteMic();

    void muteSpeaker();

    void onCallState(OnCallStateParam &prm) override;
    void onCallMediaState(OnCallMediaStateParam &prm) override;


private:
    AudioMedia m_cap_dev_med;
    AudioMedia m_play_dev_med;

signals:

};

#endif // OSHCALL_H
