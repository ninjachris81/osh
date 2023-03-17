#ifndef AUDIOPLAYLISTDEVICE_H
#define AUDIOPLAYLISTDEVICE_H

#include "qdir.h"
#include "qrandom.h"
#include <QObject>
#include <QIODevice>
#include <QFile>

class AudioPlaylistDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioPlaylistDevice(QString playlistUrl, QObject *parent = nullptr);

    /*virtual*/ bool isSequential() const override {
        return !m_loop;
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

    void readNext();

    void next();
    void previous();

protected:
    QString m_playlistUrl;
    QFile m_currentFile;
    int m_currentTrack = -1;
    bool m_loop = true;     // TBD: support non-looping non-sequential
    bool m_randomize = true;
    QRandomGenerator m_rnd;

    QStringList m_tracks;

    bool parsePlaylist();

    static bool isUtf8(const char* string);


signals:

};

#endif // AUDIOPLAYLISTDEVICE_H
