cmake_minimum_required(VERSION 2.8)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE TYPE INTERNAL FORCE)
project("lms7suite")
#include modules for finding FFTW and CyAPI
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
cmake_policy(SET CMP0015 OLD)
if(${CMAKE_MAJOR_VERSION} GREATER 2)
	cmake_policy(SET CMP0043 NEW)
endif()
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}"
  controlLogic
  controlPanelGUI
 )

find_package(wxWidgets REQUIRED richtext xml html xrc adv aui core base gl)
include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_DEBUG OFF)
set(wxWidgets_USE_UNICODE OFF)
set(wxWidgets_USE_UNIVERSAL OFF)
set(wxWidgets_USE_STATIC ON)

# Add sub-directories
add_subdirectory(controlLogic)
add_subdirectory(controlPanelGUI)

set(BINARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")

set(controlLibs	
	controlLogic
	controlPanelGUI
	)
	
if(WIN32)
	find_package(CyAPI REQUIRED)
	LINK_DIRECTORIES(${CYAPI_LIBRARIES})	
	include_directories(${CYAPI_INCLUDE_DIRS})
endif()

# Add all targets to the build-tree export set
export(TARGETS ${controlLibs} FILE "${PROJECT_BINARY_DIR}/lms7suiteTargets.cmake")

add_executable(lms7suite ${controlLibs} control_LMS7002App.cpp CommonUtilities.cpp resource.rc)
set(AUTO_UPDATE_VERSION OFF CACHE BOOL "Uses python script to increment version")
if(AUTO_UPDATE_VERSION)
	add_custom_target(updateVersion ALL COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/auto_version.py WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})	
	add_dependencies(lms7suite updateVersion)
endif()

set_target_properties(lms7suite
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
target_link_libraries(lms7suite ${wxWidgets_LIBRARIES})
target_link_libraries(lms7suite ${controlLibs})
target_link_libraries(lms7suite fftviewer)
if (MSVC)
	set_property(TARGET lms7suite APPEND PROPERTY LINK_FLAGS /SUBSYSTEM:WINDOWS)	
	set(CMAKE_GENERATOR_TOOLSET "v120_xp" CACHE STRING "Platform Toolset" FORCE) 
endif(MSVC)
