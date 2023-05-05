#!/bin/bash

ReleasePath=./build/sdk/native-c/firebolt-core-native-sdk/
rm -rf ${ReleasePath}
mkdir -p ${ReleasePath}/core
cp -ar ./src/native/src ${ReleasePath}/core
cp -ar ./src/native/test ${ReleasePath}/core
cp -ar ./src/native/CMakeLists.txt ${ReleasePath}/core
cp -a ./src/native/build-core.sh ${ReleasePath}/core
cp -a ${ReleasePath}/../generated ${ReleasePath}/core

mkdir -p ${ReleasePath}/openrpc
cp -ar ../firebolt-openrpc/build/sdk/native-c/firebolt-openrpc-native-sdk/* ${ReleasePath}/openrpc

cd ${ReleasePath}../
tar -cvzf firebolt-core-native-sdk.tgz firebolt-core-native-sdk/*
cd -
