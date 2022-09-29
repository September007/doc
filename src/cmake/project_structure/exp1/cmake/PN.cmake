# relied VARS which need be set form caller cmake-file
# 1. RELATIVE_ROOT_DIR
# 说明: relative path to root-cmake-project-dir, for the root-cmake, this is ./

# this only need be call by top-build-level Project-node
function(setup_env)
    # set module_path point to root-cmake-proj-dir
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_ROOT_DIR}/cmake)
    get_filename_component(ABSOLUTE_MODULE_PATH ${MODULE_PATH} ABSOLUTE)
    message(STATUS "set module path: ${ABSOLUTE_MODULE_PATH}")
    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${ABSOLUTE_MODULE_PATH})
    include(env)
endfunction()

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    setup_env()
    message(STATUS "set TPS: " ${CMAKE_CURRENT_SOURCE_DIR})
else()
    message(STATUS "set SPS: " ${CMAKE_CURRENT_SOURCE_DIR})
endif()