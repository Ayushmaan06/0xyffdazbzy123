#include <bits/stdc++.h>
using namespace std;
#define int long long
#define tej ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

int topDownKnapsack(vector<int> &wt, vector<int> &val, int idx, int W, vector<vector<int>> &dp) {
    if (idx < 0 || W == 0) return 0;
    if (dp[idx][W] != -1) return dp[idx][W];

    if (wt[idx] > W) {
        dp[idx][W] = topDownKnapsack(wt, val, idx - 1, W, dp);
    } else {
        dp[idx][W] = max(
            topDownKnapsack(wt, val, idx - 1, W, dp),
            val[idx] + topDownKnapsack(wt, val, idx - 1, W - wt[idx], dp)
        );
    }
    return dp[idx][W];
}

vector<int> findSelectedItems(vector<int> &wt, vector<int> &val, vector<vector<int>> &dp, int W) {
    int n = wt.size();
    vector<int> selectedItems;
    int i = n - 1, j = W;
    
    while (i >= 0 && j > 0) {
        if (i == 0 && dp[i][j] > 0) { 
            selectedItems.push_back(i);
            break;
        }
        if (i > 0 && dp[i][j] != dp[i - 1][j]) {
            selectedItems.push_back(i);
            j -= wt[i];
        }
        i--;
    }
    
    return selectedItems;
}

void solve(int test) {
    int n, W;
    cin >> n >> W;
    vector<int> wt(n), val(n);
    for (int i = 0; i < n; i++) cin >> wt[i];
    for (int i = 0; i < n; i++) cin >> val[i];

    vector<vector<int>> memo(n, vector<int>(W + 1, -1));
    int answer = topDownKnapsack(wt, val, n - 1, W, memo);

    cout << "Maximum value: " << answer << "\n";

    vector<int> selectedItems = findSelectedItems(wt, val, memo, W);
    
    cout << "Selected items (1-based index): ";
    for (int i : selectedItems) cout << (i + 1) << " ";
    cout << "\n";
    
    cout << "Weights of selected items: ";
    for (int i : selectedItems) cout << wt[i] << " ";
    cout << "\n";
}

signed main() {
    tej;
    int test = 1;
    while (test--) {
        solve(test);
    }
    return 0;
}
