#include <bits/stdc++.h>
#include <chrono>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace std::chrono;
// using namespace __gnu_pbds;
#define int long long
// #define endl "\n"
#define tej ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define mod 1000000007
#define sum(zee) (accumulate((zee).begin(), (zee).end(), 0LL))
#define mine(zee) (*min_element((zee).begin(), (zee).end()))
#define maxe(zee) (*max_element((zee).begin(), (zee).end()))
#define mini(zee) (min_element((zee).begin(), (zee).end()) - (zee).begin())
#define maxi(zee) (max_element((zee).begin(), (zee).end()) - (zee).begin())
#define cnt(zee, x) (count((zee).begin(), (zee).end(), (x)))
#define lob(zee, x) (*lower_bound((zee).begin(), (zee).end(), (x)))
#define upb(zee, x) (*upper_bound((zee).begin(), (zee).end(), (x)))
#define ojs() \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;

#define order_of_key(x) oset.order_of_key(x) // Number of elements less than x
#define find_by_order(k) *oset.find_by_order(k) // K-th smallest element (0-based index)

#define oin(x) oset.insert(x);      // O(log n)
#define oer(x) oset.erase(x);       // O(log n)

int a[1]={0};
class FastInput {
public:
    FastInput() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
    }

    int nextInt() {
        int x;
        cin >> x;
        return x;
    }

    long long nextLong() {
        long long x;
        cin >> x;
        return x;
    }
};

FastInput in;
//ostream &output = ot;
// void solve(int test)
// {
//     // Your solution here
// }

// Main function




void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

signed main() {
    tej;
    int n=in.nextInt();
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = in.nextInt();
    }

    vector<int> arr1 = arr;
    auto start = high_resolution_clock::now();
    selectionSort(arr1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Selection Sort: ";
    // printArray(arr1);
    cout << "Time taken by Selection Sort: " << duration.count() << " microseconds" << endl;

    vector<int> arr2 = arr;
    start = high_resolution_clock::now();
    insertionSort(arr2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion Sort: ";
    // printArray(arr2);
    cout << "Time taken by Insertion Sort: " << duration.count() << " microseconds" << endl;

    vector<int> arr3 = arr;
    start = high_resolution_clock::now();
    bubbleSort(arr3);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Bubble Sort: ";
    // printArray(arr3);
    cout << "Time taken by Bubble Sort: " << duration.count() << " microseconds" << endl;

    return 0;
}