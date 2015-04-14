set(lms7controlLogic_src_files
	ADF_module.cpp
	Algorithms.cpp
	CoefficientFileParser.cpp
	ConnectionCOM.cpp
	ConnectionManager.cpp
	ConnectionUSB.cpp
	LMS7002_MainControl.cpp
	lmSemaphore.cpp
	lmThread.cpp
	MCU_BD.cpp
	MessageLog.cpp
	PLL_CGEN.cpp
	PLL_SX.cpp
	Programmer.cpp
	RegistersMap.cpp
	Si5351C.cpp
	SignalHandler.cpp	
	streamFPGA.cpp
)

if(WIN32)
	find_package(CyAPI REQUIRED)
	LINK_DIRECTORIES(${CYAPI_LIBRARIES})	
	include_directories(${CYAPI_INCLUDE_DIRS})
endif()

add_library(controlLogic STATIC ${lms7controlLogic_src_files})
target_include_directories(controlLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if(WIN32)
	target_link_libraries(controlLogic ${CYAPI_LIBRARIES})
endif()
if(UNIX)
	target_link_libraries(controlLogic usb-1.0)
endif()
