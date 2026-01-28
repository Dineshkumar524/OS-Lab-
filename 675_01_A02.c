#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    pid_t pid;
    char buffer[100];

    // Parent creates and writes to file
    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File open failed");
        exit(1);
    }

    printf("Enter text to write into file: ");
    fgets(buffer, sizeof(buffer), stdin);

    write(fd, buffer, strlen(buffer));
    close(fd);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        char read_buffer[100];
        int n;

        fd = open("data.txt", O_RDONLY);
        if (fd < 0) {
            perror("File open failed");
            exit(1);
        }

        n = read(fd, read_buffer, sizeof(read_buffer) - 1);
        if (n < 0) {
            perror("Read failed");
            close(fd);
            exit(1);
        }

        read_buffer[n] = '\0';  // null terminate

        printf("\nChild reading from file:\n%s", read_buffer);

        close(fd);
    }
    else {
        wait(NULL);
        printf("\nParent: Child finished reading.\n");
    }

    return 0;
}
