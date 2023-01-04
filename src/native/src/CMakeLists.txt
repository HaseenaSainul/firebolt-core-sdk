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

add_library(${TARGET} SHARED
    Module.cpp
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(${NAMESPACE}Core CONFIG REQUIRED)

target_link_libraries(${TARGET}
    PUBLIC
        ${NAMESPACE}Core::${NAMESPACE}Core
)

InstallHeaders(
    TARGET ${TARGET}
    EXCLUDE_ROOT_DIR
    HEADERS .
    NAMESPACE ${FIREBOLT_NAMESPACE}
    SOURCE ${GENERATED_CODE_PATH}/include
    DESTINATION ${FIREBOLT_NAMESPACE}/generated
)

