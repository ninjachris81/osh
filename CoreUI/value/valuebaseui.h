#ifndef VALUEBASEUI_H
#define VALUEBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "value/valuebase.h"
#include "visualitembase.h"

class ValueBaseUI : public VisualItemBase
{
    Q_OBJECT
public:
    explicit ValueBaseUI(QObject *parent = nullptr);

    Q_PROPERTY(QString fullId READ fullId NOTIFY fullIdChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    Q_PROPERTY(QVariant rawValue READ rawValue NOTIFY rawValueChanged)
    Q_PROPERTY(value::VALUE_TYPE valueType READ valueType NOTIFY valueTypeChanged)
    Q_PROPERTY(double signalRate READ signalRate NOTIFY signalRateChanged)
    Q_PROPERTY(QString unitTypeSuffix READ unitTypeSuffix NOTIFY unitTypeSuffixChanged)

    Q_INVOKABLE void updateValue(QVariant newValue);

    QString fullId();
    bool isValid();
    QVariant rawValue();
    value::VALUE_TYPE valueType();
    double signalRate();
    QString unitTypeSuffix();

protected:
    ValueBase* m_value;

signals:
    void fullIdChanged();
    void isValidChanged();
    void rawValueChanged();
    void valueTypeChanged();
    void signalRateChanged();
    void unitTypeSuffixChanged();

public slots:
};

#endif // VALUEBASEUI_H
