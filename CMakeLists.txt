cmake_minimum_required(VERSION 4.0)
project(constant_vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(constant_vector INTERFACE)
target_include_directories(constant_vector INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_executable(test_exec test.cpp)
#target_link_libraries(test_exec PRIVATE constant_vector)


include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF)
set(BENCHMARK_USE_BUNDLED_GTEST OFF)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.4
)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark benchmark::benchmark_main constant_vector)
