#include "imagemagickthumnailmanager.h"

ImageMagickThumnailManager::ImageMagickThumnailManager(QString basePath, QObject *parent)
    : QObject{parent}
{
    timer.setInterval(1000 * 60 * 60);
    connect(&timer, &QTimer::timeout, this, &ImageMagickThumnailManager::onTimeout);
    timer.start();
}

void ImageMagickThumnailManager::onTimeout() {



}
