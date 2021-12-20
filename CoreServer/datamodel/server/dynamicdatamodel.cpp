#include "dynamicdatamodel.h"

DynamicDatamodel::DynamicDatamodel(QObject *parent) : DatamodelBase("DynamicDatamodel", parent)
{

}

QByteArray DynamicDatamodel::serialize() {
    QByteArray data;

    return data;
}

void DynamicDatamodel::deserialize(QByteArray data) {

}
