cmake_minimum_required(VERSION 3.5)
project(lab_3)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    uint1024_t_spec
    uint1024_t_spec.cc
)
target_link_libraries(
    uint1024_t_spec
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(uint1024_t_spec)