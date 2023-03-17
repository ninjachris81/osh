#include "audioplaylistdevice.h"
#include "qdir.h"
#include "qfileinfo.h"
#include "qrandom.h"
#include "qregularexpression.h"
#include "qtextcodec.h"

#include <QDebug>
#include <QFile>

AudioPlaylistDevice::AudioPlaylistDevice(QString playlistUrl, QObject *parent)
    : QIODevice{parent}, m_playlistUrl(playlistUrl)
{

}

bool AudioPlaylistDevice::open(OpenMode mode) {
    if (mode == ReadOnly) {
        if (parsePlaylist()) {
            readNext();
            QIODevice::open(mode);
            return true;
        } else {
            qWarning() << "Empty playlist or error";
            return false;
        }
    } else {
        qWarning() << "Only readonly mode supported";
        return false;
    }
}

void AudioPlaylistDevice::close() {
    qDebug() << Q_FUNC_INFO;
    QIODevice::close();
}

void AudioPlaylistDevice::readNext() {
    // calculate next track index
    if (m_randomize) {
        m_currentTrack = m_rnd.bounded(m_tracks.size()-1);
    } else {
        if (m_currentTrack == -1) {
            m_currentTrack = 0;
        } else {
            if (m_currentTrack == m_tracks.size()-1) {
                m_currentTrack = 0;
            } else {
                m_currentTrack++;
            }
        }
    }

    if (m_currentFile.fileName() == m_tracks.at(m_currentTrack)) {
        // same file again
        qDebug() << "New file is same as old one";
        m_currentFile.reset();
    } else {
        if (m_currentFile.isOpen()) {
            m_currentFile.close();
        }

        m_currentFile.setFileName(m_tracks.at(m_currentTrack));
        if (m_currentFile.exists()) {
            if (m_currentFile.open(ReadOnly)) {
                qDebug() << "File opened" << m_currentFile.fileName();
            } else {
                qWarning() << "Cannot open file" << m_currentFile.fileName();
                readNext();
            }
        } else {
            qWarning() << "File not found" << m_currentFile.fileName();
        }
    }
}

qint64 AudioPlaylistDevice::readData(char *data, qint64 maxlen) {
    if (m_currentFile.isReadable()) {

        qint64 dataRead = m_currentFile.read(data, maxlen);
        if (m_currentFile.bytesAvailable() == 0) {
            readNext();
        }

        return dataRead;
    } else {
        qWarning() << "Current file not readable" << m_currentFile.fileName();
    }

}

void AudioPlaylistDevice::next() {

}

void AudioPlaylistDevice::previous() {

}

bool AudioPlaylistDevice::parsePlaylist() {
    const char kStandardM3uTextEncoding[] = "Windows-1250";
    const char kM3uHeader[] = "#EXTM3U";
    const auto kUniveralEndOfLineRegEx = QRegularExpression(QStringLiteral("\r\n|\r|\n"));
    const char kM3uCommentPrefix[] = "#";

    m_tracks.clear();

    QFile file(m_playlistUrl);
    if (file.open(QIODevice::ReadOnly)) {
        QFileInfo fileInfo(m_playlistUrl);
        QDir basePath;
        if (fileInfo.isAbsolute()) {
            basePath = fileInfo.dir();
        }

        QByteArray byteArray = file.readAll();
        QString fileContents;
        if (AudioPlaylistDevice::isUtf8(byteArray.constData())) {
            fileContents = QString::fromUtf8(byteArray);
        } else {
            // FIXME: replace deprecated QTextCodec with direct usage of libicu
            fileContents = QTextCodec::codecForName(kStandardM3uTextEncoding)
                                   ->toUnicode(byteArray);
        }

        if (!fileContents.startsWith(kM3uHeader)) {
            qWarning() << "M3U playlist file" << m_playlistUrl << "does not start with" << kM3uHeader;
        }

        const QStringList fileLines = fileContents.split(kUniveralEndOfLineRegEx);
        for (const QString& line : fileLines) {
            if (line.startsWith(kM3uCommentPrefix)) {
                // Skip lines with comments
                continue;
            }
            if (!line.isEmpty()) {
                QString filePath = line;

                QFileInfo fileInfo(filePath);
                if (!fileInfo.isAbsolute()) {
                    filePath = basePath.absoluteFilePath(filePath);
                }

                m_tracks.append(filePath);
            }
        }
    } else {
        qWarning() << "Failed to open playlist file" << m_playlistUrl;
    }

    qDebug() << "Files in playlist" << m_tracks.size();

    file.close();

    return !m_tracks.isEmpty();
}

bool AudioPlaylistDevice::isUtf8(const char* string) {
    if (!string) {
        return false;
    }

    const unsigned char* bytes = (const unsigned char *)string;
    while (*bytes) {
        if(     (// ASCII
                        bytes[0] == 0x09 ||
                        bytes[0] == 0x0A ||
                        bytes[0] == 0x0D ||
                        (0x20 <= bytes[0] && bytes[0] <= 0x7E)
                )
        ) {
                bytes += 1;
                continue;
        }

        if(     (// non-overlong 2-byte
                        (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF)
                )
        ) {
                bytes += 2;
                continue;
        }

        if(     (// excluding overlongs
                        bytes[0] == 0xE0 &&
                        (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// straight 3-byte
                        ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
                                bytes[0] == 0xEE ||
                                bytes[0] == 0xEF) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// excluding surrogates
                        bytes[0] == 0xED &&
                        (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                )
        ) {
                bytes += 3;
                continue;
        }

        if(     (// planes 1-3
                        bytes[0] == 0xF0 &&
                        (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// planes 4-15
                        (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
                        (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// plane 16
                        bytes[0] == 0xF4 &&
                        (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
                        (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                        (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                )
        ) {
                bytes += 4;
                continue;
        }

        return false;
    }

    return true;
}
