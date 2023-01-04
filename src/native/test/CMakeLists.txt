# Copyright 2023 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.3)

project(FireboltCoreSDKTests)
project_version(1.0.0)

set(TESTLIB ${PROJECT_NAME})

message("Setup ${TESTLIB} v${PROJECT_VERSION}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(${NAMESPACE}Core CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDK CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDKTests CONFIG REQUIRED)

add_library(${TESTLIB} STATIC FireboltCoreSDKTests.cpp)

target_link_libraries(${TESTLIB}
    PUBLIC
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
        ${FIREBOLT_NAMESPACE}SDKTests::${FIREBOLT_NAMESPACE}SDKTests
)

target_include_directories(${TESTLIB}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
    $<INSTALL_INTERFACE:include/${FIREBOLT_NAMESPACE}
)

set_target_properties(${TESTLIB} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    LINK_WHAT_YOU_USE TRUE
    FRAMEWORK FALSE
)

set(TESTAPP FireboltCoreSDKTestApp)

message("Setup ${TESTAPP} v${PROJECT_VERSION}")

add_executable(${TESTAPP} FireboltCoreSDKTestsMain.c Module.cpp)

target_link_libraries(${TESTAPP}
    PRIVATE
        ${TESTLIB}
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)
