#ifndef MACROS_H
#define MACROS_H

#include <QtGlobal>
#include <QLoggingCategory>

#define REQUIRE_MANAGER(manager) Q_ASSERT(getManager<manager>(manager::MANAGER_ID) != nullptr)
#define REQUIRE_MANAGER_X(parent, manager) Q_ASSERT(parent->getManager<manager>(manager::MANAGER_ID) != nullptr)

#define iDebug() qCDebug(QLoggingCategory(this->logCatName().toUtf8()))
#define iInfo() qCInfo(QLoggingCategory(this->logCatName().toUtf8()))
#define iWarning() qCWarning(QLoggingCategory(this->logCatName().toUtf8()))
#define iCritical() qCCritical(QLoggingCategory(this->logCatName().toUtf8()))

#endif // MACROS_H
