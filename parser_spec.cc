#include <fstream>
#include <gtest/gtest.h>
#include <unistd.h>
#include "parser.c"

TEST(lab_3, parser_get_addr) {
    char* line =
        "ix-la15-03.ix.netcom.com - - [13/Jul/1995:21:04:13 -0400] \"GET "
        "/images/NASA-logosmall.gif HTTP/1.0\" 200 786";
    EXPECT_STREQ(get_addr(line), "ix-la15-03.ix.netcom.com");
}

TEST(lab_3, parser_get_time) {
    char *line =
        "ix-la15-03.ix.netcom.com - - [13/Jul/1995:21:04:13 -0400] \"GET "
        "/images/NASA-logosmall.gif HTTP/1.0\" 200 786";
    EXPECT_EQ(get_time(line), 805658653);
}

TEST(lab_3, parser_get_timestr) {
    char *line =
        "ix-la15-03.ix.netcom.com - - [13/Jul/1995:21:04:13 -0400] \"GET "
        "/images/NASA-logosmall.gif HTTP/1.0\" 200 786";
    EXPECT_STREQ(get_timestr(line), "13/Jul/1995:21:04:13 -0400");
}

TEST(lab_3, parser_get_response_code_str) {
    char *line =
        "ix-la15-03.ix.netcom.com - - [13/Jul/1995:21:04:13 -0400] \"GET "
        "/images/NASA-logosmall.gif HTTP/1.0\" 200 786";
    EXPECT_STREQ(get_response_code_str(line), "200");
}

TEST(lab_3, parser_get_bytes_sent) {
    char *line =
        "ix-la15-03.ix.netcom.com - - [13/Jul/1995:21:04:13 -0400] \"GET "
        "/images/NASA-logosmall.gif HTTP/1.0\" 200 786";
    EXPECT_EQ(get_bytes_sent(line), 786);
}

