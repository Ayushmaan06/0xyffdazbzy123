#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int pipefds[2];
    char buffer[5];

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char *pin = "4128";

    printf("Writing PIN to pipe...\n");
    write(pipefds[1], pin, strlen(pin) + 1);  // Write to pipe
    printf("Done.\n");

    printf("Reading PIN from pipe...\n");
    read(pipefds[0], buffer, sizeof(buffer)); // Read from pipe
    printf("PIN from pipe: %s\n", buffer);

    return EXIT_SUCCESS;
}
