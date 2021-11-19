#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_usage_string(char* executable_name) {
    printf("Usage: %s filename [-l | --lines] [-b | --bytes] [-w | --words]\n", executable_name);
}

bool is_word_delimiter(char c) {
    if (c == '\n')
        return true;
    if (c == ' ')
        return true;
    if (c == '\t')
        return true;
    return false;
}

int main(int argc, char *argv[]) {

    // output flags
    bool lines_flag = false;
    bool bytes_flag = false;
    bool words_flag = false;

    if (argc < 2) {
        print_usage_string(argv[0]);
        return 0;
    }


    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Could not open the file '%s'\n", argv[1]);
        return 0;
    }

    // parse args
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--lines") == 0 || strcmp(argv[i], "-l") == 0)
            lines_flag = true;
        else if (strcmp(argv[i], "--bytes") == 0 || strcmp(argv[i], "-b") == 0)
            bytes_flag = true;
        else if (strcmp(argv[i], "--words") == 0 || strcmp(argv[i], "-w") == 0)
            words_flag = true;
        else {
            print_usage_string(argv[0]);
            return 0;
        }
    }

    int lines_count = 1;
    int bytes_count = 0;
    int words_count = 0;

    bool inside_word = false;
    char current_char;

    while ((current_char = fgetc(input_file)) != EOF) {
        if (current_char == '\n')
            lines_count++;
        if (is_word_delimiter(current_char)) {
            inside_word = false;
        } else if (!inside_word) {
            words_count++;
            inside_word = true;
        }
        bytes_count += sizeof(current_char);
    }

    if (bytes_count == 0)
        lines_count = 0;

    bool all_flag = !words_flag && !lines_flag && !bytes_flag;

    if (all_flag || lines_flag)
        printf("Lines: %d\n", lines_count);
    if (all_flag || words_flag)
        printf("Words: %d\n", words_count);
    if (all_flag || bytes_flag)
        printf("Bytes: %d\n", bytes_count);

    return 0;
}
