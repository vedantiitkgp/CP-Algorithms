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
typedef vector<vb> vvb;

//O(n^2) approach
void longestPalindromicSubstring(string str)
{
    int n = str.length();
    vvb dp(n, vb(n, false));
    int start = 0;
    int maxLength = 1;
    // Substring of length 1
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = true;
    }

    //Substring of length 2
    for (int i = 0; i < n - 1; i++)
    {
        if (str[i] == str[i + 1])
        {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    //Substring of length > 3
    for (int k = 3; k <= n; k++)
    {
        for (int i = 0; i < n - k + 1; i++)
        {
            int j = i + k - 1;
            if (dp[i + 1][j - 1] && str[i] == str[j])
            {
                dp[i][j] = true;
                start = i;
                maxLength = k;
            }
        }
    }
    cout << str.substr(start, maxLength) << endl;
}

int main()
{
    string str;
    cin >> str;
    longestPalindromicSubstring(str);
    return 0;
}