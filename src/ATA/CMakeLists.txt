set(ATA_LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(ATA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ATA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/ATA)
set(ATA_SOURCES
        ${ATA_LIBRARY_TYPE}
#	${ATA_SOURCE_DIR}/core/application.cpp
	${ATA_SOURCE_DIR}/core/context.cpp
	${ATA_SOURCE_DIR}/core/monitor.cpp
	${ATA_SOURCE_DIR}/core/string.cpp
	${ATA_SOURCE_DIR}/core/surface.cpp
	${ATA_SOURCE_DIR}/core/event.cpp
	${ATA_SOURCE_DIR}/core/bitmapicon.cpp
	${ATA_SOURCE_DIR}/core/log.cpp
	${ATA_SOURCE_DIR}/core/glresource.cpp

        ${ATA_SOURCE_DIR}/run/thread.cpp
	${ATA_SOURCE_DIR}/run/thread_impl.cpp
	${ATA_SOURCE_DIR}/run/mutex.cpp
	${ATA_SOURCE_DIR}/run/lock.cpp
	${ATA_SOURCE_DIR}/run/thread_local.cpp
	${ATA_SOURCE_DIR}/run/cthread.c

        ${ATA_SOURCE_DIR}/gfx/glew.c
)

if(ATA_PLATFORM_WINDOWS)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/win32/thread_impl_win32.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/win32/sleep_impl_win32.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/win32/mutex_impl_win32.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/win32/thread_local_impl_win32.cpp)
else()
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/posix/thread_impl_posix.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/posix/sleep_impl_posix.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/posix/mutex_impl_posix.cpp)
	list(APPEND ATA_SOURCES ${ATA_SOURCE_DIR}/run/posix/thread_local_impl_posix.cpp)
endif()

# Approach taken from SFML. Specify where the binaries are located to build with dependencies.
if(ATA_PLATFORM_WINDOWS)
        set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/external/headers")
        if(ATA_COMPILER_GCC)
                if(ARCH_32BITS)
                        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-mingw/x86")
                        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/bin/x86")
                elseif(ARCH_64BITS)
                        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-mingw/x64")
                        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/bin/x64")
                endif()
        elseif(ATA_COMPILER_MSVC)
                if(SFML_MSVC_VERSION LESS 14)
                        if(ARCH_32BITS)
                                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-msvc/x86")
                        elseif(ARCH_64BITS)
                                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-msvc/x64")
                        endif()
                else()
                        if(ARCH_32BITS)
                                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-msvc-universal/x86")
                        elseif(ARCH_64BITS)
                                set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-msvc-universal/x64")
                        endif()
                endif()
                message(STATUS "MSVC Library Path: ${CMAKE_LIBRARY_PATH}")

                if(ATA_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Release")
                        message(WARNING "CMAKE_BUILD_TYPE is ignored for multi-configuration generators (use the --config Release option)")
                endif()
                set(GLFW_BUILD_WIN32 ON)
        endif()
elseif(ATA_PLATFORM_MACOSX)
        set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/external")
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/external/libs-osx/lib/")
endif()

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_WAYLAND OFF)

ata_find_package(OpenGL INCLUDE "OPENGL_INCLUDE_DIR" LINK "OPENGL_LIBRARIES")
if(ATA_BUILD_LOCAL_DEPS)
        set(GLFW_LOCATION "${PROJECT_SOURCE_DIR}/external")
        ata_find_package(glfw INCLUDE "GLFW_INCLUDE_DIR" LINK "GLFW_LIBRARY")
else()
        include(FetchContent)
        FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.3.5
        )
        FetchContent_MakeAvailable(glfw)

#        if(ATA_BUILD_SHARED)
#                set_target_properties(glfw PROPERTIES POSITION_INDEPENDENT_CODE ON)
#        endif()

endif()

add_library(atangria ${ATA_SOURCES} )
target_include_directories(atangria PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_include_directories(atangria PRIVATE "${PROJECT_SOURCE_DIR}/external/headers")
target_link_libraries(atangria PRIVATE glfw OpenGL)

if(ATA_PLATFORM_WINDOWS)
        target_link_libraries(atangria PRIVATE winmm gdi32)
endif()