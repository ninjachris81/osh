#ifndef VALUEMANAGERUI_H
#define VALUEMANAGERUI_H

#include <QObject>

#include "value/valuemanagerbase.h"

class ValueManagerUI : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerUI(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg);

signals:

public slots:
};

#endif // VALUEMANAGERUI_H
