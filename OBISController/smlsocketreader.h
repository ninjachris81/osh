#pragma once

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QVariant>

#include <cstddef>

#include "sharedlib.h"

class QSerialPort;

class SHARED_LIB_EXPORT SMLSocketReader : public QObject
{
    Q_OBJECT
public:
    explicit SMLSocketReader(const QString &port, QObject *parent = nullptr);
    ~SMLSocketReader() override;

    bool start();
    void stop();

Q_SIGNALS:
    void valueReceived(QVariant value);
    void obisValueReceived(QByteArray obisCode, QVariant value);
    void readerError(QString message);

private Q_SLOTS:
    void consumeAvailableData();

private:
    void processFrame(QByteArray frame);
    void processFile(unsigned char *buffer, std::size_t bufferLength);

    QSerialPort *m_serialPort;
    QByteArray m_buffer;
};
