cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

add_library(EDEN_Script
    ../../src/EDEN_Script/ComponentArguments.cpp
    ../../src/EDEN_Script/ScriptManager.cpp)

set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)

find_library(LUA_LIB
        lua
        HINTS "${EXTERNAL_LIB_DIR}/Lua/build/arm64/${CMAKE_BUILD_TYPE}"
        REQUIRED)

target_include_directories(EDEN_Script PUBLIC "${EXTERNAL_LIB_DIR}/Lua/src/src/")
target_include_directories(EDEN_Script PUBLIC "${ROOT_DIR}/src/EDEN/")

target_link_libraries(EDEN_Script PUBLIC ${LUA_LIB})