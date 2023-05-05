#!/bin/bash

ReleasePath=./build/sdk/native-c/release/
rm -rf ${ReleasePath}
mkdir -p ${ReleasePath}/core
cp -ar ./src/native/src ${ReleasePath}/core
cp -ar ./src/native/test ${ReleasePath}/core
cp -ar ./src/native/CMakeLists.txt ${ReleasePath}/core
cp -a ./src/native/build-core.sh ${ReleasePath}/core

mkdir -p ${ReleasePath}/openrpc
cp -ar ../firebolt-openrpc/build/sdk/native-c/release/* ${ReleasePath}/openrpc

cd ${ReleasePath}../
tar -cvzf release.tgz release
cd -
