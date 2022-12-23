cmake_minimum_required(VERSION 3.3)

project(FireboltCoreSDKTests)
project_version(1.0.0)

set(TARGET ${PROJECT_NAME})

message("Setup ${TARGET} v${PROJECT_VERSION}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(${NAMESPACE}Core CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDK CONFIG REQUIRED)
find_package(${FIREBOLT_NAMESPACE}SDKTests CONFIG REQUIRED)

add_library(${TARGET} STATIC FireboltCoreSDKTests.cpp)

target_link_libraries(${TARGET}
    PUBLIC
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
)

target_include_directories(${TARGET}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
    $<INSTALL_INTERFACE:include/${FIREBOLT_NAMESPACE}
)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    LINK_WHAT_YOU_USE TRUE
    FRAMEWORK FALSE
)

add_subdirectory(App)
