cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

add_library(EDEN_Debug
        ../../src/EDEN_Debug/DebugDrawer.cpp)

set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)

find_library(BULLET_DYNAMICS_LIB
        BulletDynamics
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/BulletDynamics/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(BULLET_COL_LIB
        BulletCollision
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/BulletCollision/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(BULLET_LIN_MATH_LIB
        LinearMath
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/LinearMath/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(BULLET_3_GEO_LIB
        Bullet3Geometry
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/Bullet3Geometry/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(BULLET_3_COM_LIB
        Bullet3Common
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/Bullet3Common/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(BULLET_3_DYN_LIB
        Bullet3Dynamics
        HINTS "${EXTERNAL_LIB_DIR}/Bullet/build/arm64/src/Bullet3Dynamics/${CMAKE_BUILD_TYPE}"
        REQUIRED)
find_library(OGRE_LIB OgreMain HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)
find_library(OGRE_OVERLAY_LIB OgreOverlay HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)
find_library(OGRE_RTSH_LIB OgreRTShaderSystem HINTS "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/lib/macosx/${CMAKE_BUILD_TYPE}" REQUIRED)

target_include_directories(EDEN_Debug PUBLIC "${EXTERNAL_LIB_DIR}/Bullet/src/src/")
target_include_directories(EDEN_Debug PUBLIC "${ROOT_DIR}/src/EDEN/")
target_include_directories(EDEN_Debug PUBLIC "${ROOT_DIR}/src/EDEN_Render/")
target_include_directories(EDEN_Debug PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/src/OgreMain/include/")
target_include_directories(EDEN_Debug PUBLIC "${EXTERNAL_LIB_DIR}/Ogre/build/arm64/include/")

target_link_libraries(EDEN_Debug PUBLIC ${BULLET_DYNAMICS_LIB} ${BULLET_COL_LIB} ${BULLET_LIN_MATH_LIB}
        ${BULLET_3_GEO_LIB} ${BULLET_3_COM_LIB} ${BULLET_3_DYN_LIB} ${OGRE_LIB} ${OGRE_OVERLAY_LIB} ${OGRE_RTSH_LIB})