########################################################################
# Project setup for EVB7 SoapySDR support
########################################################################
cmake_minimum_required(VERSION 2.8)
project(SoapySDREVB7 CXX C)
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
find_package(SoapySDR "0.2.1" CONFIG)

if (NOT SoapySDR_FOUND)
    message(WARNING "SoapySDR development files not found - skipping support")
    return()
endif ()

if(CMAKE_COMPILER_IS_GNUCXX)
    #C++11 is a required language feature for this project
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    #and set c99 for the C sources
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

add_compile_options(-Wall)
#add_compile_options(-Werror)

add_compile_options(-mfloat-abi=hard -mfpu=neon)

include_directories(../include)
include_directories(../interfaces)

get_filename_component(LMS7002M_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src ABSOLUTE)
file(GLOB LMS7002M_SOURCES "${LMS7002M_SRC_DIR}/LMS7002M_*.c")
include_directories(${LMS7002M_SRC_DIR})
add_definitions(-D_GNU_SOURCE)

SOAPY_SDR_MODULE_UTIL(
    TARGET EVB7
    SOURCES
        ${LMS7002M_SOURCES}
        Streaming.cpp
        EVB7Device.cpp
    LIBRARIES m
)
