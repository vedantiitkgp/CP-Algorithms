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

//Binary Search
int findKeyBinarySearch(vi &sorted, int key, int l, int r)
{
    if (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (sorted[mid] == key)
            return mid;
        else if (sorted[mid] < key)
            return findKeyBinarySearch(sorted, key, mid + 1, r);
        else
            return findKeyBinarySearch(sorted, key, l, mid - 1);
    }
    return -1;
}

// Interpolative Search ( Variation of binary search)
int findKeyInterpolativeSearch(vi &sorted, int key, int l, int r)
{
    if (l <= r)
    {
        int pos = l + ((key - sorted[l]) * (r - l)) / (sorted[r] - sorted[l]);
        if (sorted[pos] == key)
            return pos;
        else if (sorted[pos] < key)
            return findKeyInterpolativeSearch(sorted, key, pos + 1, r);
        else
            return findKeyInterpolativeSearch(sorted, key, l, pos - 1);
    }
    return -1;
}

int main()
{
    int n, key;
    cin >> n >> key;
    vi sorted(n);
    for (int i = 0; i < n; i++)
        cin >> sorted[i];
    // cout << findKeyBinarySearch(sorted, key, 0, n - 1) << endl;
    cout << findKeyInterpolativeSearch(sorted, key, 0, n - 1) << endl;
    return 0;
}