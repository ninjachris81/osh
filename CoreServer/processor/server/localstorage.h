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

    Q_INVOKABLE bool contains(QString key);

    Q_INVOKABLE QVariant get(QString key, QVariant defaultValue = QVariant());

    Q_INVOKABLE void set(QString key, QVariant value);

    Q_INVOKABLE void unset(QString key);

private:
    QMap<QString, QVariant> m_values;

signals:

};

#endif // LOCALSTORAGE_H
