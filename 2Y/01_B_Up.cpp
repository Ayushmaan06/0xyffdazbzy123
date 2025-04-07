#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
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
int bottomUpKnapsack(vector<int> &wt, vector<int> &val, int n, int W) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for(int i=1; i<=n; i++){
        for(int w=1; w<=W; w++){
            if(wt[i-1] <= w){
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - wt[i-1]] + val[i-1]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][W];
}

void solve(int test)
{
    // Your solution here
    int n, W;
    cin >> n >> W;
    vector<int> wt(n), val(n);
    for(int i=0; i<n; i++) cin >> wt[i];
    for(int i=0; i<n; i++) cin >> val[i];

    int answer = bottomUpKnapsack(wt, val, n, W);

    cout << "Bottom-up result: " << answer << "\n";
}

// Main function
signed main() {
    tej;
    // #ifndef ONLINE_JUDGE
    //     ojs();
    // #endif

    int test=1;
    // cin >> test;
    while(test--) {
        solve(test);
    }
    return 0;
}