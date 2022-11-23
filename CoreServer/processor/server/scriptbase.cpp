#include "scriptbase.h"

ScriptBase::ScriptBase(QString name, QObject *parent) : Identifyable(name), QObject(parent)
{

}

LogCat::LOGCAT ScriptBase::logCat() {
    return LogCat::PROCESSOR;
}
