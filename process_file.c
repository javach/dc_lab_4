#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_word_delimiter(char c) {
    if (c == '\n')
        return true;
    if (c == ' ')
        return true;
    if (c == '\t')
        return true;
    return false;
}

void process_file(FILE *file, int *lines_count, int *bytes_count, int *words_count) {
    *lines_count = 1;
    *bytes_count = 0;
    *words_count = 0;
    bool inside_word = false;
    char current_char;

    while ((current_char = fgetc(file)) != EOF) {
        if (current_char == '\n')
            (*lines_count)++;
        if (is_word_delimiter(current_char)) {
            inside_word = false;
        } else if (!inside_word) {
            (*words_count)++;
            inside_word = true;
        }
        (*bytes_count) += sizeof(current_char);
    }

    if (*bytes_count == 0)
        *lines_count = 0;
}