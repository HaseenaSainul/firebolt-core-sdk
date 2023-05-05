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
find_package(${FIREBOLT_NAMESPACE}SDK CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDKTests CONFIG REQUIRED)

add_library(${TESTLIB} STATIC CoreSDKTests.cpp CoreSDKTestGeneratedCode)

target_link_libraries(${TESTLIB}
    PUBLIC
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
        ${FIREBOLT_NAMESPACE}SDKTests::${FIREBOLT_NAMESPACE}SDKTests
        ${FIREBOLT_NAMESPACE}CoreSDK
)

target_include_directories(${TESTLIB}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
    $<BUILD_INTERFACE:${GENERATED_CODE_PATH}generated/include>
    $<BUILD_INTERFACE:${SYSROOT_PATH}/usr/include>
    $<BUILD_INTERFACE:${FIREBOLT_PATH}/usr/include/${FIREBOLT_NAMESPACE}>
    $<INSTALL_INTERFACE:include/${FIREBOLT_NAMESPACE}Test>
)

set_target_properties(${TESTLIB} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    LINK_WHAT_YOU_USE TRUE
    FRAMEWORK FALSE
)

set(TESTAPP FireboltCoreSDKTestApp)

message("Setup ${TESTAPP} v${PROJECT_VERSION}")

add_executable(${TESTAPP} Main.c Module.cpp)

target_link_libraries(${TESTAPP}
    PRIVATE
        ${TESTLIB}
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SRC_DIR}/../>
)

install(
    TARGETS ${TESTLIB} EXPORT ${TESTLIB}Targets
    LIBRARY DESTINATION lib COMPONENT libs
     PUBLIC_HEADER DESTINATION include/${FIREBOLT_NAMESPACE}Test COMPONENT devel   # headers for mac (note the different component -> different package)
        INCLUDES DESTINATION include/${FIREBOLT_NAMESPACE}Test # headers
)

InstallCMakeConfig(TARGETS ${TESTLIB})
InstallCMakeConfigs(TARGET ${TESTLIB} DESTINATION ${FIREBOLT_NAMESPACE})
InstallHeaders(TARGET ${TESTLIB} HEADERS . NAMESPACE ${FIREBOLT_NAMESPACE} DESTINATION FireboltTest)
InstallLibraries(TARGET ${TESTLIB} LIBRARIES ${TESTLIB} DESTINATION ${FIREBOLT_NAMESPACE})

add_custom_command(
    TARGET ${TESTAPP}
    POST_BUILD
    COMMENT "=================== Installing TestApp ======================"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${TESTAPP} ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
)
