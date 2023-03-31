#include "gpioreaderbase.h"

GPIOReaderBase::GPIOReaderBase(int inputCount, QObject *parent)
    : QThread{parent}, m_inputCount(inputCount)
{

}
