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

project(FireboltCoreSDK)
project_version(1.0.0)
set(TARGET ${PROJECT_NAME})
message("Setup ${TARGET} v${PROJECT_VERSION}")

file(GLOB GENERATED_SOURCES "${GENERATED_CODE_PATH}generated/src/*.cpp")


add_library(${TARGET} ${FIREBOLT_LIBRARY_TYPE}
    Module.cpp
    ${GENERATED_SOURCES}
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${TARGET}
    PUBLIC
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
)
target_include_directories(${TARGET}
    PRIVATE
         $<BUILD_INTERFACE:${SYSROOT_PATH}/usr/include>
         $<BUILD_INTERFACE:${OPENRPC_INC}/src>
         $<BUILD_INTERFACE:${OPENRPC_INC}/include>
         $<BUILD_INTERFACE:${FIREBOLT_PATH}/usr/include/${FIREBOLT_NAMESPACE}>
         $<BUILD_INTERFACE:${GENERATED_CODE_PATH}generated/include>
)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    FRAMEWORK FALSE
    LINK_WHAT_YOU_USE TRUE
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(
    TARGETS ${TARGET} EXPORT ${TARGET}Targets
    LIBRARY DESTINATION lib COMPONENT libs
    PUBLIC_HEADER DESTINATION include/${TARGET} COMPONENT devel   # headers for mac (note the different component -> different package)
        INCLUDES DESTINATION include/${TARGET} # headers
)

InstallHeaders(
    TARGET ${TARGET}
    EXCLUDE_ROOT_DIR
    HEADERS .
    NAMESPACE ${FIREBOLT_NAMESPACE}
    SOURCE ${GENERATED_CODE_PATH}generated/include
    DESTINATION ${FIREBOLT_NAMESPACE}CoreSDK/generated
)

InstallLibraries(TARGET ${TARGET} ${FIREBOLT_LIBRARY_TYPE} LIBDIR ${LIBDIR} LIBRARIES ${TARGET} DESTINATION ${FIREBOLT_NAMESPACE})
InstallCMakeConfig(TARGETS ${TARGET})
InstallPackageConfig(TARGETS ${TARGET} NO_INCLUDE_DIRS DESCRIPTION "Firebolt Core SDK Library")
InstallCMakeConfigs(TARGET ${TARGET} DESTINATION ${FIREBOLT_NAMESPACE})

