osh_add_qt_project(RS485RelayController QT_MODULES SerialPort SerialBus)
target_include_directories(RS485RelayController PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_compile_definitions(RS485RelayController PRIVATE MAKE_SHARED_LIB)
target_link_libraries(RS485RelayController PRIVATE Core CoreSerial)