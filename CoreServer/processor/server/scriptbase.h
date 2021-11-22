#ifndef SCRIPTBASE_H
#define SCRIPTBASE_H

#include <QObject>
#include "identifyable.h"

class ScriptBase : public Identifyable
{
    Q_OBJECT
public:
    explicit ScriptBase(QString name, QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCRIPTBASE_H
