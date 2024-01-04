#include "serialportclient.h"
#include <QThread>
#include <QDebug>

SerialPortClient::SerialPortClient(QString portName, QSerialPort::BaudRate baudRate, quint16 readBufferSize, quint16 readTimeoutMs, QSerialPort::Parity parity, QSerialPort::StopBits stopBits, QSerialPort::DataBits databits, QObject *parent) : QObject(parent) {
    qDebug() << Q_FUNC_INFO << portName << baudRate << readTimeoutMs;

    connect(&m_readTimer, &QTimer::timeout, this, &SerialPortClient::handleReadTimeout);

    m_serialPort.setPortName(portName);
    m_serialPort.setBaudRate(baudRate);
    m_serialPort.setReadBufferSize(readBufferSize);
    m_serialPort.setParity(parity);
    m_serialPort.setStopBits(stopBits);
    m_serialPort.setDataBits(databits);

    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPortClient::handleReadyRead);
    connect(&m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortClient::handleError);

    m_readTimer.setInterval(readTimeoutMs);
}

bool SerialPortClient::isConnected() {
    return m_isConnected;
}

void SerialPortClient::setLineMode(bool lineMode) {
    m_isLineMode = lineMode;
}

void SerialPortClient::setFlowControl(QSerialPort::FlowControl flowControl) {
    m_serialPort.setFlowControl(flowControl);
}

void SerialPortClient::setReadBufferSize(qint64 size) {
    m_serialPort.setReadBufferSize(size);
}

void SerialPortClient::setRestartTimeout(int timeoutMs) {
    m_restartTimeoutMs = timeoutMs;
}

void SerialPortClient::start() {
    qDebug() << Q_FUNC_INFO;

    m_isRestarting = false;
    if (m_serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Opened port" << m_serialPort.portName();
        m_isConnected = true;
        Q_EMIT(connected());
    } else {
        startRestart();
    }
}

void SerialPortClient::write(QByteArray data, int responseTimeout) {
    qDebug() << Q_FUNC_INFO << data.toHex();

    m_serialPort.write(data);
    m_serialPort.flush();

    if (responseTimeout > 0) {
        m_readTimer.start(responseTimeout);
    }
}

void SerialPortClient::writeSync(QByteArray data, int responseTimeout) {
    qDebug() << Q_FUNC_INFO << data.toHex();
    m_serialPort.write(data);

    if (responseTimeout > 0) {
        m_serialPort.waitForBytesWritten(responseTimeout);
    }
}

QByteArray SerialPortClient::writeReadSync(QByteArray data, int readBytes, int responseTimeout) {
    writeSync(data, responseTimeout);

    if (readBytes == -1) {
        return m_serialPort.readAll();
    } else {
        return m_serialPort.read(readBytes);
    }
}

void SerialPortClient::writeLine(QByteArray data, int responseTimeout) {
    m_serialPort.write(data.append('\n'));
    if (responseTimeout > 0) {
        m_readTimer.start(responseTimeout);
    }
}

void SerialPortClient::setReadDatagramSize(quint8 size) {
    m_readDatagramSize = size;
}

void SerialPortClient::handleReadyRead() {
    qDebug() << Q_FUNC_INFO << m_serialPort.bytesAvailable();

    if (m_isLineMode) {
        while(m_serialPort.canReadLine()) {
            m_readTimer.stop();
            Q_EMIT(lineReceived(m_serialPort.readLine()));
        }
    } else {
        if (m_readDatagramSize == 0 || m_serialPort.bytesAvailable() >= m_readDatagramSize) {
            m_readTimer.stop();
            Q_EMIT(dataReceived(m_serialPort.readAll()));
        }
    }
}

void SerialPortClient::handleReadTimeout() {
    qWarning() << Q_FUNC_INFO;

    QByteArray buff = m_serialPort.readAll();

    qWarning() << "Obsolete data" << buff;

    startRestart();
}

void SerialPortClient::handleError(QSerialPort::SerialPortError serialPortError) {
    if (m_isRestarting) return;

    if (serialPortError != QSerialPort::NoError) {
        qWarning() << Q_FUNC_INFO << serialPortError;
        startRestart();
        Q_EMIT(disconnected());
    }
}

void SerialPortClient::startRestart() {
    if (m_isRestarting) return;

    qDebug() << Q_FUNC_INFO;
    m_isRestarting = true;
    m_isConnected = false;

    m_readTimer.stop();
    m_serialPort.close();

    QTimer::singleShot(m_restartTimeoutMs, [this]() {
        start();
    } );
}
