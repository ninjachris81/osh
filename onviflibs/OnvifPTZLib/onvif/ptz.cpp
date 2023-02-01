#include "ptz.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include "soap/onvifptz.nsmap"
#include <QDateTime>
#include "soap/onvifptzPTZBindingProxy.h"



PTZ::PTZ()
{

}

PTZ::~PTZ()
{

}

PTZ::PtzStatusInfo PTZ::getStatus(QString devServiceURL, QString profileToken) {
    qDebug() << "ptz service test: goGetStatuses";

    PTZ::PtzStatusInfo ptzStatusInfo;

    PTZBindingProxy p;

    _ptzws__GetStatus in;

    in.ProfileToken = profileToken.toStdString();

    _ptzws__GetStatusResponse out;

    if (p.GetStatus(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok

        ptzStatusInfo.panTiltX = out.PTZStatus->Position->PanTilt->x;
        ptzStatusInfo.panTiltY = out.PTZStatus->Position->PanTilt->y;

        ptzStatusInfo.zoomX = out.PTZStatus->Position->Zoom->x;

        ptzStatusInfo.zooming = (*out.PTZStatus->MoveStatus->Zoom == tt__MoveStatus::tt__MoveStatus__MOVING);
        ptzStatusInfo.moving = (*out.PTZStatus->MoveStatus->PanTilt == tt__MoveStatus::tt__MoveStatus__MOVING);
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);

    }

    return ptzStatusInfo    ;
}

void PTZ::getNodes(QString devServiceURL) {

    qDebug() << "ptz service test: getNodes ptzservie url = " << devServiceURL.toStdString().data() << "\n";


    PTZBindingProxy p;

    _ptzws__GetNodes in;
    _ptzws__GetNodesResponse out;

    if (p.GetNodes(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << "PTZ node size = " << out.PTZNode.size();
        for(int i =0;i< out.PTZNode.size(); i++){
            //tt__PTZNode
            qDebug() << "Node name" << i << "=" << out.PTZNode[i]->Name->data();
            qDebug() << "Node home supported " << i << "=" << out.PTZNode[i]->HomeSupported;
        }

    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);

    }

    return ;
}

void PTZ::goToPreset(QString devServiceURL) {

    qDebug() << "ptz service test: goToPreset";

    PTZBindingProxy p;

    _ptzws__GotoPreset in;
    _ptzws__GotoPresetResponse out;

    in.PresetToken = "";
    in.ProfileToken = "";

    if (p.GotoPreset(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << "PTZ go to preset ok " ;

    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
    }

    return ;
}



bool PTZ::relativeMove(QString devServiceURL, QString profileToken, float x, float y) {
    qDebug() << Q_FUNC_INFO << profileToken << x << y;

    PTZBindingProxy p;

    _ptzws__RelativeMove in;
    _ptzws__RelativeMoveResponse out;

    tt__Vector2D panTilt;
    panTilt.x = x;
    panTilt.y = y;

    tt__PTZVector translation;
    translation.PanTilt = &panTilt;

    in.Translation = &translation;
    in.ProfileToken = profileToken.toStdString();

    if (p.RelativeMove(devServiceURL.toStdString().data(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << "PTZ rel move ok " ;
        return true;
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
        return false;
    }
}

bool PTZ::continuousMove(QString devServiceURL, QString profileToken, float x, float y) {
    qDebug() << Q_FUNC_INFO << profileToken << x << y;

    PTZBindingProxy p;

    _ptzws__ContinuousMove in;
    _ptzws__ContinuousMoveResponse out;

    tt__PTZSpeed speed;
    tt__Vector2D speedPan;

    speedPan.x = x;
    speedPan.y = y;
    speed.PanTilt = &speedPan;

    in.Velocity = &speed;
    in.ProfileToken = profileToken.toStdString();

    if (p.ContinuousMove(devServiceURL.toStdString().c_str(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << "PTZ cont move ok " ;
        return true;
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
        return false;
    }
}

bool PTZ::stop(QString devServiceURL) {
    qDebug() << Q_FUNC_INFO << devServiceURL;

    PTZBindingProxy p;

    _ptzws__Stop in;
    _ptzws__StopResponse out;

    if (p.Stop(devServiceURL.toStdString().c_str(), NULL, &in, out) == SOAP_OK) {
        //ok
        qDebug() << "PTZ stop ok " ;
        return true;
    } else {
        //error
        p.soap_print_fault(stderr);
        //fflush(stderr);
        return false;
    }
}

