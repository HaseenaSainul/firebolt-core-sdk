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

project(FireboltCore)
option(ENABLE_TESTS "Build core sdk native test" OFF)

if (NOT SYSROOT_PATH)
    # Set sysroot to support PC builds, sysroot_path not configured case
    set(SYSROOT_PATH "${CMAKE_SOURCE_DIR}/../../node_modules/@firebolt-js/openrpc/firebolt" CACHE INTERNAL "" FORCE)
endif()
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${SYSROOT_PATH}/usr" CACHE INTERNAL "" FORCE)
    set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH
	"${SYSROOT_PATH}/usr/lib/cmake"
	"${SYSROOT_PATH}/tools/cmake")

find_package(WPEFramework CONFIG REQUIRED)
find_package(Firebolt CONFIG REQUIRED)
include(HelperFunctions)

add_subdirectory(src)

if (ENABLE_TESTS)
   add_subdirectory(test)
endif()

