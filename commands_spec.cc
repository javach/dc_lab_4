#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <unistd.h>
#include "commands.c"

class FileTest : public ::testing::Test {
    void SetUp() override {
        std::ofstream file("access_log");
        file << "indy2.indy.net - - [01/Jul/1995:00:26:51 -0400] \"GET "
                "/cgi-bin/imagemap/countdown?320,279 HTTP/1.0\" 302 98\n";
        file << "cs2-07.all.ptd.net - - [01/Jul/1995:00:26:53 -0400] \"GET "
                "/shuttle/countdown/ HTTP/1.0\" 200 3985\n";
        file << "cs2-07.all.ptd.net - - [01/Jul/1995:00:26:53 -0400] \"GET "
                "/shuttle/countdown/ HTTP/1.0\" 200 3985\n";
        file.close();
    }

    void TearDown() override {
        std::remove("access_log");
    }
};

TEST_F(FileTest, entries_count) {
    FILE *file = fopen("access_log", "r");
    EXPECT_EQ(command_entries_count(file), 3);
    fclose(file);
}

TEST_F(FileTest, max_period) {
    FILE *file = fopen("access_log", "r");
    ::testing::internal::CaptureStdout();
    command_max_period(file, 1, 3);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(captured.c_str(),
                 "Executing 'max_period' command...\n\r0.00% [0 / 3]\rTime "
                 "period with maximum requests in 1 seconds: 1995-07-01 "
                 "01:26:52 - 1995-07-01 01:26:53 (2 entries total)\n\n");
    fclose(file);
}

TEST_F(FileTest, status_code) {
    FILE *file = fopen("access_log", "r");
    ::testing::internal::CaptureStdout();
    command_status_code(file, "x0x", 3);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(
        captured.c_str(),
        "Executing 'status_code' command...\nEntries with status code "
        "x0x:\n\r0.00% [0 / 3]\rindy2.indy.net - - [01/Jul/1995:00:26:51 "
        "-0400] \"GET /cgi-bin/imagemap/countdown?320,279 HTTP/1.0\" 302 "
        "98\n\rcs2-07.all.ptd.net - - [01/Jul/1995:00:26:53 -0400] \"GET "
        "/shuttle/countdown/ HTTP/1.0\" 200 3985\n\rcs2-07.all.ptd.net - - "
        "[01/Jul/1995:00:26:53 -0400] \"GET /shuttle/countdown/ HTTP/1.0\" 200 "
        "3985\n\rx0x response code entries total: 3\n\n");
    fclose(file);
}

TEST_F(FileTest, bytes_sent) {
    FILE *file = fopen("access_log", "r");
    ::testing::internal::CaptureStdout();
    command_bytes_sent(file, 3985, '=', 3);
    std::string captured = ::testing::internal::GetCapturedStdout().c_str();
    EXPECT_STREQ(
        captured.c_str(),
        "Executing 'bytes_sent' command...\nEntries with bytes sent value "
        "=3985:\n\r0.00% [0 / 3]cs2-07.all.ptd.net - - [01/Jul/1995:00:26:53 "
        "-0400] \"GET /shuttle/countdown/ HTTP/1.0\" 200 "
        "3985\ncs2-07.all.ptd.net - - [01/Jul/1995:00:26:53 -0400] \"GET "
        "/shuttle/countdown/ HTTP/1.0\" 200 3985\n\rEntries with bytes sent "
        "value =3985 total: 2\n\n");


    fclose(file);
}