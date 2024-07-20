cmake_minimum_required(VERSION 3.22)
project(scenematica
	VERSION 0.0.1.0
    DESCRIPTION "Non-tiled 2D level editor"
	HOMEPAGE_URL "https://github.com/tabdroid-1/MaineCoon"
    LANGUAGES C CXX
)

set(PROJECT_SOURCE_DIR "src")
set(PROJECT_VENDOR_DIR "vendor")

file(GLOB_RECURSE PROJECT_SOURCES 
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )
# Additional project sources (vendors, etc.)
list(APPEND PROJECT_SOURCES
        )

configure_file(${PROJECT_SOURCE_DIR}/scenematica/version.h.in ${PROJECT_SOURCE_DIR}/scenematica/version.h)


add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
        ${PROJECT_SOURCES_DIR}
        ${PROJECT_VENDOR_DIR}
        ${PROJECT_BINARY_DIR}/src # for version.h
        )

include_directories(SYSTEM src)

target_link_libraries(${PROJECT_NAME} PRIVATE 

    )

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -DSM_DEBUG=1")
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/smpch.h")

