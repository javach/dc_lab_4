#include <time.h>
#include <stdio.h>
#include "parser.c"
#include "util.c"

int command_entries_count(FILE *file) {
    printf("Executing 'entries_count' command...\n");

    int entries_count = 0;
    int is_eof = 0;
    
    next_line(file, NULL, &is_eof);
    while (!is_eof) {
        entries_count++;
        next_line(file, NULL, &is_eof);
    }

    printf("This file contains %d entries.\n\n", entries_count);
    rewind(file);
    return entries_count;
}

void command_max_period(FILE *file, int duration, int entries_count) {
    printf("Executing 'max_period' command...\n");

    char line[500];
    int is_eof = 0;
    int line_index = 0;
    long max_timestamp = -1;
    int max_count = -1;
    Queue queue = init_queue();

    next_line(file, line, &is_eof);
    while (!is_eof) {
        printf_progress(line_index, entries_count);
        long timestamp = get_time(line);
        while (queue.size > 0 && queue_get_head(queue) + duration < timestamp) {
            queue_pop(&queue);
        }
        if (queue.size + 1 > max_count) {
            max_count = queue.size + 1;
            max_timestamp = timestamp;
        }
        queue_push(&queue, timestamp);

        next_line(file, line, &is_eof);
        line_index++;
    }

    long time_start = max_timestamp - duration;
    long time_end = max_timestamp;
    char time_start_str[20];
    char time_end_str[20];
    strftime(time_start_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&time_start));
    strftime(time_end_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&time_end));

    printf("\rTime period with maximum requests in %d seconds: %s - %s (%d entries total)\n\n", duration, time_start_str, time_end_str, max_count);
    rewind(file);
}

void command_status_code(FILE *file, const char *status_code, int entries_count) {
    printf("Executing 'status_code' command...\nEntries with status code %s:\n", status_code);

    char line[500];
    char copy[500];
    int is_eof = 0;
    int line_index = 0;
    int count = 0;

    next_line(file, line, &is_eof);
    while (!is_eof) {
        printf_progress(line_index, entries_count);
        strcpy(copy, line);
        char *code = get_response_code_str(copy);
        int is_passed = 1;
        for (int i = 0; i < 3; i++) {
            if (!(status_code[i] == 'x' || status_code[i] == code[i]))
                is_passed = 0;
        }
        if (is_passed) {
            count++;
            printf("\r%s\n", line);
        }

        next_line(file, line, &is_eof);
        line_index++;
    }

    printf("\r%s response code entries total: %d\n\n", status_code, count);
    rewind(file);
}

void command_bytes_sent(FILE *file, int value, const char *arg, int entries_count) {
    printf("Executing 'bytes_sent' command...\nEntries with bytes sent value %s %d\n",
           arg, value);

    char line[500];
    char copy[500];
    int is_eof = 0;
    int line_index = 0;
    int count = 0;

    next_line(file, line, &is_eof);

    while (!is_eof) {
        printf_progress(line_index, entries_count);
        strcpy(copy, line);
        int bytes_sent = get_bytes_sent(copy);
        if (strcmp(arg, "more than") == 0 && bytes_sent > value ||
            strcmp(arg, "equal to") == 0 && bytes_sent == value ||
            strcmp(arg, "less than") == 0 && bytes_sent < value) {
            printf("%s\n", line);
            count++;
        }

        next_line(file, line, &is_eof);
        line_index++;
    }

    printf("\rEntries with bytes sent value %s %d total: %d\n\n", arg, value, count);
    rewind(file);
}