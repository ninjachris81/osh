#include "visualitembase.h"
#include "meta/metainfosupport.h"

#include <QDebug>

VisualItemBase::VisualItemBase(QObject *parent) : IdentifyableUI(parent), m_metaInfos(nullptr)
{
    MetaInfoSupport* metaInfoSupport = dynamic_cast<MetaInfoSupport*>(parent);
    if (metaInfoSupport!=nullptr) {
        m_metaInfos = metaInfoSupport->metaInfo();
    } else {
        //qWarning() << "No meta support";
    }
}

int VisualItemBase::x() {
    if (m_metaInfos == nullptr) return 0;
    return m_metaInfos->x();
}

int VisualItemBase::y() {
    if (m_metaInfos == nullptr) return 0;
    return m_metaInfos->y();
}

bool VisualItemBase::visible() {
    if (m_metaInfos == nullptr) return 0;
    return m_metaInfos->visible();
}

void VisualItemBase::setX(int x) {
    if (m_metaInfos == nullptr) return;
    m_metaInfos->setX(x);
}

void VisualItemBase::setY(int y) {
    if (m_metaInfos == nullptr) return;
    m_metaInfos->setY(y);
}

void VisualItemBase::setVisible(bool visible) {
    if (m_metaInfos == nullptr) return;
    m_metaInfos->setVisible(visible);
}
