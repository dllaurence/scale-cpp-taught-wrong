#!/bin/bash
#
# Usage: ./rm_one.sh <build type>
#
# Exists so you can't fumble-finger and delete everything.

rm -rf build_$1
