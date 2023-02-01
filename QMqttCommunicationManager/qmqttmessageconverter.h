#ifndef QMQTTMESSAGECONVERTER_H
#define QMQTTMESSAGECONVERTER_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"

#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttTopicName>

class QMqttCommunicationManager;

class SHARED_LIB_EXPORT QMqttMessageConverter : public QObject
{
    Q_OBJECT
public:
    explicit QMqttMessageConverter(QObject *parent = nullptr);

    MessageBase *getMessage(QMqttMessage &message);

    QMqttTopicName getTopicName(MessageBase &message);

    void setCommManager(QMqttCommunicationManager* commManager);

private:
    QMqttCommunicationManager* m_commManager;

signals:

public slots:
};

#endif // QMQTTMESSAGECONVERTER_H
