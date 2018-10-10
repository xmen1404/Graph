#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c;++a)
#define fi first
#define se second
#define pb push_back
typedef pair<int, int> ii;
const int N = 1e5 + 10;
const int oo = 2e9;

int n, sum = 0, m;
int dsu[N], h[N];
ii pr[N][30]; // index and max value
vector<ii> tree[N];
struct spm{
    int u, v, c;
}eg[2*N];

bool cmp(const spm x, const spm y)  { return x.c < y.c; }
map<ii, int> teg;

void dfs(int pre, int u)    {
    for(auto v: tree[u]) if(v.fi != pre)    {
        h[v.fi] = h[u] + 1;
        pr[v.fi][0] = ii(u, v.se);
        dfs(u, v.fi);
    }
    return;
}
int findn(int i) { return (dsu[i] == i) ? i : (dsu[i] = findn(dsu[i])); }

void LCA(int u, int v)  {
    ii cur = ii(min(u, v), max(u, v));
    int maxn = -oo;
    if(h[u] < h[v]) swap(u, v);
    for(int i = 17; i >= 0; --i)    if(pr[u][i].fi != -1 && h[ pr[u][i].fi ] >= h[v]){
        maxn = max(maxn, pr[u][i].se);
        u = pr[u][i].fi;
    }
    //cout << u << ' ' << v << ' ' << maxn << '\n';
    for(int i = 17; i >= 0; --i )   if(pr[u][i].fi != -1 && pr[v][i].fi != -1 && pr[u][i].fi != pr[v][i].fi){
        maxn = max(maxn, pr[u][i].se);
        maxn = max(maxn, pr[v][i].se);
        u = pr[u][i].fi; v = pr[v][i].fi;
    }
    if(u != v) maxn = max(maxn, max(pr[u][0].se, pr[v][0].se));
    cout << sum - maxn + teg[cur] << '\n';
}

signed main()   {
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    FOR(i, 1, n) dsu[i] = i;
    FOR(i, 1, m)    {
        int u, v, c; cin >> u >> v >> c;
        teg[ii(min(u, v), max(u, v))] = c;
        eg[i] = {u, v, c};
    }
    sort(eg + 1, eg + m +1, cmp);
    FOR(i, 1, m)    {
        int u = eg[i].u, v = eg[i].v, c = eg[i].c;
        if(findn(u) != findn(v))    {
            sum += c;
            dsu[findn(u)] = findn(v);
            tree[u].pb(ii(v, c));
            tree[v].pb(ii(u, c));
            //cout << u << ' ' << v << '\n';
        }
    }
    FOR(i, 1, n) FOR(j, 0, 17) pr[i][j] = ii(-1, -oo);
    dfs(1, 1);
    for(int t = 1; t <= 17; ++t)    {
        FOR(u, 1, n) if(pr[u][t - 1].fi != -1) {
            pr[u][t].fi = pr[ pr[u][t - 1].fi ][t - 1].fi;
            pr[u][t].se = max(pr[u][t - 1].se, pr[ pr[u][t - 1].fi ][t - 1].se);
        }
    }
    //LCA(2, 3);
    //return 0;
    int t; cin >> t;
    while(t --) {
        int u, v; cin >> u >> v;
        LCA(u, v);
    }
    return 0;
}
