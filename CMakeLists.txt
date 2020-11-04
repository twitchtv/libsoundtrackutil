cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmakeUtils;")
include(setup)

project(libsoundtrackutil)

setup_project()

add_subdirectory(libsoundtrackutil)

# this generates the format all target
format_all(formatall)
