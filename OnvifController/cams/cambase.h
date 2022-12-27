#ifndef CAMBASE_H
#define CAMBASE_H

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

#endif // CAMBASE_H
