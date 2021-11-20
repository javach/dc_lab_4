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
    parser_spec
    parser_spec.cc
)
target_link_libraries(
    parser_spec
    gtest_main
)

add_executable(
    commands_spec
    commands_spec.cc
)
target_link_libraries(
    commands_spec
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(commands_spec)
gtest_discover_tests(parser_spec)