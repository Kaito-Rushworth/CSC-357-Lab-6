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

int main(int argc, char *argv[]) {
    limit_fork(50);

    if (argc != 2) {
        printf("Invalid Argument");
        return 1;
    }

    char *endptr;
    long number = strtol(argv[1], &endptr, 10);
    // Make sure that the number inputted is a valid number
    if (number <= 0 || *endptr != '\0') {
        printf("Invalid Number\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork Failed :(\n");
        return 1;
    }
    else if (pid == 0) {
        for (int i = 1; i <= number; i++) {
            if (i % 2 != 0) {
                printf("%d\n", i);
            }
        }
        exit(0);
    }
    else {
        for (int i = 1; i <= number; i++) {
            if (i % 2 == 0) {
                printf("\t%d\n", i);
            }
        }
        wait(NULL);
    }
}




