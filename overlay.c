#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int choice;

    printf("1. Execute 'ls' command using execl()\n");
    printf("2. Execute 'ls' command using execv()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        execl("/bin/ls", "ls", "-l", NULL);
        printf("execl() failed to execute 'ls'\n");
    } else if (choice == 2) {
        char *args[] = { "ls", "-l", NULL };
        execv("/bin/ls", args);
        printf("execv() failed to execute 'ls'\n");
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
