#ifndef VISUALITEMBASE_H
#define VISUALITEMBASE_H

#include <QObject>
#include "identifyableui.h"
#include "meta/itemmetainfo.h"

class VisualItemBase : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit VisualItemBase(QObject *parent = nullptr);

    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

    int x();
    int y();
    bool visible();

    void setX(int x);
    void setY(int y);
    void setVisible(bool visible);

protected:
    ItemMetaInfo *m_metaInfos;

signals:
    void xChanged();
    void yChanged();
    void visibleChanged();

};

#endif // VISUALITEMBASE_H
