if [ ! -d build ]; then
    mkdir build
fi

cmake -B build -S . -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build

./build/cpptest