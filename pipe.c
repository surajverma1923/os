#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t ls_pid, wc_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        fprintf(stderr, "Failed to create pipe\n");
        return 1;
    }

    // Fork the first child process for "ls -l"
    ls_pid = fork();

    if (ls_pid < 0) {
        fprintf(stderr, "Failed to create child process for ls\n");
        return 1;
    } else if (ls_pid == 0) {
        // Child process (ls -l)
        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close unused file descriptors
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Execute "ls -l" command
        execlp("ls", "ls", "-l", NULL);

        fprintf(stderr, "Failed to execute ls\n");
        return 1;
    }

    // Fork the second child process for "wc -l"
    wc_pid = fork();

    if (wc_pid < 0) {
        fprintf(stderr, "Failed to create child process for wc\n");
        return 1;
    } else if (wc_pid == 0) {
        // Child process (wc -l)
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close unused file descriptors
        close(pipe_fd[0]);
        close(pipe_fd[1]);

        // Execute "wc -l" command
        execlp("wc", "wc", "-l", NULL);

        fprintf(stderr, "Failed to execute wc\n");
        return 1;
    }

    // Close file descriptors in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for the child processes to finish
    waitpid(ls_pid, NULL, 0);
    waitpid(wc_pid, NULL, 0);

    return 0;
}
