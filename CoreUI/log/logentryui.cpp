#include "logentryui.h"

LogEntryUI::LogEntryUI(QString fullDeviceId, QString type, QString msg, QObject *parent) : QObject(parent), m_fullDeviceId(fullDeviceId), m_type(type), m_msg(msg)
{

}

QString LogEntryUI::fullDeviceId() {
    return m_fullDeviceId;
}

QString LogEntryUI::type() {
    return m_type;
}

QString LogEntryUI::msg() {
    return m_msg;
}
