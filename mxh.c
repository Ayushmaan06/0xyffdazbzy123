#include <stdio.h>
#include <stdlib.h>

// Define a struct to hold the element with priority and additional data
typedef struct HeapNode {
    int priority; // The priority to use for heap sorting
    int data;     // Additional data associated with the priority
} HeapNode;

typedef struct MaxHeap {
    HeapNode* array; // Array of HeapNode instead of int
    long long capacity;
    int size;
} MaxHeap;

// Function to create a heap with a given capacity
MaxHeap* createHeap(long long capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) {
        fprintf(stderr, "Memory allocation failed for heap.\n");
        exit(EXIT_FAILURE);
    }
   
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode)); // Array of HeapNode
    if (!heap->array) {
        fprintf(stderr, "Memory allocation failed for array.\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
   
    return heap;
}

// Utility function to swap two HeapNode elements
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain max heap property
void heapify(MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left].priority > heap->array[largest].priority) {
        largest = left;
    }

    if (right < heap->size && heap->array[right].priority > heap->array[largest].priority) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->array[index], &heap->array[largest]);
        heapify(heap, largest);
    }
}

// Insert a new element into the heap
void insert(MaxHeap* heap, int priority, int data) {
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot insert element.\n");
        return;
    }

    // Insert new element at the end
    heap->array[heap->size].priority = priority;
    heap->array[heap->size].data = data;
    heap->size++;

    // Move up to maintain heap property
    int i = heap->size - 1;
    while (i != 0 && heap->array[(i - 1) / 2].priority < heap->array[i].priority) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Extract the element with the maximum priority
HeapNode extractMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        return (HeapNode){-1, -1}; // Return invalid node
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    HeapNode root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

// Get the element with the maximum priority without removing it
HeapNode getMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        return (HeapNode){-1, -1}; // Return invalid node
    }
    return heap->array[0];
}

// Increase the priority of an element at a specific index
void increasePriority(MaxHeap* heap, int index, int newPriority) {
    if (index < 0 || index >= heap->size || newPriority <= heap->array[index].priority) {
        printf("Invalid increase operation.\n");
        return;
    }

    heap->array[index].priority = newPriority;
    while (index != 0 && heap->array[(index - 1) / 2].priority < heap->array[index].priority) {
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to heapify the entire array
void heapifyArray(MaxHeap* heap) {
    for (int i = (heap->size - 1) / 2; i >= 0; i--) {
        heapify(heap, i);
    }
}

// Print elements in ascending order based on priority
void printInAscendingOrder(MaxHeap* heap) {
    MaxHeap* tempHeap = createHeap(heap->size);
    
    // Copy current heap elements to tempHeap
    for (int i = 0; i < heap->size; i++) {
        tempHeap->array[i] = heap->array[i];
    }
    tempHeap->size = heap->size;

    // Extract elements one by one and store them in ascending order
    printf("Elements in ascending order of priority:\n");
    while (tempHeap->size > 0) {
        HeapNode node = extractMax(tempHeap);
        printf("Priority: %d, Data: %d\n", node.priority, node.data);
    }
    free(tempHeap->array);
    free(tempHeap);
}

// Main function
int main() {
    long long n;
    int priority, data;
    printf("Enter the number of elements: ");
    scanf("%lld", &n);

    MaxHeap* heap = createHeap(n > 10000000 ? n : 10000000); // Ensure minimum capacity of 10 million

    printf("Enter the elements (priority, data):\n");
    for (long long i = 0; i < n; i++) {
        scanf("%d %d", &priority, &data);
        insert(heap, priority, data);
    }

    heapifyArray(heap);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Extract Max\n");
        printf("3. Get Max\n");
        printf("4. Increase Priority\n");
        printf("5. Print in Ascending Order\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter priority and data to insert: ");
                scanf("%d %d", &priority, &data);
                insert(heap, priority, data);
                break;
            case 2: {
                HeapNode maxNode = extractMax(heap);
                printf("Extracted Max (Priority: %d, Data: %d)\n", maxNode.priority, maxNode.data);
                break;
            }
            case 3: {
                HeapNode maxNode = getMax(heap);
                printf("Current Max (Priority: %d, Data: %d)\n", maxNode.priority, maxNode.data);
                break;
            }
            case 4:
                printf("Enter index and new priority: ");
                int index, newPriority;
                scanf("%d %d", &index, &newPriority);
                increasePriority(heap, index, newPriority);
                break;
            case 5:
                printInAscendingOrder(heap);
                break;
            case 6:
                free(heap->array);
                free(heap);
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
