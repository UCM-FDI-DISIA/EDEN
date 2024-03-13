cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

add_library(EDEN_Render
        ../../src/EDEN_Render/RenderManager.cpp
        ../../src/EDEN_Render/RenderObject.cpp
        ../../src/EDEN_Render/NodeManager.cpp
        ../../src/EDEN_Render/MeshRenderer.cpp
        ../../src/EDEN_Render/Light.cpp
        ../../src/EDEN_Render/Canvas.cpp
        ../../src/EDEN_Render/CameraWrapper.cpp
        ../../src/EDEN_Render/Animator.cpp)
set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)

find_library(SDL2_LIB SDL2 HINTS "${EXTERNAL_LIB_DIR}/SDL/build/arm64/${CMAKE_BUILD_TYPE}" REQUIRED)
find_library(OGRE_LIB OgreMain HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)
find_library(OGRE_OVERLAY_LIB OgreOverlay HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)
find_library(OGRE_RTSH_LIB OgreRTShaderSystem HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)

target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/SDL/src/include/")
target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/SDL/build/arm64/include/")
target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/src/OgreMain/include/")
target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/include/")
target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/src/Components/Overlay/include/")
target_include_directories(EDEN_Render PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/src/Components/RTShaderSystem/include/")
target_include_directories(EDEN_Render PUBLIC "${ROOT_DIR}/src/EDEN/")

target_link_libraries(EDEN_Render PUBLIC ${SDL2_LIB} ${OGRE_LIB} ${OGRE_OVERLAY_LIB} ${OGRE_RTSH_LIB})

add_custom_command(TARGET EDEN_Render POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${EXTERNAL_LIB_DIR}/SDL/build/arm64/Debug/libSDL2-2.0d.0.dylib"
        "${EXTERNAL_LIB_DIR}/SDL/build/arm64/Release/libSDL2-2.0.0.dylib"
        "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}/libOgreMain.dylib"
        $<TARGET_FILE_DIR:EDEN_Render>)