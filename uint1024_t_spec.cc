#include <fstream>
#include <gtest/gtest.h>
#include "uint1024_t.c"
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <unistd.h>

TEST(lab_2, from_uint) {
    ::testing::internal::CaptureStdout();
    uint1024_t x = from_uint(1000);
    printf_value(x);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(captured.c_str(), "3E8\n");
}

TEST(lab_2, add_op) {
    ::testing::internal::CaptureStdout();
    uint1024_t x = add_op(from_uint(4294967295), from_uint(4294967295));
    printf_value(x);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(captured.c_str(), "1FFFFFFFE\n");
}

TEST(lab_2, subtr_op) {
    ::testing::internal::CaptureStdout();
    uint1024_t x = subtr_op(add_op(from_uint(4294967295), from_uint(4294967295)), from_uint(2130));
    printf_value(x);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(captured.c_str(), "1FFFFF7AC\n");
}

TEST(lab_2, mult_op) {
    ::testing::internal::CaptureStdout();
    uint1024_t x = mult_op(from_uint(4294967295), from_uint(4400));
    printf_value(x);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(captured.c_str(), "112FFFFFEED0\n");
}