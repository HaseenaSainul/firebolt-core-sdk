cmake_minimum_required(VERSION 3.3)

project(FireboltCoreSDKTestApp)
project_version(1.0.0)

set(TARGET ${PROJECT_NAME})

message("Setup ${TARGET} v${PROJECT_VERSION}")

add_executable(${TARGET} FireboltCoreSDKTestsMain.c Module.cpp)

target_link_libraries(${TARGET}
    PRIVATE
       FireboltCoreSDKTests
)

target_include_directories(${TARGET}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../>
)
