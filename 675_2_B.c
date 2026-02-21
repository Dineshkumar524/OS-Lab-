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
        fd = open("data.txt", O_RDONLY);

        if (fd < 0) {
            perror("File open failed");
            exit(1);
        }

        read(fd, read_buffer, sizeof(read_buffer));
        printf("\n\n%s", read_buffer);
        close(fd);
    }
    else {
        wait(NULL);
    }

    return 0;
}
