cmake_minimum_required(VERSION 3.0.10)
project(EDEN)

set(CMAKE_CXX_STANDARD 20)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../")

add_library(EDEN_Audio
        ../../src/EDEN_Audio/AudioWrapper.cpp)

set(EXTERNAL_LIB_DIR "${ROOT_DIR}/dependencies")
set(CMAKE_CONFIGURATION_TYPES Debug Release)


#find_library(FMOD_LIB_DEB fmodL HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Debug/" REQUIRED)
#find_library(FMOD_LIB fmod HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Release/" REQUIRED)
#find_library(FMOD_STUDIO_LIB_DEB fmodstudioL HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Debug/" REQUIRED)
#find_library(FMOD_STUDIO_LIB fmodstudio HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Release/" REQUIRED)
#find_library(FMOD_FSBANK_LIB_DEB fsbankL HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Debug/" REQUIRED)
#find_library(FMOD_FSBANK_LIB fsbank HINTS "${EXTERNAL_LIB_DIR}/FMOD/build/arm64/Release/" REQUIRED)
find_library(IRRKLANG_LIB irrklang HINTS "${EXTERNAL_LIB_DIR}/irrKlang/build/arm64/" REQUIRED)
#find_library(IRRKLANG_MP3_LIB ikpMP3 HINTS "${EXTERNAL_LIB_DIR}/irrKlang/build/arm64/" REQUIRED)

#target_include_directories(EDEN_Audio PUBLIC "${EXTERNAL_LIB_DIR}/FMOD/src/")
target_include_directories(EDEN_Audio PUBLIC "${EXTERNAL_LIB_DIR}/irrKlang/src/include/")
target_include_directories(EDEN_Audio PUBLIC "${EXTERNAL_LIB_DIR}/irrKlang/src/plugins/ikpMP3/")
target_include_directories(EDEN_Audio PUBLIC "${ROOT_DIR}/src/EDEN/")

target_link_libraries(EDEN_Audio PUBLIC ${IRRKLANG_LIB})

add_custom_command(TARGET EDEN_Audio POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${EXTERNAL_LIB_DIR}/irrKlang/build/arm64/ikpMP3.dylib"
        "${EXTERNAL_LIB_DIR}/irrKlang/build/arm64/libirrklang.dylib"
        $<TARGET_FILE_DIR:EDEN_Audio>)