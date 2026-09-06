#pragma once

#include <QObject>
#include <QQmlEngine>

#include "datamodel/datamodelmanager.h"
#include "datamodel/datamodelbaseui.h"
#include "identifyableui.h"

class DatamodelManagerUI : public DatamodelManager
{
    Q_OBJECT
    Q_DISABLE_COPY(DatamodelManagerUI)
public:
    explicit DatamodelManagerUI(QObject *parent = nullptr);

    Q_PROPERTY(DatamodelBaseUI* datamodel READ datamodel NOTIFY datamodelChanged)

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    DatamodelBaseUI* datamodel();

private:
    static DatamodelManagerUI* m_qmlInstance;
    DatamodelBaseUI* m_datamodel = nullptr;

signals:

public slots:
};

