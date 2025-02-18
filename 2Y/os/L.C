#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // Pipe file descriptors
    char message[] = "Hello, Child!";
    char buffer[50];

    if (pipe(fd) == -1) {  // Create pipe
        printf("Pipe creation failed!\n");
        return 1;
    }

    int pid = fork();  // Create child process

    if (pid > 0) {  // Parent Process
        close(fd[0]);  // Close read end (not needed)
        write(fd[1], message, strlen(message) + 1);  // Write message
        close(fd[1]);  // Close write end
    } 
    else if (pid == 0) {  // Child Process
        close(fd[1]);  // Close write end (not needed)
        read(fd[0], buffer, sizeof(buffer));  // Read message
        printf("👶 Child received: %s\n", buffer);
        close(fd[0]);  // Close read end
    }

    return 0;
}
----------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1[2], fd2[2];
    char parentMessage[] = "Hi Child!";
    char childMessage[] = "Hello Parent!";
    char buffer[50];

    pipe(fd1);  // First pipe (Parent -> Child)
    pipe(fd2);  // Second pipe (Child -> Parent)

    int pid = fork();

    if (pid > 0) {  // Parent Process
        close(fd1[0]);  // Close unused read end
        write(fd1[1], parentMessage, strlen(parentMessage) + 1);
        close(fd1[1]);

        close(fd2[1]);  // Close unused write end
        read(fd2[0], buffer, sizeof(buffer));
        printf("👨 Parent received: %s\n", buffer);
        close(fd2[0]);
    } 
    else {  // Child Process
        close(fd1[1]);  // Close unused write end
        read(fd1[0], buffer, sizeof(buffer));
        printf("👶 Child received: %s\n", buffer);
        close(fd1[0]);

        close(fd2[0]);  // Close unused read end
        write(fd2[1], childMessage, strlen(childMessage) + 1);
        close(fd2[1]);
    }

    return 0;
}
----------------------------------------------------
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);
    int pid = fork();

    if (pid == 0) {  // Child process
        close(fd[1]);  // Close write end
        dup2(fd[0], STDIN_FILENO);  // Redirect pipe input to stdin
        execlp("wc", "wc", "-l", NULL);  // Run wc -l
    } 
    else {  // Parent process
        close(fd[0]);  // Close read end
        write(fd[1], "hello\nworld\n", 12);  // Send data
        close(fd[1]);
    }

    return 0;
}

---------------------------------------------------------
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec!\n");
    execl("/bin/ls", "ls", "-l", NULL);  // Replaces this process with `ls -l`
    printf("This will not print if exec succeeds!\n"); // Won’t execute if exec works
    return 0;
}

---------------------------------------
#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args);
    printf("This will not print if exec succeeds!\n");
    return 0;
}

------------------------------------------------------------------
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4  // Number of threads
long long total_sum = 0; // Shared variable for sum
pthread_mutex_t mutex;  // Mutex for synchronization

typedef struct {
    int start;
    int end;
} Range;

// Function executed by each thread
void* partial_sum(void* arg) {
    Range* range = (Range*)arg;
    long long sum = 0;

    for (int i = range->start; i <= range->end; i++) {
        sum += i;
    }

    // Synchronize access to shared variable
    pthread_mutex_lock(&mutex);
    total_sum += sum;
    pthread_mutex_unlock(&mutex);

    free(range); // Free allocated memory
    return NULL;
}

int main() {
    int N = 100; // Change N as needed
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    int chunk_size = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        Range* range = (Range*)malloc(sizeof(Range));
        range->start = i * chunk_size + 1;
        range->end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, partial_sum, (void*)range);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy mutex

    printf("Sum of first %d numbers: %lld\n", N, total_sum);
    return 0;
}
---------------------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
long long factorial_result = 1;
pthread_mutex_t mutex;

typedef struct {
    int start;
    int end;
} Range;

// Function executed by each thread
void* partial_factorial(void* arg) {
    Range* range = (Range*)arg;
    long long partial_result = 1;

    for (int i = range->start; i <= range->end; i++) {
        partial_result *= i;
    }

    // Synchronize access to shared variable
    pthread_mutex_lock(&mutex);
    factorial_result *= partial_result;
    pthread_mutex_unlock(&mutex);

    free(range);
    return NULL;
}

int main() {
    int N = 10; // Change N as needed
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    int chunk_size = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        Range* range = (Range*)malloc(sizeof(Range));
        range->start = i * chunk_size + 1;
        range->end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, partial_factorial, (void*)range);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Factorial of %d: %lld\n", N, factorial_result);
    return 0;
}
-----------------------------------------------------------------------------
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables to store results
long long sum_result = 0;
long long factorial_result = 1;
long long array_sum_result = 0;

// Structure to pass arguments to threads
typedef struct {
    int start;
    int end;
    int* arr;
    int size;
} ThreadArgs;

