#include "identifyableui.h"

IdentifyableUI::IdentifyableUI(QObject *parent) : QObject (parent)
{
    m_parent = static_cast<Identifyable*>(parent);
}

QString IdentifyableUI::id() {
    return m_parent->id();
}
