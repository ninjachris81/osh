osh_add_qt_project(Core QT_MODULES Network Sql)
target_compile_definitions(Core PRIVATE MAKE_SHARED_LIB IS_OSH_CORE_SERVICE PROCESSOR_NATIVE_SUPPORT)
target_sources(Core PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/shared/actor_qt.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/shared/units_qt.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/shared/value_qt.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/shared/logging_categories_qt.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/shared/controllercmdtypes_qt.h"
)