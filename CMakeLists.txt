cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmakeUtils;")
include(setup)

project(libsoundtrackutil VERSION 0.0.1)

setup_project()

#global project version for use in libutil
add_compile_definitions(TWITCH_PROJECT_MAJOR_VERSION=${PROJECT_VERSION_MAJOR})
add_compile_definitions(TWITCH_PROJECT_MINOR_VERSION=${PROJECT_VERSION_MINOR})
add_compile_definitions(TWITCH_PROJECT_PATCH_VERSION=${PROJECT_VERSION_PATCH})

add_subdirectory(libsoundtrackutil)

# this generates the format all target
format_all(formatall)
