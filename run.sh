if [ ! -d build ]; then
    mkdir build
fi

# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build -S . 
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
      -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
      -DCMAKE_MAKE_PROGRAM=make \
      -B build -S .
cmake --build build

if [ ! $? -eq 0 ]; then
    echo "编译失败"
    exit 0
fi

./build/cpptest
