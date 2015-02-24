########################################################################
# Project setup for EVB7 SoapySDR support
########################################################################
cmake_minimum_required(VERSION 2.6)
project(SoapySDREVB7 CXX)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

########################################################################
# build the module
########################################################################
find_package(SoapySDR CONFIG)

if (NOT SoapySDR_FOUND)
    message(WARNING "SoapySDR development files not found - skipping support")
    return()
endif ()

if(CMAKE_COMPILER_IS_GNUCXX)
    #C++11 is a required language feature for this project
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_compile_options(-mfloat-abi=hard -mfpu=neon)

include_directories(../include)
include_directories(../interfaces)

SOAPY_SDR_MODULE_UTIL(
    TARGET EVB7
    SOURCES
        Streaming.cpp
        EVB7Device.cpp
)
