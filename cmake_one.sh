#!/bin/bash
#
# Usage: ./cmake_one.sh <build type> <compiler>

COMPILER="$2"

if [ -z $COMPILER ]; then
    COMPILER="gcc"
fi

cmake -S . -B build_$1   -DCMAKE_BUILD_TYPE=$1   -DCMAKE_CXX_COMPILER=$COMPILER
