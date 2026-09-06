osh_add_qt_project(OnvifController)
target_compile_definitions(OnvifController PRIVATE MAKE_SHARED_LIB)
target_link_libraries(OnvifController PRIVATE
    Core OnvifPTZLib OnvifAnalyticsLib OnvifMediaLib OnvifEventLib
    OnvifDeviceLib OnvifDeviceIOLib OnvifImagingLib OnvifDiscoveryLib
)