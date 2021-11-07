// Subset sum problem
// https://www.geeksforgeeks.org/subset-sum-problem-dp-25/
#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;

bool IsSubsetSum(vvi &dp, vi set, int n, int sum)
{
    if (sum == 0)
        return true;
    if (n == 0)
        return false;
    if (dp[n - 1][sum] != -1)
        return dp[n - 1][sum];

    if (set[n - 1] > sum)
        return dp[n - 1][sum] = IsSubsetSum(dp, set, n - 1, sum);
    return dp[n - 1][sum] = IsSubsetSum(dp, set, n - 1, sum) || IsSubsetSum(dp, set, n - 1, sum - set[n - 1]);
}

int main()
{
    int n, sum;
    cin >> n >> sum;
    vi set(n);
    vvi dp(n + 1, vi(sum + 1, -1));
    for (int i = 0; i < n; i++)
    {
        cin >> set[i];
    }
    cout << IsSubsetSum(dp, set, n, sum) << endl;
    return 0;
}