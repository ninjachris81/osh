#include "datamodelloaderbase.h"

DatamodelLoaderBase::DatamodelLoaderBase(QObject *parent) : QObject(parent), Identifyable("DatamodelLoaderBase")
{

}

LogCat::LOGCAT DatamodelLoaderBase::logCat() {
    return LogCat::DATAMODEL;
}
