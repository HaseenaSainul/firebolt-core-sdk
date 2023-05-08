#!/bin/bash

ReleasePath=./build/sdk/native-c/firebolt-core-native-sdk
ReleaseSDKPath=${ReleasePath}/sdk
rm -rf ${ReleasePath}
mkdir -p ${ReleaseSDKPath}/core
cp -ar ./src/native/src ${ReleaseSDKPath}/core
cp -ar ./src/native/CMakeLists.txt ${ReleaseSDKPath}/core
cp -a ${ReleasePath}/../generated ${ReleaseSDKPath}/core
cp -a ./src/native/cmake.sdk ${ReleaseSDKPath}/CMakeLists.txt
cp -a ./src/native/build-sdk.sh ${ReleaseSDKPath}/

mkdir -p ${ReleaseSDKPath}/openrpc
cp -ar ../firebolt-openrpc/build/sdk/native-c/firebolt-openrpc-native-sdk/* ${ReleaseSDKPath}/openrpc
mv ${ReleaseSDKPath}/openrpc/cmake ${ReleaseSDKPath}

mkdir -p ${ReleasePath}/test
cp -a ./src/native/ctest/* ${ReleasePath}/test
cp -a ./src/native/ctest/build-test.sh ${ReleasePath}/test

cd ${ReleasePath}/../
tar -cvzf firebolt-core-native-sdk.tgz firebolt-core-native-sdk/*
cd -
