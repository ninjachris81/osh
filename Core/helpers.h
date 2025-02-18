#ifndef HELPERS_H
#define HELPERS_H

#include <QtCore/QObject>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qmetatype.h>
#include <QDebug>

class Helpers {
public:

    template <typename Func1, typename Func2>
    static inline QMetaObject::Connection safeConnect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                     const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot, const char *signal2, const char *slot2,
                                     Qt::ConnectionType type = Qt::AutoConnection)
    {
        //typedef QtPrivate::FunctionPointer<Func1> SignalType;
        //typedef QtPrivate::FunctionPointer<Func2> SlotType;

        QMetaObject::Connection returnConnection = QObject::connect(sender, signal, receiver, slot, type);
        if (returnConnection == nullptr) {
            qWarning() << "Connect failed - trying fallback";
            returnConnection = QObject::connect(sender, signal2, receiver, slot2, type);
        }

        Q_ASSERT(returnConnection != nullptr);

        qDebug() << "Connection success";

        return returnConnection;
    }

    static QString generateMqttNameFromConstant(QString enumName) {
        QStringList parts = enumName.toLower().split('_', QString::SkipEmptyParts);
        for (int i=1; i<parts.size(); ++i) {
            parts[i].replace(0, 1, parts[i][0].toUpper());
        }

        return parts.join("");
    }




};

#endif // HELPERS_H
