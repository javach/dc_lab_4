#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Log Parse

const char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sen", "Oct", "Nov", "Dec"};

void parse_token(char *str, const char *delim, const char *sscanf_str, void *pointer) {
    if (pointer != NULL)
        sscanf(strtok(str, delim), sscanf_str, pointer);
    else
        strtok(str, delim);
}

int get_month(char *month_str) {
    for (int i = 0; i < 12; i++)
        if (strcmp(months[i], month_str) == 0)
            return i;
    return 0;
}

long convert_date_to_timestamp(char *time_str) {
    struct tm tm;
    char month_temp[4];
    parse_token(time_str, "/", "%d", &tm.tm_mday);
    parse_token(NULL, "/", "%s", &month_temp);
    parse_token(NULL, ":", "%d", &tm.tm_year);
    parse_token(NULL, ":", "%d", &tm.tm_hour);
    parse_token(NULL, ":", "%d", &tm.tm_min);
    parse_token(NULL, " ", "%d", &tm.tm_sec);

    tm.tm_mon = get_month(month_temp);
    tm.tm_year -= 1900;

    return (long) mktime(&tm);
}

// TODO: destructive usage of strtok()
char *get_addr(char *line) {
    char *addr = strtok(line, " ");
    return addr;
}

// TODO: destructive usage of strtok()
long get_time(char *line) {
    strtok(line, "[");
    char *ltime_str = strtok(NULL, "]");
    long result = convert_date_to_timestamp(ltime_str);
    return result;
}

// TODO: destructive usage of strtok()
char *get_timestr(char *line) {
    strtok(line, "[");
    return strtok(NULL, "]");
}

// TODO: destructive usage of strtok()
int get_response_code(char *line) {
    strtok(line, "\"");
    strtok(NULL, "\"");
    int result;
    parse_token(NULL, " ", "%d", &result);
    return result;
}

// TODO: destructive usage of strtok()
char *get_response_code_str(char *line) {
    strtok(line, "\"");
    strtok(NULL, "\"");
    return strtok(NULL, " ");
}

// TODO: destructive usage of strtok()
int get_bytes_sent(char *line) {
    strtok(line, "\"");
    strtok(NULL, "\"");
    strtok(NULL, " ");
    int result;
    parse_token(NULL, " ", "%d", &result);
    return result;
}

// File Parse

void next_line(FILE *file, char line[500], int *is_eof) {
    if (line != NULL)
        memset(line, 0, 500 * (sizeof(line[0])));
    char current_char = fgetc(file);
    int current_index = 0;
    while (current_char != EOF && current_char != '\n') {
        if (line != NULL)
            line[current_index] = current_char;
        current_char = fgetc(file);
        current_index++;
    }

    if (current_char == EOF)
        *is_eof = 1;
}

void printf_progress(int line_index, int entries_count) {
    if (line_index % 10000 != 0)
        return;
    printf("\r%.2f%% [%d / %d]", 1.0 * line_index / entries_count * 100.0, line_index, entries_count);
    fflush(stdout);
}
