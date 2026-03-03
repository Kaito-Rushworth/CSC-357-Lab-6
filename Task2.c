#include <stdio.h>
#include <stdlib.h>

int main_even(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid Argument");
        return 1;
    }

    char *endptr;
    long number = strtol(argv[1], &endptr, 10);

    if (number < 0 || *endptr != '\0') {
        printf("Invalid Argument");
        return 1;
    }

    for (int i = 1; i <= number; i++) {
        if (i % 2 == 0) {
            printf("%ld\n", i);
        }
    }
    return 0;
}

int main_odd(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid Argument");
        return 1;
    }

    char *endptr;
    long number = strtol(argv[1], &endptr, 10);

    if (number < 0 || *endptr != '\0') {
        printf("Invalid Argument");
        return 1;
    }

    for (int i = 1; i <= number; i++) {
        if (i % 2 != 0) {
            printf("%ld\n", i);
        }
    }
    return 0;
}


