#ifndef AUDIOSTREAMDEVICE_H
#define AUDIOSTREAMDEVICE_H

#include "qurl.h"
#include <QObject>
#include <QIODevice>

class AudioStreamDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioStreamDevice(QUrl url, QObject *parent = nullptr);

    /*virtual*/ bool isSequential() const override {
        return false;
    }

    /*virtual*/ bool open(OpenMode mode) override;
    /*virtual*/ void close() override;

    /*virtual*/ qint64 bytesToWrite() const override {
        return 0;
    }

    /*virtual*/ bool canReadLine() const override {
        return false;
    }

    /*virtual*/ qint64 readData(char *data, qint64 maxlen) override;

    /*virtual*/ qint64 readLineData(char *data, qint64 maxlen) override {
        Q_UNUSED(data);
        Q_UNUSED(maxlen);
        return 0;
    }

    /*virtual*/ qint64 writeData(const char *data, qint64 len) override {
        Q_UNUSED(data);
        Q_UNUSED(len);
        return 0;
    }

protected:
    QUrl m_url;


signals:

};

#endif // AUDIOSTREAMDEVICE_H
