cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

add_library(EDEN_Input
        ../../src/EDEN_Input/InputManager.cpp
        ../../src/EDEN_Input/InputWrapper.cpp)

set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)

find_library(SDL2_LIB SDL2 HINTS "${EXTERNAL_LIB_DIR}/SDL/build/arm64/${CMAKE_BUILD_TYPE}" REQUIRED)

target_include_directories(EDEN_Input PUBLIC "${EXTERNAL_LIB_DIR}/SDL/src/include/")
target_include_directories(EDEN_Input PUBLIC "${EXTERNAL_LIB_DIR}/SDL/build/arm64/include/")
target_include_directories(EDEN_Input PUBLIC "${ROOT_DIR}/src/EDEN/")
target_include_directories(EDEN_Input PUBLIC "${ROOT_DIR}/src/EDEN_Script/")

target_link_libraries(EDEN_Input PUBLIC ${SDL2_LIB})

add_custom_command(TARGET EDEN_Input POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${EXTERNAL_LIB_DIR}/SDL/build/arm64/Debug/libSDL2-2.0d.0.dylib"
        "${EXTERNAL_LIB_DIR}/SDL/build/arm64/Release/libSDL2-2.0.0.dylib"
        $<TARGET_FILE_DIR:EDEN_Input>)