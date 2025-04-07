#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<double, pair<int, int>> &a, const pair<double, pair<int, int>> &b) {
    return a.first > b.first;  // Sort by value/weight ratio
}

double fractionalKnapsack(vector<pair<double, pair<int, int>>> &items, int capacity) {
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;
    vector<pair<int, int>> selectedItems;  // To store selected items and their weights

    for (auto &item : items) {
        int weight = item.second.first;
        int value = item.second.second;

        if (capacity >= weight) {
            maxValue += value;
            capacity -= weight;
            selectedItems.push_back({weight, value});
        } else {
            maxValue += item.first * capacity;
            selectedItems.push_back({capacity, (int)(item.first * capacity)});
            break;
        }
    }

    // Print selected items and their weights
    cout << "Selected items (weight, value):\n";
    for (auto &selectedItem : selectedItems) {
        cout << "(" << selectedItem.first << ", " << selectedItem.second << ")\n";
    }

    return maxValue;
}

int main() {
    int n, capacity;
    // cout << "Enter number of items: ";
    cin >> n;
    
    // cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<pair<double, pair<int, int>>> items(n);  // {value/weight, {weight, value}}

    // cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        int weight, value;
        cin >> weight >> value;
        items[i] = { (double)value / weight, {weight, value} };
    }

    cout << "Maximum value in Knapsack: " << fractionalKnapsack(items, capacity) << endl;

    return 0;
}