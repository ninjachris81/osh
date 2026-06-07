#ifndef VALUEGROUP_H
#define VALUEGROUP_H

#include <QObject>

#include "sharedlib.h"

#include "identifyable.h"

class SHARED_LIB_EXPORT ValueGroup : public QObject, public Identifyable
{
    Q_OBJECT
public:
    ValueGroup();
    explicit ValueGroup(QString id, QObject *parent = nullptr);

signals:

public slots:
};

#endif // VALUEGROUP_H
