#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;  // Sort by finish time
}

void activitySelection(vector<pair<int, int>> &activities) {
    sort(activities.begin(), activities.end(), compare);

    cout << "Selected activities:\n";
    
    int lastFinish = activities[0].second;
    cout << "(" << activities[0].first << ", " << activities[0].second << ")\n";

    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].first >= lastFinish) {
            cout << "(" << activities[i].first << ", " << activities[i].second << ")\n";
            lastFinish = activities[i].second;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<pair<int, int>> activities(n);  // {start, finish}

    cout << "Enter start and finish times:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i].first >> activities[i].second;
    }

    activitySelection(activities);

    return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #include <bits/stdc++.h>
using namespace std;

bool compare(const pair<double, pair<int, int>> &a, const pair<double, pair<int, int>> &b) {
    return a.first > b.first;  // Sort by value/weight ratio
}

double fractionalKnapsack(vector<pair<double, pair<int, int>>> &items, int capacity) {
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;

    for (auto &item : items) {
        int weight = item.second.first;
        int value = item.second.second;

        if (capacity >= weight) {
            maxValue += value;
            capacity -= weight;
        } else {
            maxValue += item.first * capacity;
            break;
        }
    }

    return maxValue;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<pair<double, pair<int, int>>> items(n);  // {value/weight, {weight, value}}

    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        int weight, value;
        cin >> weight >> value;
        items[i] = { (double)value / weight, {weight, value} };
    }

    cout << "Maximum value in Knapsack: " << fractionalKnapsack(items, capacity) << endl;

    return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  #include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
    return a.first > b.first; // Sort by profit in descending order
}

int jobScheduling(vector<pair<int, pair<int, int>>> &jobs) {
    sort(jobs.begin(), jobs.end(), compare);

    int n = jobs.size();
    int maxDeadline = 0;

    // Find the maximum deadline
    for (auto &job : jobs) {
        maxDeadline = max(maxDeadline, job.second.first);
    }

    vector<int> slot(maxDeadline + 1, -1); // -1 indicates empty slot
    int maxProfit = 0, countJobs = 0;

    for (auto &job : jobs) {
        int profit = job.first;
        int deadline = job.second.first;
        int id = job.second.second;

        // Find an empty slot for this job (from deadline to earlier slots)
        for (int j = deadline; j > 0; j--) {
            if (slot[j] == -1) { // If slot is empty
                slot[j] = id; // Assign job ID to slot
                maxProfit += profit;
                countJobs++;
                break;
            }
        }
    }

    cout << "Maximum Profit: " << maxProfit << endl;
    cout << "Jobs selected: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1) {
            cout << slot[i] << " ";
        }
    }
    cout << endl;

    return maxProfit;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<pair<int, pair<int, int>>> jobs(n); // {profit, {deadline, jobID}}

    cout << "Enter profit, deadline, and job ID for each job:\n";
    for (int i = 0; i < n; i++) {
        int profit, deadline, jobID;
        cin >> profit >> deadline >> jobID;
        jobs[i] = {profit, {deadline, jobID}};
    }

    jobScheduling(jobs);

    return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
