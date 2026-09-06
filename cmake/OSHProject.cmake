function(osh_add_qt_project target_name)
    set(options)
    set(one_value_args)
    set(multi_value_args QT_MODULES)
    cmake_parse_arguments(OSH "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    file(GLOB_RECURSE target_sources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
    )
    if(NOT target_sources)
        message(FATAL_ERROR "No sources found for ${target_name}")
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" OR EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
        add_executable(${target_name} ${target_sources})
    else()
        add_library(${target_name} SHARED ${target_sources})
    endif()

    target_compile_definitions(${target_name} PRIVATE QT_DEPRECATED_WARNINGS)
    target_compile_options(${target_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    )
    target_include_directories(${target_name} PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/Core"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(${target_name} PRIVATE Qt6::Core)
    foreach(module IN LISTS OSH_QT_MODULES)
        target_link_libraries(${target_name} PRIVATE Qt6::${module})
    endforeach()
endfunction()