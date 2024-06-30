#include "gpioreaderbase.h"

GPIOReaderBase::GPIOReaderBase(int inputCount, QObject *parent)
    : QThread{parent}, m_inputCount(inputCount)
{

}

void GPIOReaderBase::enableDebug() {
    m_enableDebug = true;
}
