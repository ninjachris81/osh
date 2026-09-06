#pragma once

#include <QObject>

class CamBase : public QObject
{
    Q_OBJECT
public:
    explicit CamBase(QObject *parent = nullptr);

private:
    QString m_ip;

signals:

};

