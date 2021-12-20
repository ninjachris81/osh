#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <QObject>
#include <QMap>
#include <QVariant>

class LocalStorage : public QObject
{
    Q_OBJECT
public:
    explicit LocalStorage(QObject *parent = nullptr);

    Q_INVOKABLE bool contains(QString key);

    Q_INVOKABLE QVariant get(QString key, QVariant defaultValue = QVariant());

    Q_INVOKABLE void set(QString key, QVariant value);

private:
    QMap<QString, QVariant> m_values;

signals:

};

#endif // LOCALSTORAGE_H
