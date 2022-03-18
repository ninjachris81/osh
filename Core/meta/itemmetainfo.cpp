#include "itemmetainfo.h"

void ItemMetaInfo::serialize(QJsonObject &obj) {
    QJsonObject metaObj;

    metaObj.insert("x", m_x);
    metaObj.insert("y", m_y);
    metaObj.insert("visible", m_visible);
    metaObj.insert("description", m_description);

    obj.insert("meta", metaObj);
}

void ItemMetaInfo::deserialize(QJsonObject obj) {
    QJsonObject metaObj = obj.value("meta").toObject();

    m_x = metaObj.value("x").toInt();
    m_y = metaObj.value("y").toInt();
    m_visible = metaObj.value("visible").toBool();
    m_description = metaObj.value("description").toString();
}


int ItemMetaInfo::x() {
    return m_x;
}

int ItemMetaInfo::y() {
    return m_y;
}

bool ItemMetaInfo::visible() {
    return m_visible;
}

QString ItemMetaInfo::description() {
    return m_description;
}

void ItemMetaInfo::setX(int x) {
    m_x = x;
}

void ItemMetaInfo::setY(int y) {
    m_y = y;
}

void ItemMetaInfo::setVisible(bool visible) {
    m_visible = visible;
}

void ItemMetaInfo::setDescription(QString description) {
    m_description = description;
}
