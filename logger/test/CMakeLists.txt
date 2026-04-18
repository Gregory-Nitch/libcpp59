# Set cmake version
cmake_minimum_required(VERSION 4.3.1)

#Set project name, version, description
project(logger_test_suite VERSION 1.0.0 DESCRIPTION "libcpp59 logger unit tests." LANGUAGES CXX)

# Add test executables
add_executable(test_logger src/test_logger.cpp)

# link to libs
target_link_libraries(test_logger PRIVATE logger)

# Add test relative paths
target_include_directories(test_logger PRIVATE src)

# currently there is no common dir, left as a place holder
# Add common shared lib
# target_link_libraries(test_logger PRIVATE common)
