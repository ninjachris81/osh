#ifndef VALUEGROUP_H
#define VALUEGROUP_H

#include <QObject>

#include "identifyable.h"

class ValueGroup : public Identifyable
{
    Q_OBJECT
public:
    explicit ValueGroup(QString id, QObject *parent = nullptr);

signals:

public slots:
};

#endif // VALUEGROUP_H
