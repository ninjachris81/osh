#ifndef SCRIPTBASE_H
#define SCRIPTBASE_H

#include <QObject>
#include "identifyable.h"

class ScriptBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit ScriptBase(QString name, QObject *parent = nullptr);

    LogCat::LOGCAT logCat();

signals:

public slots:
};

#endif // SCRIPTBASE_H
