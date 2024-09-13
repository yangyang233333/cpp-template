if [ ! -d build ]; then
    mkdir build
fi

# cmake -B build -S . -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build

./build/cpptest
