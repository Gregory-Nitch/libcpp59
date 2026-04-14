# Set cmake version
cmake_minimum_required(VERSION 4.3.1)

#Set project name, version, description
project(logger VERSION 1.0.0 DESCRIPTION "libcpp59 logger" LANGUAGES C++)

# add source to library
add_library(logger SHARED src/logger.cpp)

# Declare public API of lib
set_target_properties(logger PROPERTIES PUBLIC_HEADER logger/inc/logger.hpp)

# Include relative paths
target_include_directories(logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/libcpp59>
)

add_subdirectory(test)
