#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const long double PI = (acos(-1));
const long long MOD = 1000000007;
struct Edge
{
    long long to;
    long long cost;
};
using Graph = vector<vector<Edge>>;
using P = pair<ll, ll>;
const long long INF = 1LL << 60;

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
long long combi(long long n, long long a)
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

template <typename T>
bool next_combination(const T first, const T last, int k)
{
    const T subset = first + k;
    // empty container | k = 0 | k == n
    if (first == last || first == subset || last == subset)
    {
        return false;
    }
    T src = subset;
    while (first != src)
    {
        src--;
        if (*src < *(last - 1))
        {
            T dest = subset;
            while (*src >= *dest)
            {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

void dfs(vector<ll> s, ll mx, ll N, vector<vector<ll>> &arr)
{
    if (s.size() == (size_t)N)
    {
        //cout << s.c_str() << endl;
        arr.push_back(s);
    }
    else
    {
        for (ll c = s.size() > 0 ? 0 : 0; c <= mx; c++)
        {
            s.push_back(c);
            dfs(s, mx, N, arr);
            s.pop_back();
        }
    }

    return;
}

int bfs(int sx, int sy, int gx, int gy, int h, int w, vector<vector<char>> map)
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

    return ans[gy][gx];
}

ll modfactorial(ll a)
{
    if (a == 1)
        return 1;

    return (a % MOD) * (modfactorial(a - 1) % MOD);
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

/* dijkstra(G,s,dis)
    入力：グラフ G, 開始点 s, 距離を格納する dis
    計算量：O(|E|log|V|)
    副作用：dis が書き換えられる
*/
void dijkstra(const Graph &G, int s, vector<ll> &dis, vector<ll> &prev)
{
    int N = G.size();
    dis.resize(N, INF);
    prev.resize(N, -1); // 初期化
    priority_queue<P, vector<P>, greater<P>> pq;
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty())
    {
        P p = pq.top();
        pq.pop();
        int v = p.second;
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

vector<string> split( string &s, char delim)
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

int main()
{
    ll h,w,l;
    cin >> h >> w >> l;

    vector<vector<char>> v;

    for (int i = 0; i<h; i++){
        vector<char> a;
        for (int j = 0; j < w; j++)
        {
            char tmp;
            cin >> tmp;
            a.push_back(tmp);
        }
        v.push_back(a);
    }

    vector<vector<ll>> harr;
    vector<vector<ll>> warr;

    vector<ll> s;
    dfs(s, 1, h, harr);
    dfs(s, 1, w, warr);

    vector<vector<char>> vtmp;

    ll ans = 0;

    for (int j = 0; j < harr.size(); j++)
    {
        vtmp = v;
        for (int a = 0; a < h; a++)
        {
            if (harr[j][a] == 1)
            {
                for (int aa = 0; aa < w; aa++)
                {
                    vtmp[a][aa] = '*';
                }
            }
        }
        vector<vector<char>> vtmp2 = vtmp;
        for (int k = 0; k < warr.size(); k++)
        {
            for (int a = 0; a < w; a++)
            {
                if (warr[k][a] == 1)
                {
                    for (int aa = 0; aa < h; aa++)
                    {
                        vtmp[aa][a] = '*';
                    }
                }
            }

            ll cnt = 0;
            for (int x = 0; x < h; x++)
            {
                for (int y = 0; y < w; y++)
                {
                    if (vtmp[x][y] == '#')
                        cnt++;
                }
            }

            vtmp = vtmp2;
            if (cnt == l)
                ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
//cout << std::fixed << std::setprecision(15)