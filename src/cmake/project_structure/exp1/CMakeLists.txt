cmake_minimum_required(VERSION 3.21)

project(EXP1)
set(RELATIVE_ROOT_DIR .)
include(${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_ROOT_DIR}/cmake/PN.cmake)

add_subdirectory(SPS1)
add_subdirectory(SPS2)


