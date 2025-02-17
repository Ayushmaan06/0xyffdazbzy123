#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int pipefds[2];
    char buffer[5];

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) { // Child process
        char *pin = "4821";
        close(pipefds[0]);  // Close read end
        write(pipefds[1], pin, strlen(pin) + 1);
        printf("Generating PIN in child and sending to parent...\n");
        exit(EXIT_SUCCESS);
    } else if (pid > 0) { // Parent process
        wait(NULL);  // Wait for child
        close(pipefds[1]);  // Close write end
        read(pipefds[0], buffer, sizeof(buffer));
        printf("Parent received PIN '%s'\n", buffer);
    }

    return EXIT_SUCCESS;
}
