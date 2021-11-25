#include "commonscripts.h"

CommonScripts::CommonScripts(QJSEngine *engine, QObject *parent) : ScriptBase("CommonScripts", parent), m_engine(engine)
{

}

/*
 * Returns true if the function has been called
*/
bool CommonScripts::ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant invalidValue, QJSValue function) {
    iDebug() << Q_FUNC_INFO << actualValue << expectedValue;

    QVariant actual = actualValue->isValid() ? actualValue->rawValue() : invalidValue;
    QVariant expected = expectedValue->isValid() ?  expectedValue->rawValue() : invalidValue;

    if (actual != expected) {
        // call func
        if (function.isCallable()) {
            iDebug() << "Call function" << actual << expected;
            QJSValueList paramList;
            paramList << m_engine->toScriptValue(expected);
            function.call(paramList);
            return true;
        } else {
            iWarning() << "Parameter is not a function" << function.toString();
        }
    } else {
        iDebug() << "Same value" << actual << expected;
    }

    return false;
}
