cmake_minimum_required(VERSION 3.16)
project(cpptest)

# basic configuration
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Root directory
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Header directory
include_directories(${ROOT_DIR}/src)

# Search all files recursively
file(GLOB_RECURSE SRC_FILES ${ROOT_DIR}/src/*.cc)

# Exclude some files from ${SRC_FILES}
list(FILTER SRC_FILES EXCLUDE REGEX ${ROOT_DIR}/src/file_you_dont_want.cc)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link 3rd libary
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt spdlog::spdlog tcmalloc)

