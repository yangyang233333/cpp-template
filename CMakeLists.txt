cmake_minimum_required(VERSION 3.16)
project(cpptest)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(-O0 -g -Wall -Wextra
        -fsanitize=address
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
        -fsanitize-address-use-after-scope
        -fsanitize-recover=address)
    add_link_options(-fsanitize=address)
else()
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()


file(GLOB_RECURSE SRC_FILES ${ROOT_DIR}/src/*.cc)
add_executable(cpptest ${SRC_FILES})

target_include_directories(cpptest PRIVATE ${ROOT_DIR}/src)

find_package(fmt CONFIG REQUIRED)
find_package(tabulate CONFIG REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)
target_include_directories(cpptest PRIVATE ${FUSE3_INCLUDE_DIRS})

target_link_libraries(cpptest PRIVATE 
    tabulate::tabulate 
    fmt::fmt 
    ${FUSE3_LIBRARIES}
)
