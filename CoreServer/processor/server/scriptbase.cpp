#include "scriptbase.h"

ScriptBase::ScriptBase(QString name, QObject *parent) : Identifyable(name, parent)
{

}

LogCat::LOGCAT ScriptBase::logCat() {
    return LogCat::PROCESSOR;
}
