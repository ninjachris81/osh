#ifndef THREADSAFEQJSENGINE_H
#define THREADSAFEQJSENGINE_H

#include <QJSEngine>
#include <QThread>
#include <QDebug>

namespace ThreadSafeQJSEngine {

template <typename F>
auto call(QJSEngine* engine, F&& f) -> typename std::enable_if<!std::is_void<decltype(f())>::value, decltype(f())>::type
{
    if (QThread::currentThread() != engine->thread())
    {
        qDebug() << "Invoking in other thread";

        decltype(f()) result;
        QMetaObject::invokeMethod(engine, std::forward<F>(f), Qt::BlockingQueuedConnection, &result);
        return result;
    }
    else
    {
        qDebug() << "Same thread";

        return std::forward<F>(f)();
    }
}

template <typename F>
auto call(QJSEngine* engine, F&& f) -> typename std::enable_if<std::is_void<decltype(f())>::value, void>::type
{
    if (QThread::currentThread() != engine->thread())
    {
        qDebug() << "Invoking in other thread";
        QMetaObject::invokeMethod(engine, std::forward<F>(f), Qt::BlockingQueuedConnection);
    }
    else
    {
        qDebug() << "Same thread";
        std::forward<F>(f)();
    }
}

};

#endif // THREADSAFEQJSENGINE_H
