#ifndef ACTORCONFIG_H
#define ACTORCONFIG_H

#include <QObject>

class ActorConfig : public QObject
{
    Q_OBJECT
public:
    explicit ActorConfig(QObject *parent = nullptr);

signals:

};

#endif // ACTORCONFIG_H
