#----------------------------------------------------------------------------
# Specify the required CMake version.
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11...3.20 FATAL_ERROR)

#----------------------------------------------------------------------------
# Define project name and version.
#----------------------------------------------------------------------------
set(ATA_VERSION_MAJOR 2)
set(ATA_VERSION_MINOR 1)
set(ATA_VERSION_PATCH 0)
set(ATA_VERSION ${ATA_VERSION_MAJOR}.${ATA_VERSION_MINOR}.${ATA_VERSION_PATCH})
project(Atangria VERSION ${ATA_VERSION})

#----------------------------------------------------------------------------
# List all options.
#----------------------------------------------------------------------------
include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)
ata_set_default_option(ATA_BUILD_SHARED ON BOOL "Build Atangria as static or shared library")
ata_set_default_option(ATA_BUILD_EXAMPLES ON BOOL "Build Atangria examples")
ata_set_default_option(ATA_BUILD_TESTS ON BOOL "Build Atangria tests")
ata_set_default_option(ATA_BUILD_GL_DEBUG_CONTEXT OFF BOOL "Build Atangria with an OpenGL debug-context")
ata_set_default_option(ATA_BUILD_TYPE "Debug" STRING "Choose the type of build (Debug or Release)")
ata_set_default_option(ATA_BUILD_LOCAL_DEPS OFF BOOL "Build with dependencies installed locally on your machine")
ata_set_default_option(ATA_INSTALL ON BOOL "Install Atangria on your machine")

#----------------------------------------------------------------------------
# Determine what type of build to use.
#----------------------------------------------------------------------------
set(BUILD_SHARED_LIBS ${ATA_BUILD_SHARED})
set(ATA_BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBS})
set(CMAKE_BUILD_TYPE ${ATA_BUILD_TYPE} CACHE STRING "Choose the type of build (Debug or Release)" FORCE)

if(ATA_BUILD_SHARED)
	set(ATA_LIBRARY_TYPE "SHARED" CACHE STRING "Internally used symbol to determine the library type (STATIC or SHARED)")
	set(ATA_DYNAMIC_BUILD 1)
else()
	set(ATA_LIBRARY_TYPE "STATIC" CACHE STRING "Internally used symbol to determine the library type (STATIC or SHARED)")
endif()

if(ATA_BUILD_TYPE STREQUAL "Debug")
	set(ATA_DEBUG_MODE 1)
endif()

message(STATUS "Atangria build-type: ${ATA_BUILD_TYPE}")
message(STATUS "Atangria build shared: ${ATA_BUILD_SHARED_LIBRARY}")
message(STATUS "Atangria library-type: ${ATA_LIBRARY_TYPE}")

#----------------------------------------------------------------------------
# Detect the operating system.
#----------------------------------------------------------------------------
include(CMakeDependentOption)
cmake_dependent_option(ATA_PLATFORM_WINDOWS "Define this symbol when building on Windows" ON "WIN32" OFF)
cmake_dependent_option(ATA_PLATFORM_UNIX "Define this symbol when building on Unix-like systems" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(ATA_PLATFORM_MACOSX "Define this symbol when building on MacOSX systems" ON "APPLE" OFF)

#----------------------------------------------------------------------------
# Tell CMake something about the project set up.
#----------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake)
configure_file("${CMAKE_SOURCE_DIR}/include/ATA/config.h.in" "${CMAKE_SOURCE_DIR}/include/ATA/config.h" ESCAPE_QUOTES)
configure_file("${CMAKE_SOURCE_DIR}/include/ATA/config/compiler.h.in" "${CMAKE_SOURCE_DIR}/include/ATA/config/compiler.h" ESCAPE_QUOTES)
configure_file("${CMAKE_SOURCE_DIR}/include/ATA/config/platform.h.in" "${CMAKE_SOURCE_DIR}/include/ATA/config/platform.h" ESCAPE_QUOTES)

#----------------------------------------------------------------------------
# Specify the source location.
#----------------------------------------------------------------------------
add_definitions(-DGLEW_STATIC)
add_subdirectory(src/ATA)

#----------------------------------------------------------------------------
# Build examples, if specified.
#----------------------------------------------------------------------------
if(ATA_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

#----------------------------------------------------------------------------
# Build tests, if specified.
#----------------------------------------------------------------------------
if(ATA_BUILD_TESTS)
	add_subdirectory(tests)
endif()
