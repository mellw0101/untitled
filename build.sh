#!/bin/bash
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake \
    -G Ninja \
    -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja\
    -DCMAKE_C_COMPILER=/usr/bin/clang\
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++\
    ..
cmake --build . -j 30