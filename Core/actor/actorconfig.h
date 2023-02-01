#ifndef ACTORCONFIG_H
#define ACTORCONFIG_H

#include <QObject>

#include "sharedlib.h"

class SHARED_LIB_EXPORT ActorConfig : public QObject
{
    Q_OBJECT
public:
    explicit ActorConfig(QObject *parent = nullptr);

signals:

};

#endif // ACTORCONFIG_H
