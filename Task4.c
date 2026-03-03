#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Invalid Argument");
        return 1;
    }

    // Open the file for writing, or it doesn't exist, make it
    int fd;
    fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        printf("Open Failed\n");
        return 1;
    }

    // Make stdout go to the file instead
    if (dup2(fd, STDOUT_FILENO) == -1) {
        printf("Duplicate Failed\n");
        return 1;
    }
    // No need for original file descriptor
    // Stdout now points to file
    close(fd);

    // Replace this program with other specified one
    // argv[1] is b
    if (execlp(argv[1], argv[1], NULL) == -1) {
        printf("Execl Failed\n");
        return 1;
    }

}
