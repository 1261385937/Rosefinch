set(lib_name rosefinch)

file(GLOB_RECURSE src_files ${CMAKE_SOURCE_DIR}/src/*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${src_files})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${lib_name} ${src_files}) 