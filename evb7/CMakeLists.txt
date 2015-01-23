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

include_directories(../include)
include_directories(../interfaces)

SOAPY_SDR_MODULE_UTIL(
    TARGET SoapySDREVB7
    SOURCES SoapySDREVB7.cpp
)
