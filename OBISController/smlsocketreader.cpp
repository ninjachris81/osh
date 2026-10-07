#include "smlsocketreader.h"

#include <QDebug>
#include <QSerialPort>

#include <cmath>
#include <cstdlib>
#include <memory>
#include <utility>

#include <sml/sml_file.h>
#include <sml/sml_list.h>
#include <sml/sml_shared.h>
#include <sml/sml_value.h>

namespace {
constexpr qsizetype MaxTransportFrameLength = 8096;

const QByteArray &transportStartSequence()
{
    static const QByteArray sequence = QByteArray::fromHex("1b1b1b1b01010101");
    return sequence;
}

const QByteArray &transportEndSequence()
{
    static const QByteArray sequence = QByteArray::fromHex("1b1b1b1b1a");
    return sequence;
}
}

SMLSocketReader::SMLSocketReader(const QString &port, QObject *parent)
    : QObject(parent)
    , m_serialPort(new QSerialPort(this))
{
    m_serialPort->setPortName(port);
    connect(m_serialPort, &QSerialPort::readyRead, this, &SMLSocketReader::consumeAvailableData);
    connect(m_serialPort, &QSerialPort::errorOccurred, this,
            [this](QSerialPort::SerialPortError error) {
                if (error == QSerialPort::NoError || error == QSerialPort::NotOpenError) {
                    return;
                }
                const QString message = m_serialPort->errorString();
                qWarning() << "SML serial reader error:" << message;
                Q_EMIT readerError(message);
            });
}

SMLSocketReader::~SMLSocketReader()
{
    stop();
}

bool SMLSocketReader::start()
{
    if (m_serialPort->isOpen()) {
        return true;
    }

    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        const QString message = m_serialPort->errorString();
        qWarning() << "Could not open SML serial port" << m_serialPort->portName() << message;
        Q_EMIT readerError(message);
        return false;
    }

    m_buffer.clear();
    if (!m_serialPort->setRequestToSend(true)) {
        const QString message = m_serialPort->errorString();
        qWarning() << "Could not assert RTS for SML serial port" << m_serialPort->portName() << message;
        Q_EMIT readerError(message);
    }
    return true;
}

void SMLSocketReader::stop()
{
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
    }
    m_buffer.clear();
}

void SMLSocketReader::consumeAvailableData()
{
    m_buffer.append(m_serialPort->readAll());

    while (!m_buffer.isEmpty()) {
        const qsizetype startIndex = m_buffer.indexOf(transportStartSequence());
        if (startIndex < 0) {
            const qsizetype maxSuffixLength = transportStartSequence().size() - 1;
            qsizetype suffixLength = qMin(m_buffer.size(), maxSuffixLength);
            while (suffixLength > 0
                   && !transportStartSequence().startsWith(m_buffer.sliced(m_buffer.size() - suffixLength))) {
                --suffixLength;
            }
            m_buffer = suffixLength == 0 ? QByteArray() : m_buffer.right(suffixLength);
            return;
        }

        if (startIndex > 0) {
            m_buffer.remove(0, startIndex);
        }

        const qsizetype endIndex = m_buffer.indexOf(transportEndSequence(), transportStartSequence().size());
        if (endIndex < 0) {
            if (m_buffer.size() > MaxTransportFrameLength) {
                const QString message = QStringLiteral("SML transport frame exceeded %1 bytes")
                                            .arg(MaxTransportFrameLength);
                qWarning() << message;
                Q_EMIT readerError(message);
                m_buffer.remove(0, 1);
                continue;
            }
            return;
        }

        const qsizetype frameLength = endIndex + 8;
        if (frameLength > MaxTransportFrameLength) {
            const QString message = QStringLiteral("SML transport frame exceeded %1 bytes")
                                        .arg(MaxTransportFrameLength);
            qWarning() << message;
            Q_EMIT readerError(message);
            m_buffer.remove(0, 1);
            continue;
        }
        if (m_buffer.size() < frameLength) {
            return;
        }

        QByteArray frame = m_buffer.left(frameLength);
        m_buffer.remove(0, frameLength);
        processFrame(std::move(frame));
    }
}

void SMLSocketReader::processFrame(QByteArray frame)
{
    const qsizetype payloadLength = frame.size() - 16;
    if (payloadLength <= 0) {
        const QString message = QStringLiteral("Received an empty SML transport frame");
        qWarning() << message;
        Q_EMIT readerError(message);
        return;
    }

    processFile(reinterpret_cast<unsigned char *>(frame.data() + 8),
                static_cast<std::size_t>(payloadLength));
}

void SMLSocketReader::processFile(unsigned char *buffer, std::size_t bufferLength)
{
    std::unique_ptr<sml_file, decltype(&sml_file_free)> file(
        sml_file_parse(buffer, bufferLength), &sml_file_free);
    if (!file) {
        const QString message = QStringLiteral("libSML could not parse the received SML file");
        qWarning() << message;
        Q_EMIT readerError(message);
        return;
    }

    for (short i = 0; i < file->messages_len; ++i) {
        sml_message *message = file->messages[i];
        if (!message || !message->message_body || !message->message_body->tag
            || *message->message_body->tag != SML_MESSAGE_GET_LIST_RESPONSE) {
            continue;
        }

        auto *response = static_cast<sml_get_list_response *>(message->message_body->data);
        if (!response) {
            continue;
        }

        for (sml_list *entry = response->val_list; entry; entry = entry->next) {
            if (!entry->value) {
                continue;
            }

            const QByteArray obisCode = entry->obj_name && entry->obj_name->str
                                            && entry->obj_name->len > 0
                                            ? QByteArray(reinterpret_cast<const char *>(entry->obj_name->str),
                                                         entry->obj_name->len)
                                            : QByteArray();
            const auto emitValue = [this, &obisCode](QVariant receivedValue) {
                Q_EMIT valueReceived(receivedValue);
                if (!obisCode.isEmpty()) {
                    Q_EMIT obisValueReceived(obisCode, receivedValue);
                }
            };

            sml_value *value = entry->value;
            const unsigned char type = value->type & SML_TYPE_FIELD;
            if (type == SML_TYPE_OCTET_STRING) {
                if (!value->data.bytes) {
                    const QString message = QStringLiteral("Received an invalid SML octet string");
                    qWarning() << message;
                    Q_EMIT readerError(message);
                    continue;
                }
                if (value->data.bytes->len == 0) {
                    emitValue(QString());
                    continue;
                }

                char *hexString = nullptr;
                if (sml_value_to_strhex(value, &hexString, true) && hexString) {
                    const QString stringValue = QString::fromLatin1(hexString);
                    std::free(hexString);
                    emitValue(stringValue);
                } else {
                    std::free(hexString);
                    const QString message = QStringLiteral("Could not convert an SML octet string");
                    qWarning() << message;
                    Q_EMIT readerError(message);
                }
            } else if (value->type == SML_TYPE_BOOLEAN) {
                if (!value->data.boolean) {
                    const QString message = QStringLiteral("Received an invalid SML boolean");
                    qWarning() << message;
                    Q_EMIT readerError(message);
                    continue;
                }
                emitValue(static_cast<bool>(*value->data.boolean));
            } else if (type == SML_TYPE_INTEGER || type == SML_TYPE_UNSIGNED) {
                const int scaler = entry->scaler ? *entry->scaler : 0;
                const double scaledValue = sml_value_to_double(value) * std::pow(10.0, scaler);
                emitValue(scaledValue);
            }
        }
    }
}
