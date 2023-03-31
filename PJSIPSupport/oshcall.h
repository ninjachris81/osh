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
    #include <pjmedia.h>
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
    ToneGenerator m_ringToneGenerator;
    ToneDescVector m_toneVector;

    AudioMedia m_cap_dev_med;
    AudioMedia m_play_dev_med;

    void onStartRinging();
    void onStopRinging();

signals:
    void startRinging();
    void stopRinging();

};

#endif // OSHCALL_H
