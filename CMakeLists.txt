cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)
project(SP VERSION 1.3.1 LANGUAGES C CXX)

# this is a test..
macro(sp_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

cmake_policy(SET CMP0042 NEW)
if(NOT CMAKE_VERSION VERSION_LESS 3.9)
	cmake_policy(SET CMP0068 NEW)
endif()

# another test..
if(NOT CMAKE_OSX_SYSROOT)
    # query the path to the default SDK, will fail on non-macOS, but it's okay.
    execute_process(COMMAND xcodebuild -sdk macosx -version Path
                    COMMAND head -n 1
                    COMMAND tr -d '\n'
                    OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
                    ERROR_QUIET)
endif()

if(POLICY CMP0079)
	cmake_policy(SET CMP0079 NEW)
endif()

if(NOT CMAKE_VERSION VERSION_LESS 3.9)
    cmake_policy(SET CMP0068 NEW)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_INSTALL_INCLUDEDIR include)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

sp_set_option(SP_RENDERER Legacy STRING "Choose a renderer type for drawing operations: Legacy|Core|None")
sp_set_option(BUILD_SHARED_LIBS OFF BOOL "Build shared libraries")
sp_set_option(SP_BUILD_EXAMPLES ON BOOL "Build the SP example programs")
sp_set_option(SP_BUILD_TESTS ON BOOL "Build tests")
sp_set_option(SP_INSTALL ON BOOL "Install SP on the system or not")
sp_set_option(SP_BUILD_OPENGL_CORE_PROFILE ON BOOL "TRUE to build an OpenGL Core Profile, FALSE to build an OpenGL Compat Profile")
sp_set_option(SP_BUILD_OPENGL_DEBUG_CONTEXT FALSE BOOL "TRUE to build an OpenGL Debug Context")
sp_set_option(CMAKE_BUILD_TYPE "Debug" STRING "Choose a build type: Debug|Release|RelWithDebInfo|MinSizeRel")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose a build type: Debug|Release|RelWithDebInfo|MinSizeRel" FORCE)
endif()

if(BUILD_SHARED_LIBS)
	set(SP_DYNAMIC_BUILD 1)
endif()

if(SP_BUILD_OPENGL_CORE_PROFILE)
	set(SP_OPENGL_CORE_PROFILE 1)
endif()

if(SP_BUILD_OPENGL_DEBUG_CONTEXT)
	set(SP_OPENGL_DEBUG_CONTEXT 1)
endif()



# To be removed
if(SP_RENDERER STREQUAL "Legacy")
	set(SP_LEGACY_RENDERER 1)
elseif(SP_RENDERER STREQUAL "Core")
	set(SP_CORE_RENDERER 1)
elseif(SP_RENDERER STREQUAL "None")
	set(SP_NO_RENDERER 1)
else()
	message(FATAL_ERROR "Invalid option selected, please choose a renderer: Legacy|Core|None")
endif()

if(SP_PLATFORM_MACOS)
	sp_set_option(SP_BUILD_FRAMEWORKS FALSE BOOL "TRUE to build SP as frameworks libraries (release only), FALSE to build according to BUILD_SHARED_LIBS")
	sp_set_option(SP_DEPENDENCIES_INSTALL_PREFIX "/Library/Frameworks" PATH "External frameworks (FLAC, Freetype, Vorbis, ...) installation directory")
	sp_set_option(SP_INSTALL_XCODE_TEMPLATES FALSE BOOL "TRUE to automatically install the Xcode templates, FALSE to do nothing about it. The templates are compatible with Xcode 4 and 5.")
else()
	sp_set_option(SP_DEPENDENCIES_INSTALL_PREFIX "." PATH "External libraries (FLAC, Freetype, Vorbis, ...) installation directory")
endif()

# specify install directory..
if(SP_PLATFORM_WINDOWS)
	set(DEFAULT_INSTALL_MISC_DIR .)
elseif(SP_PLATFORM_LINUX OR SP_PLATFORM_FREEBSD OR SP_PLATFORM_OPENBSD)
	set(DEFAULT_INSTALL_MISC_DIR share/Playground)
elseif(SP_PLATFORM_MACOS)
	set(DEFAULT_INSTALL_MISC_DIR /usr/local/share/Playground)
endif()
sp_set_option(SP_MISC_INSTALL_PREFIX "${DEFAULT_INSTALL_MISC_DIR}" PATH "Prefix installation path for miscellaneous files")

if(SP_COMPILER_MSVC)
	message(FATAL_ERROR "MSVC compiler not supported by SP")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

include_directories(
	${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES} 
	${CMAKE_SOURCE_DIR}/include 
	${CMAKE_SOURCE_DIR}/extern
	${CMAKE_SOURCE_DIR}/tests 
	${CMAKE_SOURCE_DIR}/examples
	${GLFW_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIRS}
	${gtest_SOURCE_DIR}/include 
	${gtest_SOURCE_DIR}
)

add_definitions(-DGLEW_STATIC)
add_subdirectory(src/SP)

if(SP_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

if(SP_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()