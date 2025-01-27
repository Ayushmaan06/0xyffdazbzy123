#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to merge two subarrays for Merge Sort
void merge(vector<int>& arr, int l, int m, int r, int& steps) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        steps++;
    }     
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        steps++;
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        steps++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        steps++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        steps++;
    }
}

// Merge Sort function
void mergeSort(vector<int>& arr, int l, int r, int& steps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, steps);
        mergeSort(arr, m + 1, r, steps);
        merge(arr, l, m, r, steps);
    }
}

// Function to heapify a subtree for Heap Sort
void heapify(vector<int>& arr, int n, int i, int& steps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        steps++;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        steps++;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        steps++;
        heapify(arr, n, largest, steps);
    }
}

// Heap Sort function
void heapSort(vector<int>& arr, int& steps) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, steps);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        steps++;
        heapify(arr, i, 0, steps);
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high, int& steps) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            steps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    steps++;
    return (i + 1);
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high, int& steps) {
    if (low < high) {
        int pi = partition(arr, low, high, steps);
        quickSort(arr, low, pi - 1, steps);
        quickSort(arr, pi + 1, high, steps);
    }
}

void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

    int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> arr1 = arr, arr2 = arr, arr3 = arr;
    int stepsMerge = 0, stepsHeap = 0, stepsQuick = 0;

    auto start = high_resolution_clock::now();
    mergeSort(arr1, 0, n - 1, stepsMerge);
    printArray(arr1);
    auto end = high_resolution_clock::now();
    auto durationMerge = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    heapSort(arr2, stepsHeap);
    printArray(arr2);
    end = high_resolution_clock::now();
    auto durationHeap = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    quickSort(arr3, 0, n - 1, stepsQuick);
    printArray(arr3);
    end = high_resolution_clock::now();
    auto durationQuick = duration_cast<nanoseconds>(end - start).count();

    cout << "Merge Sort took " << durationMerge << " nanoseconds and " << stepsMerge << " steps.\n";
    cout << "Heap Sort took " << durationHeap << " nanoseconds and " << stepsHeap << " steps.\n";
    cout << "Quick Sort took " << durationQuick << " nanoseconds and " << stepsQuick << " steps.\n";

    return 0;
}