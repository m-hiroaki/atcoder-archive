#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const long long MOD = 1000000007;
long long modpow(long long a, long long n, long long m)
{
    long long ans = 1;
    while (n)
    {
        if (n & 1)
        {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        n >>= 1;
    }
    return ans;
}
long long acombi(long long n, long long a)
{
    long long ans = 1, ans1 = 1;
    for (long long i = n - a + 1; i <= n; i++)
    {
        ans *= i % MOD;
        ans %= MOD;
    }

    for (long long i = 2; i <= a; i++)
        ans1 = (ans1 * i) % MOD;
    ans1 = modpow(ans1, MOD - 2, MOD);
    return ((ans % MOD) * ans1) % MOD;
}

void dfs(string s, char mx, ll N)
{
    if (s.length() == N)
    {
        cout << s.c_str() << endl;
    }
    else
    {
        for (char c = 'a'; c <= mx; c++)
        {
            dfs(s + c, ((c == mx) ? (char)(mx + 1) : mx), N);
        }
    }
}

int bfs(int a, int b, int h, int w, char tmp[][101])
{
    int ans[101][101] = {0};
    char c[101][101] = {0};
    queue<pair<int, int>> s;

    for (int i = 0; i <= h; i++)
    {
        for (int j = 0; j <= w; j++)
        {
            c[i][j] = tmp[i][j];
        }
    }

    s.push(make_pair(a, b));

    while (s.size() > 0)
    {

        pair<int, int> tmp = s.front();
        s.pop();
        c[tmp.first][tmp.second] = '#';
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (tmp.first + i < 1 || tmp.first + i > h)
                {
                    continue;
                }
                if (tmp.second + j < 1 || tmp.second + j > w)
                {
                    continue;
                }
                if (i != 0 && j != 0)
                {
                    continue;
                }
                if (i == 0 && j == 0)
                {
                    continue;
                }
                if (c[tmp.first + i][tmp.second + j] == '#')
                {
                    continue;
                }
                c[tmp.first + i][tmp.second + j] = '#';
                if (ans[tmp.first + i][tmp.second + j] == 0)
                {
                    ans[tmp.first + i][tmp.second + j] = ans[tmp.first][tmp.second] + 1;
                }
                else
                {
                    ans[tmp.first + i][tmp.second + j] = min(ans[tmp.first + i][tmp.second + j], ans[tmp.first][tmp.second] + 1);
                }
                s.push(make_pair(tmp.first + i, tmp.second + j));
            }
        }
    }

    int asd = 0;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            asd = max(a, ans[i][j]);
        }
    }

    return asd;
}

long long combi(long long n, long long k)
{
    if (n == k || k == 0)
        return 1;
    else
    {
        return combi(n - 1, k - 1) + combi(n - 1, k);
    }
}

int main()
{
    ll N;
    cin >> N;
    ll tmp[2*100000]={0};
    map<ll, ll> a;

    for (int i = 0; i < N; i++)
    {
        cin >> tmp[i];
        a[tmp[i]]++;
    }

    map<ll, ll> aa;
    map<ll, ll> aaa;
    ll total = 0;
    for (auto i = a.begin(); i != a.end(); ++i)
    {

        if (i->second > 2)
        {
            aa[i->first] = i->second*(i->second-1)/ 2;
            aaa[i->first] = (i->second-1) * (i->second - 2) / 2;
        }
        else if (i->second > 1)
        {
            aa[i->first] = i->second * (i->second - 1) / 2;
            aaa[i->first] = 0;
        }
        else
        {
            aa[i->first] = 0;
            aaa[i->first] = 0;
        }
        total += aa[i->first];
    }

    for (int k = 0; k < N; k++)
    {
        cout << total - (aa[tmp[k]] - aaa[tmp[k]]) << endl;
    }
    return 0;
}
