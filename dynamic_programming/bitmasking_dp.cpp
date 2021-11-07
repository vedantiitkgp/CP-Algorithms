// Bitmasking an DP Problem
// https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/
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

ll countWaysUtil(int mask, int i, vi capList[], vvi &dp, int allMask, int limit)
{
    if (allMask == mask)
        return 1;

    if (i > limit)
        return 0;

    if (dp[mask][i] != -1)
        return dp[mask][i];

    //Not processing the ith cap
    ll ways = countWaysUtil(mask, i + 1, capList, dp, allMask, limit);

    int size = capList[i].size();

    for (int j = 0; j < size; j++)
    {
        if (mask & (i << capList[i][j]))
            continue;
        else
            ways += countWaysUtil(mask | (1 << capList[i][j]), i + 1, capList, dp, allMask, limit);
    }
    return dp[mask][i] = ways;
}

void countWays(int n, int limit)
{
    vvi dp(1 << (n + 1), vi(limit, -1));
    vi capList[limit + 1];
    string temp, str;
    int x;
    getline(cin, str); // Handle the newline charachter
    for (int i = 0; i < n; i++)
    {
        getline(cin, str);
        stringstream ss(str);
        while (ss >> temp)
        {
            stringstream s(temp);
            s >> x;
            capList[x].push_back(i);
        }
    }
    int allMask = (1 << n) - 1;
    cout << countWaysUtil(0, 1, capList, dp, allMask, limit) << endl;
}

int main()
{
    //No of persons and high limit for the cap
    int n, limit;
    cin >> n >> limit;
    countWays(n, limit);
    return 0;
}