#include<bits/stdc++.h>
using namespace std;

#define fi first
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define se second
#define pb push_back

typedef pair<int, int> ii;
typedef pair<int, ii> pii;
const int mod = 1e9 + 7;
const int oo = 1e9;
const int N = 400;

struct book{
    int v, flow, cap, cost, rev;
} ;

int n, source = 0, sink;
int f[N][N], pr[N], ans[N], dist[N];
bool visit[N], inqueue[N];
vector<int> vi[N];
vector<ii> trace[N][N];
vector<book> vif[2 * N];
ii eg[N], las[2*N];

void addeg(int u, int v, int cap, int cost) {
    book a = {v, 0, cap, cost, vif[v].size()};
    book b = {u, 0, 0, -cost, vif[u].size()};
    vif[u].pb(a); vif[v].pb(b);
}

bool ford() {
    FOR(i, 0, sink + 1) dist[i] = oo, inqueue[i] = false;
    dist[source] = 0;
    queue<int> pq;
    pq.push(source); inqueue[source] = true;

    while(!pq.empty())  {
        int u = pq.front(); pq.pop();
        //cout << u << ' ' << dist[u] << '\n';
        inqueue[u] = false;
        for(int i = 0; i < vif[u].size(); ++i)   {
            auto v = vif[u][i];
            if(dist[v.v] > dist[u] + v.cost && v.cap > v.flow) {
                dist[v.v] = dist[u] + v.cost;
                las[v.v] = ii(u, i);
                if(!inqueue[v.v])   {
                    inqueue[v.v] = true;
                    pq.push(v.v);
                }
            }
        }
    }
    //cout << dist[sink] << '\n';
    return dist[sink] != oo;
}

int spm()   {
    int mflow = oo, cur = sink;
    while(cur != source)    {
        int nex = las[cur].fi, pos = las[cur].se;
        mflow = min(mflow, vif[nex][pos].cap - vif[nex][pos].flow);
        cur = nex;
    }
    cur = sink;
    while(cur != source)    {
        int nex = las[cur].fi, pos = las[cur].se;
        vif[nex][pos].flow += mflow;
        vif[ cur ][ vif[nex][pos].rev ].flow -= mflow;
        cur = nex;
    }
    return mflow;
}

void flow() {
    int mflow = 0;
    while(ford()) {
        mflow += spm();
    }
    return; // :D
}

vector<ii> maxflow( vector<pii> egg )    {
    FOR(i, 0, sink + 10) vif[i].clear();
    for(auto v: egg)    addeg(v.se.fi, v.se.se, 1, v.fi);
    FOR(i, 1, n) addeg(source, i, 1, 0);
    FOR(i, n + 1, 2*n - 1) addeg(i, sink, 1, 0);
    flow();
    vector<ii> res;
    FOR(i, 1, n)    {
        for(auto v: vif[i]) if(v.cap == 1 && v.flow == 1)
            res.pb(ii(i, v.v));
    }
    //cout << res.size() << '\n';
    return res;
}

void solve(int pre, int u)  {
    pr[u] = pre;
    for(int v: vi[u]) if(v != pre)
        solve(u, v);
    vector<pii> tmp;

    if(u == 1)  {
        for(int v: vi[u]) if(v != pre)  {
            for(int i = 1; i < n; ++i)
                tmp.pb({f[v][i], {v, i + n} });
        }

        vector<ii> cur = maxflow(tmp);

        f[1][n + 1] = 0;
        for(ii v: cur) {
            trace[1][n + 1].pb(ii(v.fi, v.se - n));
            //cout << v.fi << ' ' << v.se - n << '\n';
            f[1][n + 1] += f[v.fi][v.se - n];
        }
    } else {
        for(int i = 1; i < n; ++i)  {
            tmp.clear(); //if(u == 2) cout << "sdf\n " << i << '\n';
            for(int v: vi[u]) if(v != pre){
                for(int j = 1; j < n; ++j) if(j != i)   {
                    tmp.pb({f[v][j], {v, j + n}});
                    //if(u == 2) cout << v << ' ' << j + n << ' ' << f[v][j] << '\n';
                }
            }
            if(tmp.size() == 0) {
                f[u][i] = i;
                continue;
            }
            vector<ii> cur = maxflow(tmp);
           // cout << cur.size() << '\n';
            int sum = i;
            for(ii v: cur)  {
                trace[u][i].pb(ii(v.fi, v.se - n));
                sum += f[v.fi][v.se - n];
            }
            f[u][i] = sum;

        }
    }
}

void mask(int u, int col)   {
    ans[u] = col;
    for(auto v: trace[u][col]){
        mask(v.fi, v.se);
    }
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n; sink = 2*n;
    FOR(i, 1, n) FOR(j, 1, n + 1) f[i][j] = oo;
    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        vi[u].pb(v); vi[v].pb(u);
        eg[i] = {u, v};
    }

    solve(1, 1);
    //cout << f[4][2] << '\n';
    mask(1, n + 1);
    cout << f[1][n + 1] << '\n';
    int sum = 0;
    FOR(i, 1, n - 1)    {
        int u = eg[i].fi, v = eg[i].se;
        if(pr[u] == v) swap(u, v);
        sum +=
        cout << ans[v] << ' ';
    }
    return 0;
}
