#!/bin/bash
set -e
./build.sh
cd build/src
./MD5
cd ../../
