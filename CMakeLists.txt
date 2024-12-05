cmake_minimum_required(VERSION 3.15)
project(cpptest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Root directory
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native -pthread -g -Wall -pthread -mavx2 -mfma")
else()
    # AVX2
    message("xxxxxxxx")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -march=native -mtune=native -O3 -mavx2 -pthread -mfma -msse2 -ftree-vectorize -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fopenmp -fopenmp-simd -funroll-loops -Wfatal-errors -DUSE_AVX2")
endif()

# 3rd libary
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Header directory
include_directories(${ROOT_DIR}/src)

# Search all files recursively
file(GLOB_RECURSE SRC_FILES ${ROOT_DIR}/src/*.cc)

# Exclude some files from ${SRC_FILES}
list(FILTER SRC_FILES EXCLUDE REGEX ${ROOT_DIR}/src/file_you_dont_want.cc)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt spdlog::spdlog)

# fuse3
find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3>=3.16)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUSE3_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FUSE3_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${FUSE3_CFLAGS_OTHER})
