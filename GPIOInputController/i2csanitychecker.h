#ifndef I2CSANITYCHECKER_H
#define I2CSANITYCHECKER_H

#include <QObject>
#include <QTimer>

#define I2C_CHECK_INTERVAL 30000

class I2CSanityChecker : public QObject
{
    Q_OBJECT
public:
    explicit I2CSanityChecker(QObject *parent = nullptr);


    void setBus(int i2cBus);
    void setDevList(QList<int> devList);

    void start();

private slots:
    void onCheckBusses();

private:
    QTimer m_Timer;
    int m_i2cBus;
    QList<int> m_devList;

signals:
    void i2cNotDetected();

};

#endif // I2CSANITYCHECKER_H
