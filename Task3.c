#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}

// Accept only one input
int main (int argc, char *argv[]) {

    limit_fork(50);

    if (argc != 2) {
        printf("Invalid Argument");
        return 1;
    }

    // Convert input string to a number
    char *endptr;
    long number = strtol(argv[1], &endptr, 10);

    // Check that number is valid
    if (number < 0 || *endptr != '\0') {
        printf("Invalid Number");
        return 1;
    }

    // Create first child
    pid_t pid1 = fork();
    if (pid1 < 0) {
        printf("Fork Failed");
        return 1;
    }
    // If we are inside first child
    if (pid1 == 0) {
        // Replace this child with odds program
        if (execl("./odds", "odds", argv[1], NULL) == -1) {
            printf("Execl Failed");
            return 1;
        }
    }

    // Create second child
    pid_t pid2 = fork();
    if (pid2 < 0) {
        printf("Fork Failed");
        return 1;
    }
    if (pid2 == 0) {
        // Replace this child with evens program
        if (execl("./evens", "evens", argv[1], NULL) == -1) {
            printf("Exec Failed");
            return 1;
        }
    }
    // Parents wait for both children to finish
    wait(NULL);
    wait(NULL);
}
