#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 100

int main() {
    int *arr = mmap(NULL, SIZE * sizeof(int), PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (arr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    printf("Array before insertion sort:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for (int i = 1; i < SIZE; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            munmap(arr, SIZE * sizeof(int));
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {  
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }

    printf("Array after insertion sort:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    munmap(arr, SIZE * sizeof(int));
    return 0;
}
