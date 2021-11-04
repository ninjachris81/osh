#ifndef SERIALPORTCLIENT_H
#define SERIALPORTCLIENT_H

#include <QByteArray>
#include <QSerialPort>
#include <QTimer>


class SerialPortClient : public QObject
{
    Q_OBJECT

public:

    explicit SerialPortClient(QString portName, QSerialPort::BaudRate baudRate = QSerialPort::BaudRate::Baud115200, quint16 readTimeoutMs = 5000, QSerialPort::Parity parity = QSerialPort::Parity::NoParity, QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop, QSerialPort::DataBits databits = QSerialPort::DataBits::Data8, QObject *parent = nullptr);

    void write(QByteArray data, int responseTimeout = -1);
    void writeLine(QByteArray data, int responseTimeout = -1);

    void setLineMode(bool lineMode);

    void setFlowControl(QSerialPort::FlowControl flowControl);
    void setReadBufferSize(qint64 size);
    void setRestartTimeout(int timeoutMs);

    void setReadDatagramSize(quint8 size);

    bool isConnected();

public slots:
    void start();

signals:
    void lineReceived(QByteArray data);
    void dataReceived(QByteArray data);

private:
    void startRestart();

private slots:
    void handleReadyRead();
    void handleReadTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    bool m_isLineMode = false;
    QSerialPort m_serialPort;
    QByteArray m_readData;
    QTimer m_readTimer;
    bool m_isRestarting = false;
    int m_restartTimeoutMs = 5000;
    quint8 m_readDatagramSize = 0;
    bool m_isConnected = false;

signals:
    void connected();
    void disconnected();

};

#endif // SERIALPORTCLIENT_H
