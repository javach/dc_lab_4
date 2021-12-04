#include <fstream>
#include <gtest/gtest.h>
#include "process_file.c"
#include <unistd.h>

class FileTest : public ::testing::Test {
    void SetUp() override {
        std::ofstream file_1("file_1.txt");
        std::ofstream file_2("file_2.txt");
        std::ofstream file_3("file_3.txt");

        file_1 << "word word word word\nword word word word";
        file_2 << "♥ ♥ ♥ ♥♥ as\n♥";
        file_3 << "iwqw sa    asdasd qw\nqw  wqewqw eee    \n\n";

        file_1.close();
        file_2.close();
        file_3.close();
    }

    void TearDown() override {
        std::remove("file_1.txt");
        std::remove("file_2.txt");
        std::remove("file_3.txt");
    }
};

TEST_F(FileTest, sample_1) {
    int lines_count;
    int bytes_count;
    int words_count;
    FILE *file = fopen("file_1.txt", "r");

    process_file(file, &lines_count, &bytes_count, &words_count);

    EXPECT_EQ(lines_count, 2);
    EXPECT_EQ(words_count, 8);
    EXPECT_EQ(bytes_count, 39);
}

TEST_F(FileTest, sample_2) {
     int lines_count;
    int bytes_count;
    int words_count;
    FILE *file = fopen("file_2.txt", "r");

    process_file(file, &lines_count, &bytes_count, &words_count);

    EXPECT_EQ(lines_count, 2);
    EXPECT_EQ(words_count, 6);
    EXPECT_EQ(bytes_count, 25);
}

TEST_F(FileTest, sample_3) {
     int lines_count;
    int bytes_count;
    int words_count;
    FILE *file = fopen("file_3.txt", "r");

    process_file(file, &lines_count, &bytes_count, &words_count);

    EXPECT_EQ(lines_count, 4);
    EXPECT_EQ(words_count, 7);
    EXPECT_EQ(bytes_count, 41);
}
