#ifndef ITEMMETAINFO_H
#define ITEMMETAINFO_H

#include <QObject>

#include "sharedlib.h"

#include "datamodel/serializationsupport.h"

class SHARED_LIB_EXPORT ItemMetaInfo : private SerializationSupport
{

public:
    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    int x();
    int y();
    bool visible();
    QString description();

    void setX(int x);
    void setY(int y);
    void setVisible(bool visible);
    void setDescription(QString description);

private:
    int m_x = 0;
    int m_y = 0;
    bool m_visible = true;
    QString m_description = "";

};

#endif // ITEMMETAINFO_H
