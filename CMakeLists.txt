cmake_minimum_required(VERSION 3.16)
project(cpptest)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

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

# 设置库搜索路径
set(CMAKE_PREFIX_PATH "${ROOT_DIR}/vcpkg_installed/x64-linux/lib")


file(GLOB_RECURSE SRC_FILES ${ROOT_DIR}/src/*.cc)
add_executable(cpptest ${SRC_FILES})

target_include_directories(cpptest PRIVATE ${ROOT_DIR}/src ${ROOT_DIR}/vcpkg_installed/x64-linux/include)

link_directories(${ROOT_DIR}/vcpkg_installed/x64-linux/lib)

find_package(fmt CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)
target_include_directories(cpptest PRIVATE ${FUSE3_INCLUDE_DIRS})

target_link_libraries(cpptest PRIVATE 
    fmt::fmt 
    ${FUSE3_LIBRARIES}
    fiu
    CURL::libcurl
)

# pkg-config package: fuse3
find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3>=3.16)
target_link_libraries(cpptest PRIVATE ${FUSE3_LIBRARIES})
target_include_directories(cpptest PRIVATE ${FUSE3_INCLUDE_DIRS})
target_compile_options(cpptest PRIVATE ${FUSE3_CFLAGS_OTHER})
