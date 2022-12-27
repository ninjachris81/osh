#ifndef JIDETECH_P1_4X_H
#define JIDETECH_P1_4X_H

#include <QObject>
#include "cambase.h"

class JideTech_P1_4X : public CamBase
{
    Q_OBJECT
public:
    explicit JideTech_P1_4X(QObject *parent = nullptr);

signals:

};

#endif // JIDETECH_P1_4X_H
