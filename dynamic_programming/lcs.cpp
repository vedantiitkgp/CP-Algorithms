// Calculating a LCS and Printing it
// https://www.geeksforgeeks.org/printing-longest-common-subsequence/
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

void printLCS(vvi dp, string suspect1, string suspect2, int m, int n)
{
    string result;
    int i = m, j = n;
    int index = dp[m][n];
    while (i > 0 && j > 0)
    {
        if (suspect1[i - 1] == suspect2[j - 1])
        {
            result.push_back(suspect1[i - 1]);
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
            j--;
    }
    reverse(result.begin(), result.end());
    cout << result << endl;
}

//Memoization(Similar is tabulation approach)

int lcsUtil(vvi &dp, string suspect1, string suspect2, int m, int n)
{
    if (m < 1 || n < 1)
        return 0;
    else if (dp[m][n] != -1)
        return dp[m][n];

    if (suspect1[m - 1] == suspect2[n - 1])
        return dp[m][n] = 1 + lcsUtil(dp, suspect1, suspect2, m - 1, n - 1);
    else
    {
        return dp[m][n] = max(lcsUtil(dp, suspect1, suspect2, m - 1, n), lcsUtil(dp, suspect1, suspect2, m, n - 1));
    }
}

void lcs(string suspect1, string suspect2)
{
    int m = suspect1.length();
    int n = suspect2.length();
    vvi dp(m + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[0][i] = 0;
    }
    lcsUtil(dp, suspect1, suspect2, m, n);
    printLCS(dp, suspect1, suspect2, m, n);
}

int main()
{
    string suspect1, suspect2;
    cin >> suspect1 >> suspect2;
    lcs(suspect1, suspect2);
    return 0;
}