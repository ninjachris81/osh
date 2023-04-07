#ifndef IMAGEMAGICKWRAPPER_H
#define IMAGEMAGICKWRAPPER_H

#include <QObject>

#include <Magick++.h>

using namespace Magick;

class ImageMagickWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ImageMagickWrapper(QObject *parent = nullptr);

    double compareImages(QString file1, QString file2);
signals:

};

#endif // IMAGEMAGICKWRAPPER_H
