#include "imagemagickwrapper.h"

ImageMagickWrapper::ImageMagickWrapper(QObject *parent)
    : QObject{parent}
{
    InitializeMagick(NULL);
}

double ImageMagickWrapper::compareImages(QString file1, QString file2) {
    Image img1;
    Image img2;

    img1.read(file1.toStdString().c_str());
    img2.read(file2.toStdString().c_str());

    return img1.compare(img2, MetricType::MeanAbsoluteErrorMetric);
}
