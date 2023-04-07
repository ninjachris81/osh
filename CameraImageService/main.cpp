#include "config/localconfig.h"
#include "imagemagickwrapper.h"
#include <QCoreApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocalConfig config;

    ImageMagickWrapper im;

    qDebug() << im.compareImages("D:\\Temp\\img\\20230404\\images\\A23040405343011.jpg", "D:\\Temp\\img\\20230404\\images\\A23040405343112.jpg");

    return a.exec();
}
