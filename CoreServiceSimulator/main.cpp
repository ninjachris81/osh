#include <QCoreApplication>
#include <QDebug>

#include "simulation/simulator.h"

//  not sure why this block is needed to compile in 5.12
#include "value/longvalue.h"
#include "value/stringvalue.h"
#include "actor/audioplaybackactor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    LocalConfig config;
    Simulator simulator(&config);

    //  not sure why this block is needed to compile in 5.12
    KnownDevice test1;
    ValueGroup test2;
    ShutterActor test3;
    IntegerValue test4;
    DoubleValue test5;
    LongValue test6;
    StringValue test7;
    AudioPlaybackActor test8;
    DigitalActor test9;
    BooleanValue test10;

    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\nprocessor.*=true\ndatamodel.*=true"));
    //QLoggingCategory::setFilterRules(QStringLiteral("device.*=false"));


    return a.exec();
}
