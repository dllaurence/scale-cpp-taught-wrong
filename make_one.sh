#!/bin/bash
#
# Usage: ./make_one.sh <build type> <verbose>

cmake --build build_$1 -- VERBOSE=$2
