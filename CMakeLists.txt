########################################################################
# Project setup for LMS7 driver
#
# This project builds the sources into a static library
# and had install rules for the library and headers
########################################################################
cmake_minimum_required(VERSION 2.8)
project(LMS7002MDriver C)

########################################################################
# Compiler setup
########################################################################
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    add_definitions(-D_GNU_SOURCE)
endif()

########################################################################
# Build static library
########################################################################
include_directories(include)
file(GLOB LMS7002M_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/LMS7002M_*.c")
add_library(LMS7002M STATIC ${LMS7002M_SOURCES})
install(TARGETS LMS7002M DESTINATION lib${LIB_SUFFIX})

########################################################################
# install headers
########################################################################
install(DIRECTORY include/LMS7002M DESTINATION include)
