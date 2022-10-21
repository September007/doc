# relied VARS which need be set form caller cmake-file
# 1. RELATIVE_ROOT_DIR
# 说明: relative path to root-cmake-project-dir, for the root-cmake, this is ./

# this only need be call by top-build-level Project-node
macro(setup_env)
    # 1. set module_path point to root-cmake-proj-dir
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_ROOT_DIR}/cmake)
    get_filename_component(ABSOLUTE_MODULE_PATH ${MODULE_PATH} ABSOLUTE)
    message(STATUS "set module path: ${ABSOLUTE_MODULE_PATH}")
    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${ABSOLUTE_MODULE_PATH})
    include(env)

    # 2. build option
    set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
    set_property(GLOBAL PROPERTY TARGET_MESSAGES OFF)

    # build dirs
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
    set(TARGET_ROOT ${CMAKE_INSTALL_PREFIX})

    set(TARGET_TRIPLE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${TARGET_TRIPLE_CONFIG})

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${BUILD_CONFIG})

    if(WIN32)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${BUILD_CONFIG})
    else()
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/${BUILD_CONFIG})
    endif()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/${BUILD_CONFIG})
    # set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/pdb/${BUILD_CONFIG})

    # 强制修改安装目录
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${config}" config_uc)

        foreach(type ARCHIVE LIBRARY RUNTIME PDB)
            set(CMAKE_${type}_OUTPUT_DIRECTORY_${config_uc}
                ${CMAKE_${type}_OUTPUT_DIRECTORY})
        endforeach()
        unset(config_uc)
    endforeach()

    # IDE
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # FIXME
    if(WIN32)
        set(TARGET_SUFFIX WIN32)
    else()
        set(TARGET_SUFFIX POSIX)
    endif()

    # compile 
    set(CMAKE_CXX_STANDARD 11)

    # debug
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

endmacro()

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    setup_env()
    message(STATUS "set TPS: " ${CMAKE_CURRENT_SOURCE_DIR})
else()
    message(STATUS "set SPS: " ${CMAKE_CURRENT_SOURCE_DIR})
endif()