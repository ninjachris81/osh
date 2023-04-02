#include "oshcall.h"

#include "oshaccount.h"
#include "oshstatecallback.h"

#include <QDebug>

OshCall::OshCall(OshStateCallback *stateCallback, OshAccount &account, int callId, QObject *parent)
    : QObject{parent}, Call(account, callId), m_callback(stateCallback)
{
    m_ringToneGenerator.createToneGenerator();

    ToneDesc t1;
    t1.freq1 = 440;
    //t1.freq2 = 480;
    t1.on_msec = 1500;
    t1.off_msec = 3000;
    m_toneVector.push_back(t1);
    m_ringToneGenerator.play(m_toneVector, true);

    m_cap_dev_med = Endpoint::instance().audDevManager().getCaptureDevMedia();
    m_play_dev_med = Endpoint::instance().audDevManager().getPlaybackDevMedia();
}

void OshCall::accept() {
    qDebug() << Q_FUNC_INFO;
    CallOpParam answerPrm;
    answerPrm.statusCode = PJSIP_SC_OK;
    answer(answerPrm);
}

void OshCall::kill() {
    qDebug() << Q_FUNC_INFO;

    if (isActive()) {
        CallOpParam hangupPrm;
        hangupPrm.statusCode = PJSIP_SC_CONFLICT;
        hangup(hangupPrm);
    }
}

void OshCall::muteMic() {
    m_cap_dev_med.adjustTxLevel(0.0);       // TO BE TESTED
}

void OshCall::muteSpeaker() {
    m_play_dev_med.adjustRxLevel(0.0);
}


void OshCall::onCallState(OnCallStateParam &prm) {
    CallInfo info = getInfo();

    qDebug() << Q_FUNC_INFO << info.state << info.lastStatusCode;

    pjsip_inv_state callState = info.state;
    pjsip_status_code statusCode = info.lastStatusCode;
    pjsip_role_e role = info.role;

    switch(callState)     {
    case PJSIP_INV_STATE_DISCONNECTED:
    case PJSIP_INV_STATE_CONFIRMED:
        stopRinging();
        changeState(IDLE);
        break;
    case PJSIP_INV_STATE_EARLY:
        if (statusCode == PJSIP_SC_RINGING && role == PJSIP_ROLE_UAC) {
            startRinging();
            changeState(RINGING);
//        } else if (statusCode == PJSIP_SC_PROGRESS) {
//            stopRinging();
        }
        break;
    default:
        break;
    }
}

void OshCall::onCallMediaState(OnCallMediaStateParam &prm) {
    qDebug() << Q_FUNC_INFO;
    AudioMedia aud_med;

    try {
        // Get the first audio media
        aud_med = getAudioMedia(-1);
    } catch(...) {
        qWarning() << "Errow while getting media";
        return;
    }

    // This will connect the sound device/mic to the call audio media
    m_cap_dev_med.startTransmit(aud_med);

    // And this will connect the call audio media to the sound device/speaker
    aud_med.startTransmit(m_play_dev_med);

    changeState(ACTIVE);
}


void OshCall::startRinging() {
    qDebug() << Q_FUNC_INFO;

    //m_ringToneGenerator.play(m_toneVector, true);
    m_ringToneGenerator.startTransmit(m_play_dev_med);

}

void OshCall::stopRinging() {
    qDebug() << Q_FUNC_INFO;

    m_ringToneGenerator.stopTransmit(m_play_dev_med);
    //m_ringToneGenerator.stop();
}

void OshCall::changeState(OshCallState state) {
    qDebug() << Q_FUNC_INFO << state;
    m_callback->changeState(state);
}
