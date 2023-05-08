#!/bin/bash
TEST_PATH="."
if [ "$1" != "" ]
then
   TEST_PATH=$1
fi
rm -rf ${TEST_PATH}/build
cmake -B${TEST_PATH}/build -S${TEST_PATH} -DSYSROOT_PATH=${SYSROOT_PATH} -DFIREBOLT_PATH=${FIREBOLT_PATH}
cmake --build ${TEST_PATH}/build
