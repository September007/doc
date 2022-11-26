cmake_minimum_required(VERSION 3.2)

project(test)

link_directories(global_lib)
link_libraries(stdc++)

add_executable(test )

include_directories(xx)
target_include_directories(test PUBLIC "${CMAKE_CURRENT_LIST_DIR}/set_target_properties_include")
include_directories(global_include )
set_property(TARGET test  PROPERTY  INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/set_target_properties_include")
set_property(SOURCE test.2.cpp APPEND PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/set_source_files_properties_include")
set_property(SOURCE test.3.cpp  PROPERTY INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/set_source_files_properties_include")



target_sources(test PRIVATE test.cpp test.2.cpp test.3.cpp)
