#!/bin/bash
set -e
rm -rf build
mkdir build/
cd build/
cmake -DOPTIMIZE=$OPTIMIZE ..
make -j
ulimit -s unlimited
ctest -j4 --output-on-failure
cd ..
python3 match.py
