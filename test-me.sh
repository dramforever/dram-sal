#!/bin/bash
rm -rf build || exit 1
mkdir build/ || exit 1
cd build/ || exit 1
cmake -DOPTIMIZE=$OPTIMIZE .. || exit 1
make || exit 1
ctest --output-on-failure || exit 1
