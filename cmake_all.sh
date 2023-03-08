#!/bin/bash
#
# Usage: ./cmake_all.sh <compiler>

#set -x

COMPILER="$1"

if [ -z $COMPILER ]; then
    COMPILER="gcc"
fi

TYPES=(release debug sanitize threadsan)

for TYPE in ${TYPES[@]} ; do
    ./cmake_one.sh $TYPE $COMPILER
done
