#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <QString>
#include <string>
class Analytics
{
public:
    Analytics();
    ~Analytics();

    static void getGetServiceCapabilities(QString devServiceURL);

    static void getAnalyticsModules(QString devServiceURL);
};

#endif // ANALYTICS_H
