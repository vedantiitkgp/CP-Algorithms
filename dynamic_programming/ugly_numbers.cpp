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

int uglyNumbers(int n)
{
    int i2 = 0, i3 = 0, i5 = 0;
    vi ugly(n + 1);
    ugly[0] = 1;
    int nextMultiple2, nextMultiple3, nextMultiple5;
    nextMultiple2 = ugly[i2] * 2;
    nextMultiple3 = ugly[i3] * 3;
    nextMultiple5 = ugly[i5] * 5;
    for (int i = 1; i < n; i++)
    {
        ugly[i] = min(nextMultiple2, min(nextMultiple3, nextMultiple5));
        if (nextMultiple2 == ugly[i])
        {
            i2++;
            nextMultiple2 = ugly[i2] * 2;
        }
        if (nextMultiple3 == ugly[i])
        {
            i3++;
            nextMultiple3 = ugly[i3] * 3;
        }
        if (nextMultiple5 == ugly[i])
        {
            i5++;
            nextMultiple5 = ugly[i5] * 5;
        }
    }
    return ugly[n - 1];
}

int main()
{
    int n;
    cin >> n;
    cout << uglyNumbers(n) << endl;
    return 0;
}