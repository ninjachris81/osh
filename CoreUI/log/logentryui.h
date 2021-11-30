#ifndef LOGENTRYUI_H
#define LOGENTRYUI_H

#include <QObject>

class LogEntryUI : public QObject
{
    Q_OBJECT
public:
    explicit LogEntryUI(QString deviceId, QString type, QString msg, QObject *parent = nullptr);

    Q_PROPERTY(QString fullDeviceId READ fullDeviceId NOTIFY fullDeviceIdChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString msg READ msg NOTIFY msgChanged)

    QString fullDeviceId();
    QString type();
    QString msg();

private:
    QString m_fullDeviceId;
    QString m_type;
    QString m_msg;

signals:
    void msgChanged();
    void typeChanged();
    void fullDeviceIdChanged();

public slots:
};

#endif // LOGENTRYUI_H
