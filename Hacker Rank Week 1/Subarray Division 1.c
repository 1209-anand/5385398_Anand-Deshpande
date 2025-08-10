#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

/*
 * Complete the 'birthday' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY s
 *  2. INTEGER d
 *  3. INTEGER m
 */
int birthday(int s_count, int* s, int d, int m) {
    if (m > s_count || s_count == 0) return 0; 
    
    int ways = 0;
    
 
    int current_sum = 0;
    for (int i = 0; i < m; i++) {
        current_sum += s[i];
    }
    if (current_sum == d) ways++;
    
    for (int i = m; i < s_count; i++) {
        current_sum += s[i] - s[i - m];
        if (current_sum == d) ways++;
    }
    
    return ways;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    if (!fptr) return 1;

    int n = parse_int(ltrim(rtrim(readline())));
    char** s_temp = split_string(rtrim(readline()));

    int* s = malloc(n * sizeof(int));
    if (!s) return 1;
    
    for (int i = 0; i < n; i++) {
        s[i] = parse_int(s_temp[i]);
    }

    char** first_multiple_input = split_string(rtrim(readline()));
    int d = parse_int(first_multiple_input[0]);
    int m = parse_int(first_multiple_input[1]);

    int result = birthday(n, s, d, m);
    fprintf(fptr, "%d\n", result);

    fclose(fptr);
    free(s);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024, data_length = 0;
    char* data = malloc(alloc_length);
    if (!data) return NULL;

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;

        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return NULL;
    }

    if (data_length && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    } else {
        data[data_length] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return NULL;
    while (isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return NULL;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int count = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * (++count));
        if (!splits) return NULL;
        splits[count - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = (int)strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
