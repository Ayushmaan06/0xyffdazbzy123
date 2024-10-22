#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Struct to hold an element with its value, list index, and element index
typedef struct HeapNode {
    int value;
    int listIndex;
    int elementIndex;
} HeapNode;

// Min-heap struct
typedef struct MinHeap {
    HeapNode* array;
    int size;
} MinHeap;

// Utility function to swap two heap nodes
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the heap to maintain min-heap property
void heapify(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left].value < heap->array[smallest].value)
        smallest = left;

    if (right < heap->size && heap->array[right].value < heap->array[smallest].value)
        smallest = right;

    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// Function to extract the minimum element from the heap
HeapNode extractMin(MinHeap* heap) {
    HeapNode root = heap->array[0];

    if (heap->size > 1) {
        heap->array[0] = heap->array[heap->size - 1];
        heap->size--;
        heapify(heap, 0);
    } else {
        heap->size--;
    }

    return root;
}

// Function to insert a new element into the heap
void insertHeap(MinHeap* heap, HeapNode newNode) {
    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = newNode;

    // Fix the min heap property by moving the new element up
    while (i != 0 && heap->array[(i - 1) / 2].value > heap->array[i].value) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to find the smallest range covering at least one element from each list
void findSmallestRange(int** nums, int* numsSizes, int k) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (HeapNode*)malloc(k * sizeof(HeapNode));
    heap->size = 0;

    int maxValue = INT_MIN;
    int start = 0, end = INT_MAX;

    // Initialize the heap with the first element from each list
    for (int i = 0; i < k; i++) {
        HeapNode newNode = { nums[i][0], i, 0 };
        insertHeap(heap, newNode);
        if (nums[i][0] > maxValue) {
            maxValue = nums[i][0];
        }
    }

    // Process the heap
    while (1) {
        HeapNode minNode = extractMin(heap);
        int minValue = minNode.value;

        // Update the range if it's smaller than the current one
        if (maxValue - minValue < end - start) {
            start = minValue;
            end = maxValue;
        }

        // If there are no more elements in the current list, we are done
        if (minNode.elementIndex + 1 == numsSizes[minNode.listIndex]) {
            break;
        }

        // Insert the next element from the same list
        int nextValue = nums[minNode.listIndex][minNode.elementIndex + 1];
        insertHeap(heap, (HeapNode){ nextValue, minNode.listIndex, minNode.elementIndex + 1 });

        // Update the max value
        if (nextValue > maxValue) {
            maxValue = nextValue;
        }
    }

    printf("Smallest range is [%d, %d]\n", start, end);

    // Free memory
    free(heap->array);
    free(heap);
}

// Main function to take input from the user
int main() {
    int k;
    printf("Enter the number of lists: ");
    scanf("%d", &k);

    int** nums = (int**)malloc(k * sizeof(int*));
    int* numsSizes = (int*)malloc(k * sizeof(int));

    // Input the lists
    for (int i = 0; i < k; i++) {
        printf("Enter the size of list %d: ", i + 1);
        scanf("%d", &numsSizes[i]);

        nums[i] = (int*)malloc(numsSizes[i] * sizeof(int));
        printf("Enter elements of list %d: ", i + 1);
        for (int j = 0; j < numsSizes[i]; j++) {
            scanf("%d", &nums[i][j]);
        }
    }

    // Call the function to find the smallest range
    findSmallestRange(nums, numsSizes, k);

    // Free memory
    for (int i = 0; i < k; i++) {
        free(nums[i]);
    }
    free(nums);
    free(numsSizes);

    return 0;
}
