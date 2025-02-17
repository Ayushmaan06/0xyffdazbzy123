#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

void getPIN(char pin[PIN_LENGTH + 1]) {
    srand(getpid() + time(NULL));
    pin[0] = '1' + rand() % 7;
    for (int i = 1; i < PIN_LENGTH; i++) {
        pin[i] = '0' + rand() % 7;
    }
    pin[PIN_LENGTH] = '\0';
}

int main(void) {
    while (1) {
        int pipefds[2];
        char pin[PIN_LENGTH + 1];
        char buffer[PIN_LENGTH + 1];

        pipe(pipefds);

        pid_t pid = fork();

        if (pid == 0) { // Child process
            getPIN(pin);
            close(pipefds[0]); // Close read end
            write(pipefds[1], pin, PIN_LENGTH + 1);
            printf("Generated PIN in child: %s\n", pin);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) { // Parent process
            wait(NULL); // Wait for child
            close(pipefds[1]); // Close write end
            read(pipefds[0], buffer, PIN_LENGTH + 1);
            printf("Parent received PIN: %s\n", buffer);
        }
    }
    return EXIT_SUCCESS;
}
