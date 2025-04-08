#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_REF_LEN 100

// FIFO simulation function
void simulate_FIFO(int ref[], int n, int frames) {
    int *frame = malloc(sizeof(int) * frames);
    int front = 0;
    int hits = 0, misses = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                hits++;
                found = true;
                break;
            }
        }
        if (!found) {
            frame[front] = ref[i];
            front = (front + 1) % frames;
            misses++;
        }
    }
    printf("FIFO (frames = %d): Hits = %d, Misses = %d, Hit Ratio = %.2f%%\n",
           frames, hits, misses, (float)hits / n * 100);
    free(frame);
}

// LRU simulation function
void simulate_LRU(int ref[], int n, int frames) {
    int *frame = malloc(sizeof(int) * frames);
    int *lastUsed = malloc(sizeof(int) * frames);
    int hits = 0, misses = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                hits++;
                lastUsed[j] = i;
                found = true;
                break;
            }
        }
        if (!found) {
            misses++;
            int emptyIndex = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }
            if (emptyIndex != -1) {
                frame[emptyIndex] = ref[i];
                lastUsed[emptyIndex] = i;
            } else {
                
                int lru = INT_MAX, lruIndex = -1;
                for (int j = 0; j < frames; j++) {
                    if (lastUsed[j] < lru) {
                        lru = lastUsed[j];
                        lruIndex = j;
                    }
                }
                frame[lruIndex] = ref[i];
                lastUsed[lruIndex] = i;
            }
        }
    }
    printf("LRU (frames = %d): Hits = %d, Misses = %d, Hit Ratio = %.2f%%\n",
           frames, hits, misses, (float)hits / n * 100);
    free(frame);
    free(lastUsed);
}

// Optimal simulation function
void simulate_Optimal(int ref[], int n, int frames) {
    int *frame = malloc(sizeof(int) * frames);
    int hits = 0, misses = 0;
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                hits++;
                found = true;
                break;
            }
        }
        if (!found) {
            misses++;
            int emptyIndex = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {  
                    emptyIndex = j;
                    break;
                }
            }
            if (emptyIndex != -1) {
                frame[emptyIndex] = ref[i];
            } else {
                
                int farthest = i, indexToReplace = -1;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i+1; k < n; k++) {
                        if (frame[j] == ref[k])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        indexToReplace = j;
                    }
                }
                
                if (indexToReplace == -1)
                    indexToReplace = 0;
                frame[indexToReplace] = ref[i];
            }
        }
    }
    printf("Optimal (frames = %d): Hits = %d, Misses = %d, Hit Ratio = %.2f%%\n",
           frames, hits, misses, (float)hits / n * 100);
    free(frame);
}

int main() {
    int ref[MAX_REF_LEN];
    int n;
    
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);
    if(n > MAX_REF_LEN) {
        printf("Maximum reference string length is %d\n", MAX_REF_LEN);
        return 1;
    }
    printf("Enter the reference string (space separated integers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }
    
    int framesToTest[] = {3, 4, 5};
    int testCount = sizeof(framesToTest) / sizeof(framesToTest[0]);
    
    for (int i = 0; i < testCount; i++) {
        int frames = framesToTest[i];
        simulate_FIFO(ref, n, frames);
        simulate_LRU(ref, n, frames);
        simulate_Optimal(ref, n, frames);
        printf("---------------------------\n");
    }
    
    return 0;
}
