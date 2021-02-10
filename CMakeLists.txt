cmake_minimum_required(VERSION 3.10)

project(msdfgen VERSION 1.8 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#----------------------------------------------------------------
# Gathering File
#----------------------------------------------------------------

file(GLOB_RECURSE msdfgen_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"core/*.h"
	"core/*.hpp"
)

file(GLOB_RECURSE msdfgen_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"core/*.cpp"
)

# Build the library (aliased name because it's the same target name the exe)
include(folderize)
folderize_sources(msdfgen_HEADERS ${CMAKE_SOURCE_DIR})
folderize_sources(msdfgen_SOURCES ${CMAKE_SOURCE_DIR})

#----------------------------------------------------------------
# Target configuration
#----------------------------------------------------------------

add_library(msdfgen ${msdfgen_SOURCES} ${msdfgen_HEADERS} "./msdfgen.h")
add_library(msdfgen::msdfgen ALIAS msdfgen)
set_target_properties(msdfgen PROPERTIES PUBLIC_HEADER "${msdfgen_HEADERS}")
target_include_directories(msdfgen INTERFACE
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
)
