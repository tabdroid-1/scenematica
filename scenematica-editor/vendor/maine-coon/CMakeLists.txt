cmake_minimum_required(VERSION 3.22)
project(maine-coon
	VERSION 0.0.1
    DESCRIPTION "Application Framework"
	HOMEPAGE_URL "https://github.com/tabdroid-1/MaineCoon"
    LANGUAGES CXX
)

if(APPLE)
    message(STATUS "Including Objective-C++ for APPLE")
    list(APPEND LANGUAGES OBJC)
    list(APPEND LANGUAGES OBJCXX)
    set(CMAKE_OBJCXX_STANDARD 14)
    set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)
    set(CMAKE_OBJCXX_EXTENSIONS OFF)
endif()

set(PROJECT_SOURCE_DIR "src")
set(PROJECT_VENDOR_DIR "vendor")

# ##############################################################################
# Add dependencies 
# ##############################################################################

set(SDL2 "${PROJECT_VENDOR_DIR}/SDL2")
set(GLAD "${PROJECT_VENDOR_DIR}/glad")
set(STB "${PROJECT_VENDOR_DIR}/stb")
set(SPDLOG "${PROJECT_VENDOR_DIR}/spdlog")
set(IMGUI "${PROJECT_VENDOR_DIR}/imgui")
set(IMGUIZMO "${PROJECT_VENDOR_DIR}/imguizmo")
set(TRACY "${PROJECT_VENDOR_DIR}/tracy")
set(OPENLAL "${PROJECT_VENDOR_DIR}/openal-soft")
set(LIBSNDFILE "${PROJECT_VENDOR_DIR}/libsndfile")

# ##############################################################################
# Project executable setup
# ##############################################################################

file(GLOB_RECURSE PROJECT_SOURCES 
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

# # Additional project sources (vendors, etc.)
list(APPEND PROJECT_SOURCES
        "${SPDLOG}/include/spdlog/spdlog.h"
        "${STB}/stb_image.h"
        "${STB}/stb_image.cpp"
        "${SDL2}/include/SDL.h"
        )


add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
        ${PROJECT_SOURCES_DIR}
        ${PROJECT_VENDOR_DIR}

        ${SPDLOG}/include
        ${OPENLAL}/include
        ${LIBSNDFILE}/include
        )


include_directories(SYSTEM src)
include_directories(${IMGUI})
include_directories(${IMGUIZMO})
include_directories(${STB})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${TRACY})

# ####################
# Add Subdirectories
# ####################

add_subdirectory(${SDL2} EXCLUDE_FROM_ALL)
add_subdirectory(${TRACY})
add_subdirectory(${SPDLOG})
add_subdirectory(${IMGUI})
add_subdirectory(${IMGUIZMO})
add_subdirectory(${LIBSNDFILE})

if (WIN32)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /experimental:c11atomics)
endif()
    message(STATUS "Generating scripts for Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        tracy 
        )
elseif (UNIX AND NOT APPLE AND NOT ANDROID AND NOT EMSCRIPTEN)

    find_package(OpenAL)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

    message(STATUS "Generating scripts for Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        tracy 
        OpenAL::OpenAL
        sndfile
        PkgConfig::GTK4
        )
elseif (APPLE)
    message(STATUS "Generating scripts for Mac")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        tracy 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        OpenAL::OpenAL
        sndfile
        )
elseif (EMSCRIPTEN)
    message(STATUS "Generating scripts for EMSCRIPTEN")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2-static
        imguizmo
        )
elseif (ANDROID)
    message(STATUS "Generating scripts for Android")
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        imgui
        spdlog
        SDL2::SDL2
        SDL2::SDL2main
        imguizmo
        GLESv2
        GLESv3
        EGL
        log
        android
        )
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -DMC_DEBUG=1")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Ensure that hot-reload is enabled for VS
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/mcpch.h")
