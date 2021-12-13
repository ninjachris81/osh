#ifndef VISUALITEMBASE_H
#define VISUALITEMBASE_H

#include <QObject>
#include "identifyableui.h"

class VisualItemBase : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit VisualItemBase(QObject *parent = nullptr);

    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)

    int x();
    int y();

    void setX(int x);
    void setY(int y);

protected:
    int m_x = 0;
    int m_y = 0;

signals:
    void xChanged();
    void yChanged();

};

#endif // VISUALITEMBASE_H
