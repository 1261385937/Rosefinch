
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_LIBRARY (gtest-lib STATIC
    "src/gtest-all.cc"
    "src/gtest_main.cc"
)
