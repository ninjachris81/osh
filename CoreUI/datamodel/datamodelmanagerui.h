#ifndef DATAMODELMANAGERUI_H
#define DATAMODELMANAGERUI_H

#include <QObject>
#include <QQmlEngine>

#include "datamodel/server/datamodelmanager.h"
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
    static DatamodelManagerUI* m_instance;
    DatamodelBaseUI* m_datamodel = nullptr;

signals:

public slots:
};

#endif // DATAMODELMANAGERUI_H
