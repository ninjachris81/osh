#pragma once

#include <QtGlobal>
#include <QLoggingCategory>

#define REQUIRE_MANAGER(manager) Q_ASSERT(getManager<manager>(manager::MANAGER_ID) != nullptr)
#define REQUIRE_MANAGER_X(parent, manager) Q_ASSERT(parent->getManager<manager>(manager::MANAGER_ID) != nullptr)

#define iDebug() qDebug().noquote().nospace() << "[" << this->logCatName() << "] "
//#define iDebug() qCDebug(QLoggingCategory(this->logCatName().toLatin1().constData()))

#define iInfo() qInfo().noquote().nospace() << "[" << this->logCatName() << "] "
//#define iInfo() qCInfo(QLoggingCategory(this->logCatName().toLatin1().constData()))

#define iWarning() qWarning().noquote().nospace() << "[" << this->logCatName() << "] "
//#define iWarning() qCWarning(QLoggingCategory(this->logCatName().toLatin1().constData()))

#define iCritical() qCritical().noquote().nospace() << "[" << this->logCatName() << "] "
//#define iCritical() qCCritical(QLoggingCategory(this->logCatName().toLatin1().constData()))

#define iFatal() qFatal().noquote().nospace() << "[" << this->logCatName() << "] "
//#define iFatal() qCFatal(QLoggingCategory(this->logCatName().toLatin1().constData()))
