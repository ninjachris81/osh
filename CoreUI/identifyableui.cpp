#include "identifyableui.h"

IdentifyableUI::IdentifyableUI(Identifyable *parent) : QObject (), m_parent(parent)
{
}

QString IdentifyableUI::id() {
    return m_parent->id();
}
