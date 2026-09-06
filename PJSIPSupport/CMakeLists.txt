osh_add_qt_project(PJSIPSupport)
target_compile_definitions(PJSIPSupport PRIVATE MAKE_SHARED_LIB)
target_link_libraries(PJSIPSupport PRIVATE Core)
if(UNIX AND NOT APPLE)
    set(PJPROJECT_DIR "${PROJECT_SOURCE_DIR}/pjproject")
    target_compile_definitions(PJSIPSupport PRIVATE PJ_AUTOCONF=1)
    target_include_directories(PJSIPSupport PRIVATE
        "${PJPROJECT_DIR}/pjsip/include" "${PJPROJECT_DIR}/pjlib/include"
        "${PJPROJECT_DIR}/pjlib-util/include" "${PJPROJECT_DIR}/pjmedia/include"
        "${PJPROJECT_DIR}/pjnath/include" "${PJPROJECT_DIR}/third_party/include"
    )
    target_link_directories(PJSIPSupport PRIVATE
        "${PJPROJECT_DIR}/pjsip/lib" "${PJPROJECT_DIR}/pjlib/lib"
        "${PJPROJECT_DIR}/pjlib-util/lib" "${PJPROJECT_DIR}/pjmedia/lib"
        "${PJPROJECT_DIR}/pjnath/lib" "${PJPROJECT_DIR}/third_party/lib"
    )
    target_link_libraries(PJSIPSupport PRIVATE
        pjsip pjsip-simple pjsua2 pjsua pjsip-ua pj pjlib-util
        pjmedia pjmedia-audiodev pjmedia-codec pjnath
        srtp resample speex gsmcodec ilbccodec
    )
elseif(WIN32)
    target_compile_definitions(PJSIPSupport PUBLIC PJ_USE_STUBS)
endif()