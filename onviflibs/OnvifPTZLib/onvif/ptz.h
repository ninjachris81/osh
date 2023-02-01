#ifndef PTZ_H
#define PTZ_H

#include <QString>
class PTZ
{
public:
    PTZ();
    ~PTZ();

    struct PtzStatusInfo  {
        float panTiltX = 0;
        float panTiltY = 0;
        float zoomX = 0;
        bool zooming = false;
        bool moving = false;
    };

    static PtzStatusInfo getStatus(QString devServiceURL, QString profileToken);
    static void getNodes(QString devServiceURL);
    static void goToPreset(QString devServiceURL);

    static bool relativeMove(QString devServiceURL, QString profileToken, float x, float y);
    static bool continuousMove(QString devServiceURL, QString profileToken, float x, float y);
    static bool stop(QString devServiceURL);
};

#endif // PTZ_H
