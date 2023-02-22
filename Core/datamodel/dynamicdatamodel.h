#ifndef DYNAMICDATAMODEL_H
#define DYNAMICDATAMODEL_H

#include <QObject>

#include "sharedlib.h"

#include "datamodel/datamodelbase.h"
#include "datamodel/serializationsupport.h"

class SHARED_LIB_EXPORT DynamicDatamodel : public DatamodelBase
{
    Q_OBJECT
public:
    explicit DynamicDatamodel(QObject *parent = nullptr);

    QByteArray serialize();

    void deserialize(QByteArray data);

    void addActor(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties);
    void addValue(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties);

private:
    template <typename K, typename T> void serializeMap(QJsonObject &obj, QString name, QMap<K, T> map);
    template <typename K, typename T, typename SETUP_FUNC> void deserializeMap(QJsonObject obj, QString name, QMap<K, T> &map, SETUP_FUNC setupFunc);

signals:

public slots:
};

#endif // DYNAMICDATAMODEL_H
