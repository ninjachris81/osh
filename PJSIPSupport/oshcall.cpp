#include "oshcall.h"

#include "oshaccount.h"

#include <QDebug>

OshCall::OshCall(OshAccount &account, int callId, QObject *parent)
    : QObject{parent}, Call(account, callId)
{
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
    //qDebug() << Q_FUNC_INFO << prm.e.type;
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
}
