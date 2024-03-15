cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(projects/EDEN_Render)
add_subdirectory(projects/EDEN_Audio)
add_subdirectory(projects/EDEN_Input)
add_subdirectory(projects/EDEN_Physics)
add_subdirectory(projects/EDEN_Script)

add_executable(EDEN
        src/EDEN/main.cpp
        src/EDEN/CAnimator.cpp
        src/EDEN/CButton.cpp
        src/EDEN/CCamera.cpp
        src/EDEN/CCursor.cpp
        src/EDEN/CIMage.cpp
        src/EDEN/CMeshRenderer.cpp
        src/EDEN/Component.cpp
        src/EDEN/ComponentFactory.cpp
        src/EDEN/CRigidBody.cpp
        src/EDEN/EdenMaster.cpp
        src/EDEN/Entity.cpp
        src/EDEN/Quaternion.cpp
        src/EDEN/Scene.cpp
        src/EDEN/SceneManager.cpp
        src/EDEN/TestComponent.cpp
        src/EDEN/Transform.cpp
        src/EDEN/Vector3.cpp
        src/EDEN/Hito1Prueba.cpp
        src/EDEN/UIComponent.cpp)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)

target_include_directories(EDEN PUBLIC "${ROOT_DIR}/src/EDEN_Input/")
target_include_directories(EDEN PUBLIC "${ROOT_DIR}/src/EDEN_Physics/")
target_include_directories(EDEN PUBLIC "${ROOT_DIR}/src/EDEN_Render/")
target_include_directories(EDEN PUBLIC "${ROOT_DIR}/src/EDEN_Script/")
target_include_directories(EDEN PUBLIC "${ROOT_DIR}/src/EDEN_Audio/")

target_link_libraries(EDEN PRIVATE EDEN_Render EDEN_Audio EDEN_Input EDEN_Physics EDEN_Script)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -std=c++20")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -std=c++20")