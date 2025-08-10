#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* read_line(void) {
    size_t buf_size = 1024;
    size_t len = 0;
    char *buffer = malloc(buf_size);
    if (!buffer) exit(EXIT_FAILURE);

    while (1) {
        char *ptr = buffer + len;
        if (!fgets(ptr, (int)(buf_size - len), stdin)) break;
        len += strlen(ptr);
        if (len == 0 || buffer[len - 1] == '\n') break;

        buf_size *= 2;
        buffer = realloc(buffer, buf_size);
        if (!buffer) exit(EXIT_FAILURE);
    }

    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    return buffer;
}

static char** split_tokens(char *str, int *count) {
    int slots = 0;
    char **tokens = NULL;
    char *part = strtok(str, " ");
    while (part) {
        tokens = realloc(tokens, sizeof(char*) * (slots + 1));
        if (!tokens) exit(EXIT_FAILURE);
        tokens[slots++] = part;
        part = strtok(NULL, " ");
    }
    *count = slots;
    return tokens;
}

static long long str_to_long(const char *s) {
    char *endptr;
    long long val = strtoll(s, &endptr, 10);
    if (*endptr != '\0') exit(EXIT_FAILURE);
    return val;
}

void min_max_four_sum(int total_nums, long long *numbers) {
    long long sum_all = 0;
    long long min_val = numbers[0];
    long long max_val = numbers[0];

    for (int i = 0; i < total_nums; i++) {
        sum_all += numbers[i];
        if (numbers[i] < min_val) min_val = numbers[i];
        if (numbers[i] > max_val) max_val = numbers[i];
    }

    long long min_sum = sum_all - max_val;
    long long max_sum = sum_all - min_val;

    printf("%lld %lld\n", min_sum, max_sum);
}

int main(void) {
    char *input_line = read_line();
    int num_count = 0;
    char **parts = split_tokens(input_line, &num_count);

    if (num_count != 5) {
        fprintf(stderr, "Expected 5 integers.\n");
        free(parts);
        free(input_line);
        return 1;
    }

    long long values[5];
    for (int i = 0; i < 5; i++) {
        values[i] = str_to_long(parts[i]);
    }

    min_max_four_sum(5, values);

    free(parts);
    free(input_line);
    return 0;
}

