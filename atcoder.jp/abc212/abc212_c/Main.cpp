#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const long double PI = (acos(-1));
const unsigned long long MOD = 1000000007;
struct Edge
{
    long long to;
    long long cost;
};
using Graph = vector<vector<Edge>>;
using P = pair<ll, ll>;
const long long INF = 1LL << 60;
#define ALL(a) (a).begin(), (a).end()
#define rep(i, n) for (int i = 0; i < n; i++)

vector<long long> fact, fact_inv, inv;
/*  init_nCk :二項係数のための前処理
    計算量:O(n)
*/
void init_nCk(int SIZE)
{
    fact.resize(SIZE + 5);
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact[0] = fact[1] = 1;
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++)
    {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
}
/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(1)
*/
long long nCk(int n, int k)
{
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
}

bool is_prime(ll x)
{
    if (x == 1)
    {
        return false;
    }
    for (ll i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

long long modpow(long long a, long long n, long long mod)
{
    long long res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

std::vector<std::vector<long long>> comb(int n, int r)
{
    std::vector<std::vector<long long>> v(n + 1, std::vector<long long>(n + 1, 0));
    for (int i = 0; i < v.size(); i++)
    {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (int j = 1; j < v.size(); j++)
    {
        for (int k = 1; k < j; k++)
        {
            v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
        }
    }
    return v;
}

unsigned long long combi(unsigned long long n, unsigned long long a)
{
    unsigned long long ans = 1, ans1 = 1;
    for (unsigned long long i = n - a + 1; i <= n; i++)
    {
        ans *= i % MOD;
        ans %= MOD;
    }

    for (unsigned long long i = 2; i <= a; i++)
        ans1 = (ans1 * i) % MOD;
    ans1 = modpow(ans1, MOD - 2, MOD);
    return ((ans % MOD) * ans1) % MOD;
}

void dfs(vector<ll> s, ll mi, ll mx, ll N, vector<vector<ll>> &arr)
{
    if (s.size() == (size_t)N)
    {
        //cout << s.c_str() << endl;
        arr.push_back(s);
    }
    else
    {
        for (ll c = s.size() > 0 ? 0 : mi; c <= mx; c++)
        {
            s.push_back(c);
            dfs(s, mi, mx, N, arr);
            s.pop_back();
        }
    }

    return;
}

ll bfs(int sx, int sy, int gx, int gy, int h, int w, vector<vector<char>> map)
{
    queue<pair<int, int>> s;

    vector<vector<ll>> ans;

    for (int i = 0; i < h; i++)
    {
        vector<ll> aa(w);
        ans.push_back(aa);
    }

    s.push(make_pair(sx, sy));
    while (s.size() > 0)
    {

        pair<int, int> tmp = s.front();
        s.pop();
        map[tmp.first][tmp.second] = '#';
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (tmp.first + i < 0 || tmp.first + i >= h)
                {
                    continue;
                }
                if (tmp.second + j < 0 || tmp.second + j >= w)
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
                if (map[tmp.first + i][tmp.second + j] == '#')
                {
                    continue;
                }
                map[tmp.first + i][tmp.second + j] = '#';
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

    return ans[gx][gy];
}

template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
    /* Credits: Thomas Draper */
    if ((first == last) || (first == k) || (last == k))
        return false;
    Iterator itr1 = first;
    Iterator itr2 = last;
    ++itr1;
    if (last == itr1)
        return false;
    itr1 = last;
    --itr1;
    itr1 = k;
    --itr2;
    while (first != itr1)
    {
        if (*--itr1 < *itr2)
        {
            Iterator j = k;
            while (!(*itr1 < *j))
                ++j;
            iter_swap(itr1, j);
            ++itr1;
            ++j;
            itr2 = k;
            rotate(itr1, j, last);
            while (last != j)
            {
                ++j;
                ++itr2;
            }
            rotate(k, itr2, last);
            return true;
        }
    }
    rotate(first, k, last);
    return false;
}
ll modfactorial(ll a)
{
    if (a == 1 || a == 0)
        return 1;

    return ((a % MOD) * (modfactorial(a - 1) % MOD)) % MOD;
}

ll gcd(ll a, ll b)
{
    if (a % b == 0)
    {
        return (b);
    }
    else
    {
        return (gcd(b, a % b));
    }
}

ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

map<ll, ll> prime_factor(ll n)
{
    map<ll, ll> ret;
    for (ll i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            ret[i]++;
            n /= i;
        }
    }
    if (n != 1)
        ret[n] = 1;
    return ret;
}

struct UnionFind
{
    //自身が親であれば、その集合に属する頂点数に-1を掛けたもの
    //そうでなければ親のid
    vector<int> r;

    UnionFind(int N)
    {
        r = vector<int>(N, -1);
    }

    int root(int x)
    {
        if (r[x] < 0)
            return x;
        return r[x] = root(r[x]);
    }

    bool same(int x, int y)
    { // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }

    bool unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (r[x] > r[y])
            swap(x, y);
        r[x] += r[y];
        r[y] = x;
        return true;
    }

    int size(int x)
    {
        return -r[root(x)];
    }
};

/* dijkstra(G,s,dis)
    入力：グラフ G, 開始点 s, 距離を格納する dis
    計算量：O(|E|log|V|)
    副作用：dis が書き換えられる
*/
void dijkstra(const Graph &G, int s, vector<ll> &dis, vector<ll> &prev)
{
    ll N = G.size();
    dis.resize(N, INF);
    prev.resize(N, -1); // 初期化
    priority_queue<P, vector<P>, greater<P>> pq;
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty())
    {
        P p = pq.top();
        pq.pop();
        ll v = p.second;
        if (dis[v] < p.first)
        {
            continue;
        }
        for (auto &e : G[v])
        {
            if (dis[e.to] > dis[v] + e.cost)
            {
                dis[e.to] = dis[v] + e.cost;
                prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

vector<ll> get_path(const vector<ll> &prev, ll t)
{
    vector<ll> path;
    for (ll cur = t; cur != -1; cur = prev[cur])
    {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
}

vector<string> split(string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elems.push_back(item);
        }
    }
    return elems;
}

vector<ll> divisor(ll n)
{
    vector<ll> ret;
    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ret.push_back(i);
            if (i * i != n)
                ret.push_back(n / i);
        }
    }
    sort(begin(ret), end(ret));
    return (ret);
}
template <typename T>
vector<T> smallest_prime_factors(T n)
{
    vector<T> spf(n + 1);
    for (int i = 0; i <= n; i++)
        spf[i] = i;

    for (T i = 2; i * i <= n; i++)
    {
        // 素数だったら
        if (spf[i] == i)
        {
            for (T j = i * i; j <= n; j += i)
            {

                // iを持つ整数かつまだ素数が決まっていないなら
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }

    return spf;
}

template <typename T>
set<T> factolization(T x, vector<T> &spf)
{
    set<T> ret;
    while (x != 1)
    {
        ret.insert(spf[x]);
        x /= spf[x];
    }
    //sort(ret.begin(), ret.end());
    return ret;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> v;

    rep(i, n)
    {
        ll tmp;
        cin >> tmp;
        v.push_back(make_pair(tmp, 0));
    }

    rep(i, m)
    {
        ll tmp;
        cin >> tmp;
        v.push_back(make_pair(tmp, 1));
    }

    sort(ALL(v));

    ll ans = INF;
    rep(i, n + m - 1)
    {
        if (v[i].second != v[i + 1].second)
        {
            ans = min(ans, abs(v[i].first - v[i + 1].first));
        }
    }

    cout << ans << endl;

    return 0;
}
//cout << std::fixed << std::setprecision(15)
