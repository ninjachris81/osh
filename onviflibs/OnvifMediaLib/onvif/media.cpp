#include "media.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include "soap/onvifmedia.nsmap"
#include "soap/onvifmediaMediaBindingProxy.h"

Media::Media()
{

}

Media::~Media()
{

}

Media::VideoSourceConfiguration Media::getVideoSourceConfiguration(QString devServiceURL) {
    qDebug() << Q_FUNC_INFO;

    VideoSourceConfiguration configuration;

    MediaBindingProxy p;

    _mediaws__GetVideoSourceConfiguration in;
    _mediaws__GetVideoSourceConfigurationResponse out;

    if (p.GetVideoSourceConfiguration(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        auto config = out.Configuration;
        configuration.token = QString::fromStdString(config->token);
        configuration.sourceToken = QString::fromStdString(config->SourceToken);
        configuration.name = QString::fromStdString(config->Name);
        configuration.height = config->Bounds->height;
        configuration.width = config->Bounds->width;
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return configuration;
}

QList<Media::VideoEncoderConfiguration> Media::getVideoEncoderConfigurations(QString devServiceURL) {
    QList<Media::VideoEncoderConfiguration> videoEncoderConfigurations;

    MediaBindingProxy p;

    _mediaws__GetVideoEncoderConfigurations in;
    _mediaws__GetVideoEncoderConfigurationsResponse out;

    if (p.GetVideoEncoderConfigurations(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        auto configs = out.Configurations;
        for(quint8 i =0;i<configs.size(); ++i){
            auto config = configs.at(i);

            Media::VideoEncoderConfiguration configuration;
            configuration.token = QString::fromStdString(config->token);
            configuration.name = QString::fromStdString(config->Name);
            configuration.encoding = config->Encoding;
            configuration.resolutionWidth = config->Resolution->Width;
            configuration.resolutionHeight = config->Resolution->Height;
            configuration.quality = config->Quality;

            videoEncoderConfigurations.append(configuration);
        }
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return videoEncoderConfigurations;
}

QStringList Media::getProfileTokens(QString devServiceURL) {

    QStringList tokens;
    qDebug() << "media service test: getProfileTokens";

    MediaBindingProxy p;

    _mediaws__GetProfiles in;
    _mediaws__GetProfilesResponse out;

    if (p.GetProfiles(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        std::vector<tt__Profile* >  profiles = out.Profiles;
        for(quint8 i =0;i< profiles.size(); ++i){
            tokens << QString::fromStdString(profiles.at(i)->token);
        }
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return tokens;
}


QString Media::GetStreamUri(QString devServiceURL, QString profileToken) {
    qDebug() << Q_FUNC_INFO << devServiceURL << profileToken;

    MediaBindingProxy p;

    _mediaws__GetStreamUri in;
    _mediaws__GetStreamUriResponse out;

    in.ProfileToken = profileToken.toStdString().c_str();

    if (p.GetStreamUri(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        return QString::fromStdString(out.MediaUri->Uri);
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return "";
}

