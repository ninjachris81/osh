osh_add_qt_project(OBISController QT_MODULES SerialPort SerialBus)
target_compile_definitions(OBISController PRIVATE MAKE_SHARED_LIB)
target_link_libraries(OBISController PRIVATE Core CoreSerial)

find_library(LIBSML_LIBRARY NAMES sml)
if(LIBSML_LIBRARY)
    get_filename_component(LIBSML_LIBRARY_DIR "${LIBSML_LIBRARY}" DIRECTORY)
    find_path(LIBSML_INCLUDE_DIR
        NAMES sml/sml_file.h
        HINTS
            "${LIBSML_LIBRARY_DIR}/../include"
            "${LIBSML_LIBRARY_DIR}/../../include"
        REQUIRED
    )
    target_include_directories(OBISController PRIVATE "${LIBSML_INCLUDE_DIR}")
    target_link_libraries(OBISController PRIVATE ${LIBSML_LIBRARY})
else()
    enable_language(C)
    file(GLOB_RECURSE LIBSML_SOURCES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/libsml/sml/src/*.c"
    )
    add_library(OBISLibSML STATIC ${LIBSML_SOURCES})
    set_target_properties(OBISLibSML PROPERTIES
        C_STANDARD 99
        C_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
    )
    target_include_directories(OBISLibSML PUBLIC "${PROJECT_SOURCE_DIR}/libsml/sml/include")

    if(UNIX AND NOT APPLE)
        find_library(LIBSML_UUID_LIBRARY NAMES uuid REQUIRED)
        target_link_libraries(OBISLibSML PUBLIC ${LIBSML_UUID_LIBRARY})
    endif()

    target_link_libraries(OBISController PRIVATE OBISLibSML)
endif()