#include <QCoreApplication>
#include <QDebug>

#include "simulation/simulator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    LocalConfig config;
    Simulator simulator(&config);

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nprocessor.*=true\ndatamodel.*=true"));
    //QLoggingCategory::setFilterRules(QStringLiteral("device.*=false"));

    simulator.init();

    return a.exec();
}
