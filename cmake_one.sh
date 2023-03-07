#!/bin/bash
#
# Usage: ./cmake_one.sh <build type> <compiler>

cmake -S . -B build_$1   -DCMAKE_BUILD_TYPE=$1   -DCMAKE_CXX_COMPILER=$2
