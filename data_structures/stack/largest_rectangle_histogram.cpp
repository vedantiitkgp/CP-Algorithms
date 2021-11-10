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

int getMaxArea(vi &hist, int n)
{
    stack<int> s;
    int max_area = 0;
    int tp;
    int area_with_top;
    int i = 0;
    while (i < n)
    {
        if (s.empty() || hist[s.top()] <= hist[i])
        {
            s.push(i++);
        }
        else
        {
            tp = s.top();
            s.pop();
            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
            if (max_area < area_with_top)
            {
                max_area = area_with_top;
            }
        }
    }
    while (!s.empty())
    {
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
        if (max_area < area_with_top)
        {
            max_area = area_with_top;
        }
    }
    return max_area;
}

int main()
{
    int n;
    cin >> n;
    vi hist(n);
    for (int i = 0; i < n; i++)
        cin >> hist[i];
    cout << "Max Area : " << getMaxArea(hist, n) << endl;
    return 0;
}