
set(executable_name unit_test)

aux_source_directory(. src_files)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/contrib/gtest-1.11.0/include)

add_executable(${executable_name} ${src_files}) 


if (MSVC)
    target_compile_options(${executable_name}
        PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
    )

    target_link_libraries(${executable_name} gtest-lib ws2_32)
else ()
    target_link_libraries(${executable_name} gtest-lib -static-libgcc -static-libstdc++ dl pthread)
endif ()