// Function to calculate sum of first N numbers
void* sum_function(void* arg) {
    int N = *(int*)arg; // Extract the value of N
    for (int i = 1; i <= N; i++) {
        sum_result += i; // Calculate sum
    }
    return NULL;
}

// Function to calculate factorial of N
void* factorial_function(void* arg) {
    int N = *(int*)arg; // Extract the value of N
    for (int i = 1; i <= N; i++) {
        factorial_result *= i; // Calculate factorial
    }
    return NULL;
}

// Function to calculate sum of an array
void* array_sum_function(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg; // Extract array data
    for (int i = 0; i < args->size; i++) {
        array_sum_result += args->arr[i]; // Calculate array sum
    }
    return NULL;
}

int main() {
    int N = 5; // Change this value as needed
    int arr[] = {1, 2, 3, 4, 5}; // Example array
    int array_size = sizeof(arr) / sizeof(arr[0]); // Get array size

    pthread_t thread1, thread2, thread3; // Declare threads

    // Create threads to run each function
    pthread_create(&thread1, NULL, sum_function, (void*)&N);
    pthread_create(&thread2, NULL, factorial_function, (void*)&N);

    // Struct for passing array details
    ThreadArgs args = {0, array_size, arr, array_size};
    pthread_create(&thread3, NULL, array_sum_function, (void*)&args);

    // Wait for all threads to finish execution
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Print results
    printf("Sum of first %d numbers: %lld\n", N, sum_result);
    printf("Factorial of %d: %lld\n", N, factorial_result);
    printf("Sum of array: %lld\n", array_sum_result);

    return 0;
}
------------------------------------------------------------------------------
#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For close(), write()

int main() {
    int file = open("example.txt", O_WRONLY | O_CREAT, 0644); 
    // O_WRONLY → Write only, O_CREAT → Create if not exists, 0644 → Permission

    if (file < 0) {
        perror("File opening failed");
        return 1;
    }

    char data[] = "Hello, this is a test file.\n";
    write(file, data, sizeof(data)); // Writing data to file

    close(file); // Closing the file
    printf("Data written to example.txt\n");

    return 0;
}
---------------------------------------------------------------------------------
#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For close(), read()

int main() {
    int file = open("example.txt", O_RDONLY); // Open file in read-only mode

    if (file < 0) {
        perror("File opening failed");
        return 1;
    }

    char buffer[100]; 
    int bytesRead = read(file, buffer, sizeof(buffer)); // Reading file content

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null terminate string
        printf("File content:\n%s\n", buffer);
    }

    close(file); // Closing file
    return 0;
}
--------------------------------------------------------------------
#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For close(), write()

int main() {
    int file = open("example.txt", O_WRONLY | O_APPEND); 
    // O_APPEND → Moves to end of file and writes

    if (file < 0) {
        perror("File opening failed");
        return 1;
    }

    char newData[] = "Appending new content!\n";
    write(file, newData, sizeof(newData)); // Writing new data

    close(file); // Closing file
    printf("Data appended successfully.\n");

    return 0;
}
------------------------------------------------------------
#include <stdio.h>
#include <unistd.h> // For unlink()

int main() {
    if (unlink("example.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("File deletion failed");
    }
    return 0;
}
----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 10  // Define array size

// Function to merge two sorted halves
void merge(int arr[], int left[], int right[], int mid, int size) {
    int i = 0, j = 0, k = 0;
    
    while (i < mid && j < (size - mid)) {
        if (left[i] < right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < mid) 
        arr[k++] = left[i++];

    while (j < (size - mid)) 
        arr[k++] = right[j++];
}

// Function to sort an array (Bubble Sort for simplicity)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[SIZE] = {10, 3, 15, 7, 8, 23, 74, 18, 5, 20};
    int mid = SIZE / 2;

    int fd1[2], fd2[2]; // Pipes for communication
    pipe(fd1);
    pipe(fd2);

    pid_t pid1 = fork(); // Create first child

    if (pid1 == 0) {
        // Child 1: Sorts the first half
        close(fd1[0]); // Close read end
        bubbleSort(arr, mid);
        write(fd1[1], arr, mid * sizeof(int));
        close(fd1[1]); // Close write end
        exit(0);
    }

    pid_t pid2 = fork(); // Create second child

    if (pid2 == 0) {
        // Child 2: Sorts the second half
        close(fd2[0]); // Close read end
        bubbleSort(arr + mid, SIZE - mid);
        write(fd2[1], arr + mid, (SIZE - mid) * sizeof(int));
        close(fd2[1]); // Close write end
        exit(0);
    }

    // Parent process
    wait(NULL);
    wait(NULL);

    // Reading sorted halves from children
    int left[mid], right[SIZE - mid];
    close(fd1[1]); close(fd2[1]); // Close write ends

    read(fd1[0], left, mid * sizeof(int));
    read(fd2[0], right, (SIZE - mid) * sizeof(int));

    close(fd1[0]); close(fd2[0]); // Close read ends

    // Parent merges the sorted halves
    merge(arr, left, right, mid, SIZE);

    // Display sorted array
    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
