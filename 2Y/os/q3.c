#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100;
    printf("Initial value of x: %d (pid:%d)\n", x, (int) getpid());

    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("Child process before changing x: %d (pid:%d)\n", x, (int) getpid());
        x = 200;
        printf("Child process after changing x: %d (pid:%d)\n", x, (int) getpid());
    } else { // parent process
        printf("Parent process before changing x: %d (pid:%d)\n", x, (int) getpid());
        x = 300;
        printf("Parent process after changing x: %d (pid:%d)\n", x, (int) getpid());
        int rc_wait = waitpid(rc, NULL, 0); // wait for the specific child process
    }
    return 0;
}