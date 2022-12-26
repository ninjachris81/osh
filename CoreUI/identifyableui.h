#ifndef IDENTIFYABLEUI_H
#define IDENTIFYABLEUI_H

#include <QObject>
#include "identifyable.h"

class IdentifyableUI : public QObject
{
    Q_OBJECT
public:
    explicit IdentifyableUI(Identifyable *parent = nullptr);

    Q_PROPERTY(QString id READ id NOTIFY idChanged)

    QString id();

protected:
    Identifyable* m_parent;

signals:
    void idChanged();

public slots:
};

#endif // IDENTIFYABLEUI_H
