#!/bin/bash
#
# Usage: ./make_one.sh <build type> <verbose>

LEVEL="$2"

if [ -z $LEVEL ]; then
    LEVEL=0
fi

VERBOSE=""
if [ $LEVEL != "0" ]; then
    VERBOSE="-- VERBOSE=${LEVEL}"
fi

cmake --build build_$1 $VERBOSE
