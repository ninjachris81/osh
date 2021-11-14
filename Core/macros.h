#ifndef MACROS_H
#define MACROS_H

#include <QtGlobal>

#define REQUIRE_MANAGER(manager) Q_ASSERT(getManager<manager>(manager::MANAGER_NAME) != nullptr)
#define REQUIRE_MANAGER_X(parent, manager) Q_ASSERT(parent->getManager<manager>(manager::MANAGER_NAME) != nullptr)

#endif // MACROS_H
