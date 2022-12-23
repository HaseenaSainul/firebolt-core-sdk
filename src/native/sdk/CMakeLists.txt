cmake_minimum_required(VERSION 3.3)

project(FireboltCore)
option(ENABLE_TESTS "Build core sdk native test" OFF)

list(APPEND CMAKE_MODULE_PATH
	"${SYSROOT_PATH}/usr/lib/cmake"
	"${SYSROOT_PATH}/tools/cmake")
message("SYSROOT_PATH = " ${SYSROOT_PATH})
find_package(WPEFramework CONFIG REQUIRED)
find_package(Firebolt CONFIG REQUIRED)

#if (NOT DEFINED CMAKE_PREFIX_PATH)
#    set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
#endif()

if (ENABLE_TESTS)
   add_subdirectory(Tests)
endif()

