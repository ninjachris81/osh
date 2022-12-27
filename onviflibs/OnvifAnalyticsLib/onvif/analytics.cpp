#include "analytics.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include "soap/onvifanalytics.nsmap"
#include "soap/onvifanalyticsRuleEngineBindingProxy.h"

Analytics::Analytics()
{

}

Analytics::~Analytics()
{

}
void Analytics::getGetServiceCapabilities(QString devServiceURL) {

    qDebug() << "Analytics service test: getGetServiceCapabilities";

    RuleEngineBindingProxy d;

    _analyticsws__GetServiceCapabilities in;
    _analyticsws__GetServiceCapabilitiesResponse out;

    if (d.GetServiceCapabilities(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        if(out.Capabilities != NULL){
            if (out.Capabilities->AnalyticsModuleSupport != nullptr) qDebug() << *out.Capabilities->AnalyticsModuleSupport;
            if (out.Capabilities->CellBasedSceneDescriptionSupported != nullptr) qDebug() << *out.Capabilities->CellBasedSceneDescriptionSupported;
            if (out.Capabilities->RuleSupport != nullptr) qDebug() << *out.Capabilities->RuleSupport;
        }

    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return ;
}

void Analytics::getAnalyticsModules(QString devServiceURL) {
    qDebug() << Q_FUNC_INFO;

    RuleEngineBindingProxy d;

    _analyticsws__GetAnalyticsModules in;
    _analyticsws__GetAnalyticsModulesResponse out;

    if (d.GetAnalyticsModules(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        for (quint8 i = 0;i<out.AnalyticsModule.size(); i++ ){
            qDebug() << QString::fromStdString(out.AnalyticsModule.at(i)->Name);
            qDebug() << QString::fromStdString(out.AnalyticsModule.at(i)->Type);
        }

    } else {
        //error
        d.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return ;
}

