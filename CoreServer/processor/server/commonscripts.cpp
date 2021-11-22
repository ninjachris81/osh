#include "commonscripts.h"

CommonScripts::CommonScripts(QObject *parent) : ScriptBase("CommonScripts", parent)
{

}

/*
 * Returns true if the function has been called
*/
bool CommonScripts::ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant actualInvalid, QJSValue function) {
    QVariant actual = actualValue->isValid() ? actualValue->rawValue() : actualInvalid;
    QVariant expected = expectedValue->rawValue();

    if (actual != expected) {
        // call func
        if (function.isCallable()) {
            function.call();
            return true;
        } else {
            iWarning() << "Parameter is not a function" << function.toString();
        }
    }

    return false;
}
