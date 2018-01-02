
# Custom CMake module for finding "MercuriusLib" files
# Written by Lukas Hermanns on 31/12/2017

# Macros

macro(_MERCLIB_APPEND_LIBRARIES _list _release)
	set(_debug ${_release}_DEBUG)
	if(${_debug})
		set(${_list} ${${_list}} optimized ${${_release}} debug ${${_debug}})
	else()
		set(${_list} ${${_list}} ${${_release}})
	endif()
endmacro()

# Find library

find_path(MercLib_INCLUDE_DIR NAMES Merc/Merc.h)

find_library(MercLib_LIBRARY NAMES merclib)
find_library(MercLib_LIBRARY_DEBUG NAMES merclibD)

# Setup package handle

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	MercLib
	DEFAULT_MSG
	MercLib_INCLUDE_DIR
    MercLib_LIBRARY
    MercLib_LIBRARY_DEBUG
)

if(MERCLIB_FOUND)
	set(MercLib_FOUND TRUE)
	_MERCLIB_APPEND_LIBRARIES(MercLib_LIBRARIES MercLib_LIBRARY)
endif(MERCLIB_FOUND)
