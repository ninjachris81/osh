#include "datamodelloaderbase.h"

DatamodelLoaderBase::DatamodelLoaderBase(QObject *parent) : Identifyable("DatamodelLoaderBase"), QObject(parent)
{

}

LogCat::LOGCAT DatamodelLoaderBase::logCat() {
    return LogCat::DATAMODEL;
}
