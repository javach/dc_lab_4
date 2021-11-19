#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "commands.c"

int is_number(char *s) {
    printf("%s\n", s);
    printf("%lu\n", strlen(s));
    for (int i = 0; s[i] != '\0'; i++) {
        printf("%d\n", i);
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

int convert_to_int(const char *s) {
    int value;
    sscanf(s, "%d", &value);
    return value;
}

void print_usage_string(char *executable_name) {
    fprintf(stderr, "Usage: %s filename\n", executable_name);
}

void print_help() {
    printf("Commands\n");
    printf("max_period <duration> - time period with max number of requests and duration of <duration>\n");
    printf("entries_count - count number of entries in a file\n");
    printf("status_code <code> - count number of entries with response code <code>. 'x' can be used to match any number\n");
    printf("bytes_sent <op> <value> - count number of entries with bytes sent equal to, more than <value>. Use '<', '>' and '=' for <op>.\n");
    printf("help - display this message\n");
    printf("exit - exit\n\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage_string(argv[0]);
        return -1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Could not open the file '%s'\n", argv[1]);
    }

    int entries_count = command_entries_count(file);
    int terminated = 0;

    print_help();
    while (!terminated) {
        char command[100];
        scanf("%s", command);
        if (strcmp(command, "max_period") == 0) {
            int arg;
            scanf("%d", &arg);
            command_max_period(file, arg, entries_count);
        } else if (strcmp(command, "entries_count") == 0) {
            command_entries_count(file);
        } else if (strcmp(command, "status_code") == 0) {
            char arg[3];
            scanf("%s", arg);
            command_status_code(file, arg, entries_count);
        } else if (strcmp(command, "bytes_sent") == 0) {
            char arg_1;
            int arg_2;
            scanf("%s", &arg_1);
            scanf("%d", &arg_2);

            char op[11];
            if (arg_1 == '=') strcpy(op, "equals to");
            else if (arg_1 == '<') strcpy(op, "less than");
            else if (arg_1 == '>') strcpy(op, "more than");
            else {
                printf("Error! Operator must be '=', '<' or '>'\n\n");
            }

            command_bytes_sent(file, arg_2, op, entries_count);
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else if (strcmp(command, "exit") == 0) {
            terminated = 1;
        } else {
            printf("Error! Unknown command\n\n");
        }
    }

    return 0;
}