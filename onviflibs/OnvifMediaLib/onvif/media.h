#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <string>
#include "soap/onvifmediaH.h"

class Media
{
public:
    Media();
    ~Media();

    struct VideoSourceConfiguration {
        QString token;
        QString name;
        QString sourceToken;
        int height = 0;
        int width = 0;
    };

    struct VideoEncoderConfiguration {
        QString token;
        QString name;
        int resolutionWidth = 0;
        int resolutionHeight = 0;
        tt__VideoEncoding encoding;
        float quality = 0;
    };

    static VideoSourceConfiguration getVideoSourceConfiguration(QString devServiceURL);
    static QList<VideoEncoderConfiguration> getVideoEncoderConfigurations(QString devServiceURL);
    static QStringList getProfileTokens(QString devServiceURL);
    static QString GetStreamUri(QString devServiceURL, QString profileToken);
};

#endif // MEDIA_H
