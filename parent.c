#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Failed to create child process\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process - ID: %d, Parent ID: %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process - ID: %d, Child ID: %d\n", getpid(), pid);
    }

    return 0;
}
