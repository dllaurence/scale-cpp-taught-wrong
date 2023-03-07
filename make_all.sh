#!/bin/bash
#
# Usage: ./make_all.sh <verbose>

#set -x

TYPES=(release debug sanitize threadsan)

for TYPE in ${TYPES[@]} ; do
  ./make_one.sh $TYPE $1
done
