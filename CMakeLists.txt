# Set cmake version
cmake_minimum_required(VERSION 4.2.3)

#Set project name, version, description
project(libcpp59 VERSION 1.0.0 DESCRIPTION "libcpp59 libraries" LANGUAGES CXX)

# Standard enforcement
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Common warnings for both Debug and Release
add_compile_options(
    -Wall
    -Wextra
    -Wshadow
    -Wunused
    -Wconversion
    -pedantic
    -fdiagnostics-color=always
)

string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if(build_type STREQUAL "debug")
  add_compile_options(-g -fno-omit-frame-pointer)
elseif(build_type STREQUAL "release")
  add_compile_options(-O3 -D_FORTIFY_SOURCE=2)
  add_link_options(-Wl,-z,relro -Wl,-z,now)
elseif(build_type STREQUAL "asan")
  add_compile_options(-g -fsanitize=address -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address) # Linker needs ASan too
else()
  message(FATAL_ERROR "Invalid build type: use -DCMAKE_BUILD_TYPE=Release or Debug")
endif()

# Set a global build directory for all sub-projects
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Get them tests running
include(CTest)

add_subdirectory(logger)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_logger
    COMMAND valgrind --leak-check=full --error-exitcode=1 --show-leak-kinds=all --track-origins=yes --verbose -s
    $<TARGET_FILE:test_logger>
)
set_tests_properties(test_logger PROPERTIES
    PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts"
    FAIL_REGULAR_EXPRESSION "TEST FAILURE:;ERROR SUMMARY: [1-9]"
)


#########################################################################
#                           Installation Rules                          #
#########################################################################

# Get GNU install variables
include(GNUInstallDirs)

# Install shared libraries AND define the export set 'libc59Targets'
install(TARGETS
    logger
    EXPORT libcpp59Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libcpp59
)

# Install public headers
install(DIRECTORY logger/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libcpp59
    FILES_MATCHING PATTERN "*.hpp"
)

# CMake package configuration files and target exports
install(EXPORT libcpp59Targets
    NAMESPACE libcpp59::
    FILE libcpp59Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libcpp59
)

# Install a package config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libcpp59ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/libcpp59Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libcpp59Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libcpp59
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libcpp59Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libcpp59ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libcpp59
)
