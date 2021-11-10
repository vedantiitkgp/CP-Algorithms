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

int longestSequence(vi seq, int n)
{
    if (n == 1)
        return 1;
    int res, max_ending_here = 1;
    vi dp(n, 1);
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if ((seq[j] < seq[i]) && (dp[i] < dp[j] + 1))
            {
                dp[i] = dp[j] + 1;
                max_ending_here = max(max_ending_here, dp[i]);
            }
        }
    }
    return max_ending_here;
}

int main()
{
    int n;
    cin >> n;
    vi seq(n);
    for (int i = 0; i < n; i++)
        cin >> seq[i];
    cout << longestSequence(seq, n) << endl;
    return 0;
}