#include "datamodelloaderbase.h"

DatamodelLoaderBase::DatamodelLoaderBase(QObject *parent) : Identifyable("DatamodelLoaderBase", parent)
{

}

LogCat::LOGCAT DatamodelLoaderBase::logCat() {
    return LogCat::DATAMODEL;
}
