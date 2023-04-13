#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <QObject>
#include <QMap>
#include <QVariant>

#include "sharedlib.h"

class SHARED_LIB_EXPORT LocalStorage : public QObject
{
    Q_OBJECT
public:
    explicit LocalStorage(QObject *parent = nullptr);

    Q_INVOKABLE bool contains(QString method, QString key, QString uniqueId);

    Q_INVOKABLE QVariant get(QString method, QString key, QString uniqueId, QVariant defaultValue = QVariant());

    Q_INVOKABLE void set(QString method, QString key, QString uniqueId, QVariant value);

    Q_INVOKABLE void unset(QString method, QString key, QString uniqueId);

    Q_INVOKABLE bool containsObject(QString method, QString key, QString uniqueId);

    Q_INVOKABLE void setObject(QString method, QString key, QString uniqueId, QObject* obj);

    Q_INVOKABLE QObject* getObject(QString method, QString key, QString uniqueId);

    Q_INVOKABLE void unsetObject(QString method, QString key, QString uniqueId);


private:
    static QString getId(QString method, QString key, QString uniqueId);
    QMap<QString, QVariant> m_values;
    QMap<QString, QObject*> m_objects;

signals:

};

#endif // LOCALSTORAGE_H
