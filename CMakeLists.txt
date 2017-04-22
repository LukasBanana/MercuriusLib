
# === CMake lists for the MercuriusLib - (22/04/2017) ===

cmake_minimum_required(VERSION 2.8)
project(MercuriusLib)


# === Build path ===

set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${OUTPUT_DIR} CACHE PATH "Build directory" FORCE)
set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_TEST_DIR "${PROJECT_SOURCE_DIR}/test")


# === Preprocessor definitions ===

macro(ADD_TEST_PROJECT TEST_NAME TEST_FILES)
	add_executable(${TEST_NAME} ${TEST_FILES})
	target_link_libraries(${TEST_NAME} merclib)
	set_target_properties(${TEST_NAME} PROPERTIES LINKER_LANGUAGE CXX DEBUG_POSTFIX "D")
	target_compile_features(${TEST_NAME} PRIVATE cxx_range_for)
endmacro()


# === Global files ===

file(GLOB_RECURSE HeadersAll "${PROJECT_SOURCE_DIR}/include/*.*")
file(GLOB SourcesAll "${PROJECT_SOURCE_DIR}/sources/*.*")
file(GLOB SourcesPlatformCore "${PROJECT_SOURCE_DIR}/sources/Platform/*.*")

if(WIN32)
	file(GLOB SourcesPlatform "${PROJECT_SOURCE_DIR}/sources/Platform/Win32/*.*")
elseif(UNIX)
	file(GLOB SourcesPlatform "${PROJECT_SOURCE_DIR}/sources/Platform/Linux/*.*")
endif()

set(FilesAll ${HeadersAll} ${SourcesAll} ${SourcesPlatform} ${SourcesPlatformCore})


# === Options ===

option(Mercurius_ENABLE_MULTI_THREADING "Enables multi-threading for a couple of functions" ON)

if(Mercurius_ENABLE_MULTI_THREADING)
	add_definitions(-DMC_ENABLE_MULTI_THREADING)
endif()


# === Include directories ===

include_directories("${PROJECT_INCLUDE_DIR}")


# === Source groups ===

source_group("Include" FILES ${HeadersAll})
source_group("Sources" FILES ${SourcesAll})
source_group("Sources\\Platform" FILES ${SourcesPlatform} ${SourcesPlatformCore})


# === Binaries ===

add_library(merclib SHARED ${FilesAll} ${SourcesPlatform})
set_target_properties(merclib PROPERTIES LINKER_LANGUAGE CXX DEBUG_POSTFIX "D")
target_compile_features(merclib PRIVATE cxx_strong_enums cxx_auto_type)

# Socket API
if(WIN32)
	target_link_libraries(merclib WS2_32 NetAPI32 Vfw32 Iphlpapi)
endif(WIN32)

ADD_TEST_PROJECT(Test1 "${PROJECT_TEST_DIR}/Test1.cpp")



