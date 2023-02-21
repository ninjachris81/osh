#include "httpdatamodelloader.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTimer>
#include <QEventLoop>
#include <QNetworkReply>

#include "dynamicdatamodel.h"

QString HttpDataModelLoader::LOADER_TYPE_NAME = QStringLiteral("http");

HttpDataModelLoader::HttpDataModelLoader(QUrl url, int requestTimeoutMs, QObject *parent) : DatamodelLoaderBase (parent), m_url(url), m_requestTimeoutMs(requestTimeoutMs)
{

}

DatamodelBase *HttpDataModelLoader::load(DatamodelLoadingOptions options) {
    iDebug() << Q_FUNC_INFO;

    QNetworkAccessManager nam;

    QUrl url(m_url);
    QNetworkRequest req(url);
    QNetworkReply *reply = nam.get(req);

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(m_requestTimeoutMs);
    loop.exec();

    if (timer.isActive()) {
        //QByteArray data =

        DynamicDatamodel* datamodel = new DynamicDatamodel();
        //datamodel->deserialize()

        return datamodel;
    } else {
        iWarning() << "Timeout while loading datamodel" << reply->errorString();
        Q_EMIT(error("Timeout while loading datamodel"));
        return nullptr;
    }
}

QString HttpDataModelLoader::typeName() {
    return LOADER_TYPE_NAME;
}


void HttpDataModelLoader::save(DatamodelBase* datamodel) {
    // TODO

    Q_EMIT(saved());
}
