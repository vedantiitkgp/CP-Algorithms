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

// O(n) time
int fibonacci(int n)
{
    if (n == 0 || n == 1)
        return n;
    int l1, l2, l3;
    l1 = 0;
    l2 = 1;
    for (int i = 2; i <= n; i++)
    {
        l3 = l1 + l2;
        l1 = l2;
        l2 = l3;
    }
    return l3;
}

void multiply(vvl &F, vvl &M)
{
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
void power(vvl &F, ll n)
{
    if (n == 0 || n == 1)
        return;
    vvl M(2, vl(2));
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
    {
        multiply(F, M);
    }
}
ll fibonacci_logn(ll n)
{
    if (n == 0)
        return 0;
    vvl F(2, vl(2));
    F[0][0] = 1;
    F[0][1] = 1;
    F[1][0] = 1;
    F[1][1] = 0;
    power(F, n - 1);
    return F[0][0];
}

int main()
{
    int n;
    cin >> n;
    cout << fibonacci_logn(n) << endl;
    return 0;
}