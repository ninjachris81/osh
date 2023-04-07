#ifndef IMAGEMAGICKTHUMNAILMANAGER_H
#define IMAGEMAGICKTHUMNAILMANAGER_H

#include <QObject>

#include <QTimer>
#include "imagemagickwrapper.h"

class ImageMagickThumnailManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageMagickThumnailManager(QString basePath, QObject *parent = nullptr);

private slots:
    void onTimeout();

private:
    QTimer timer;
    ImageMagickWrapper m_imWrapper;

signals:

};

#endif // IMAGEMAGICKTHUMNAILMANAGER_H
