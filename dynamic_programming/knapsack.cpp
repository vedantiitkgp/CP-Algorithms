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

int knapsack(int n, int W, vi &val, vi &weight)
{
    vvi dp(n + 1, vi(W + 1));
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (n == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
            {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            }
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main()
{
    int n, W;
    cin >> n >> W;
    vi val(n);
    vi weight(n);
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
    }
    cout << knapsack(n, W, val, weight) << endl;
    return 0;
}