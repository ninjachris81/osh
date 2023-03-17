#include "audioprocesswrapperbase.h"

AudioProcessWrapperBase::AudioProcessWrapperBase(AudioPlaybackActor *audioActor, QObject *parent) : QProcess(parent), m_audioActor(audioActor) {

}

AudioPlaybackActor *AudioProcessWrapperBase::audioActor() {
    return m_audioActor;
}
