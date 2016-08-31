#!/bin/bash
mkdir -p build
cd build
cmake -DCMAKE_CXX_FLAGS="-std=c++14" ..
