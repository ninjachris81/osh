#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "simulation/simulator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("config", "Configuration");
    parser.process(app);

    qDebug() << Q_FUNC_INFO;

    LocalConfig config(parser.positionalArguments().value(0, "config.ini"));
    Simulator simulator(&config);

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nprocessor.*=true\ndatamodel.*=true"));
    //QLoggingCategory::setFilterRules(QStringLiteral("device.*=false"));

    simulator.init();

    return app.exec();
}
