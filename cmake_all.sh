#!/bin/bash
#
# Usage: ./cmake_all.sh <compiler>

#set -x

TYPES=(release debug sanitize threadsan)

for TYPE in ${TYPES[@]} ; do
    ./cmake_one.sh $TYPE $1
done
