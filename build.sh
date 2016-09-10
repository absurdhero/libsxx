#!/bin/sh
cd build
make -j && test/sxx_GTest
