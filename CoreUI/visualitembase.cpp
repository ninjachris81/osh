#include "visualitembase.h"

VisualItemBase::VisualItemBase(QObject *parent) : IdentifyableUI{parent}
{

}

int VisualItemBase::x() {
    return m_x;
}

int VisualItemBase::y() {
    return m_y;
}

void VisualItemBase::setX(int x) {
    m_x = x;
}

void VisualItemBase::setY(int y) {
    m_y = y;
}
