cmake_minimum_required(VERSION 3.15)

project(fdk-aac-jni VERSION 2.0.1)

set(java_include_dirs
        $ENV{JAVA_HOME}/include
        $ENV{JAVA_HOME}/include/win32
        $ENV{JAVA_HOME}/jre/bin/server
        )
set(java_libs
        $ENV{JAVA_HOME}/lib/jvm.lib
        )

include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)
link_directories($ENV{JAVA_HOME}/include)
link_directories($ENV{JAVA_HOME}/include/win32)

find_package(JNI REQUIRED)

set(fdk_aac_path ./fdk-aac)

set(JNI_SRC
        libfdkaac.c
        libfdkaac.h)

aux_source_directory(${fdk_aac_path}/libAACdec/src AACDEC_SRC)
aux_source_directory(${fdk_aac_path}/libAACenc/src AACENC_SRC)
aux_source_directory(${fdk_aac_path}/libArithCoding/src ARITHCODING_SRC)
aux_source_directory(${fdk_aac_path}/libDRCdec/src DRCDEC_SRC)
aux_source_directory(${fdk_aac_path}/libFDK/src FDK_SRC)
aux_source_directory(${fdk_aac_path}/libMpegTPDec/src MPEGTPDEC_SRC)
aux_source_directory(${fdk_aac_path}/libMpegTPEnc/src MPEGTPENC_SRC)
aux_source_directory(${fdk_aac_path}/libPCMutils/src PCMUTILS_SRC)
aux_source_directory(${fdk_aac_path}/libSACdec/src SACDEC_SRC)
aux_source_directory(${fdk_aac_path}/libSACenc/src SACENC_SRC)
aux_source_directory(${fdk_aac_path}/libSBRdec/src SBRDEC_SRC)
aux_source_directory(${fdk_aac_path}/libSBRenc/src SBRENC_SRC)
aux_source_directory(${fdk_aac_path}/libSYS/src SYS_SRC)

set(fdk_aacinclude_HEADERS
        ${fdk_aac_path}/libSYS/include/machine_type.h
        ${fdk_aac_path}/libSYS/include/genericStds.h
        ${fdk_aac_path}/libSYS/include/FDK_audio.h
        ${fdk_aac_path}/libSYS/include/syslib_channelMapDescr.h
        ${fdk_aac_path}/libAACenc/include/aacenc_lib.h
        ${fdk_aac_path}/libAACdec/include/aacdecoder_lib.h)

set(libfdk_aac_SOURCES
        ${AACDEC_SRC}
        ${AACENC_SRC}
        ${ARITHCODING_SRC}
        ${DRCDEC_SRC}
        ${MPEGTPDEC_SRC}
        ${MPEGTPENC_SRC}
        ${SACDEC_SRC}
        ${SACENC_SRC}
        ${SBRDEC_SRC}
        ${SBRENC_SRC}
        ${PCMUTILS_SRC}
        ${FDK_SRC}
        ${SYS_SRC}
        ${JNI_SRC})

add_library(fdk-aac SHARED ${libfdk_aac_SOURCES})

target_include_directories(fdk-aac
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${fdk_aac_path}/libAACdec/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${fdk_aac_path}/libAACenc/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${fdk_aac_path}/libSYS/include>
        PRIVATE
        ${fdk_aac_path}/libArithCoding/include
        ${fdk_aac_path}/libDRCdec/include
        ${fdk_aac_path}/libSACdec/include
        ${fdk_aac_path}/libSACenc/include
        ${fdk_aac_path}/libSBRdec/include
        ${fdk_aac_path}/libSBRenc/include
        ${fdk_aac_path}/libMpegTPDec/include
        ${fdk_aac_path}/libMpegTPEnc/include
        ${fdk_aac_path}/libFDK/include
        ${fdk_aac_path}/libPCMutils/include)

if (MSVC)
    target_compile_options(fdk-aac PRIVATE /EHsc)
else ()
    target_compile_options(fdk-aac PRIVATE -fno-exceptions -fno-rtti)
endif ()
