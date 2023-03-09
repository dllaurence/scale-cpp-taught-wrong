#!/bin/bash
#
# Usage: ./run_all.sh

#set -x

TYPES=(release debug sanitize threadsan)

for TYPE in ${TYPES[@]} ; do
  echo
  echo "BUILD: ${TYPE}"
  ./run_one.sh $TYPE
done
