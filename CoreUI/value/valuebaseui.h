#ifndef VALUEBASEUI_H
#define VALUEBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "value/valuebase.h"

class ValueBaseUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit ValueBaseUI(QObject *parent = nullptr);

    Q_PROPERTY(QString fullId READ fullId NOTIFY fullIdChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    Q_PROPERTY(QVariant rawValue READ rawValue NOTIFY rawValueChanged)

    QString fullId();
    bool isValid();
    QVariant rawValue();

protected:
    ValueBase* m_value;

signals:
    void fullIdChanged();
    void isValidChanged();
    void rawValueChanged();

public slots:
};

#endif // VALUEBASEUI_H
