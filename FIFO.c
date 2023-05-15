#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "myfifo"

int main() {
    pid_t pid;
    int fd;
    char message[100];

    // Create FIFO
    mkfifo(FIFO_FILE, 0666);

    // Create child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Failed to create child process\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process\n");

        // Open FIFO for writing
        fd = open(FIFO_FILE, O_WRONLY);
        if (fd == -1) {
            fprintf(stderr, "Failed to open FIFO\n");
            return 1;
        }

        // Write message to FIFO
        strcpy(message, "Hello from child");
        write(fd, message, strlen(message) + 1);

        // Close FIFO
        close(fd);

        printf("Child process finished\n");
    } else {
        // Parent process
        printf("Parent process\n");

        // Open FIFO for reading
        fd = open(FIFO_FILE, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Failed to open FIFO\n");
            return 1;
        }

        // Read message from FIFO
        read(fd, message, sizeof(message));
        printf("Received message from child: %s\n", message);

        // Close FIFO
        close(fd);

        // Remove FIFO
        unlink(FIFO_FILE);

        printf("Parent process finished\n");
    }

    return 0;
}

