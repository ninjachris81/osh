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

#include "sharedlib.h"

class OshAccount;
class OshStateCallback;

using namespace pj;

class SHARED_LIB_EXPORT OshCall : public QObject, public Call
{
    Q_OBJECT
public:
    enum OshCallState {
        IDLE,
        RINGING,
        ACTIVE
    };

    explicit OshCall(OshStateCallback *stateCallback, OshAccount &account, int callId, QObject *parent = nullptr);

    void accept();

    void kill();

    void muteMic();

    void muteSpeaker();

    void onCallState(OnCallStateParam &prm) override;
    void onCallMediaState(OnCallMediaStateParam &prm) override;

private:
    OshStateCallback* m_callback = nullptr;

    ToneGenerator m_ringToneGenerator;
    ToneDescVector m_toneVector;

    AudioMedia m_cap_dev_med;
    AudioMedia m_play_dev_med;

    void startRinging();
    void stopRinging();

    void changeState(OshCallState state);

signals:
    // does not work, hence using cb
    //void stateChanged(OshCallState state);

};

#endif // OSHCALL_H
