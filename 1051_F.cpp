#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define int long long

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int oo = 1e18;

typedef pair<int, int> ii;

struct edge{
	int u, v, c;
}eg[N];

int n, m, cnt;
int h[N], d[50][N], poweg[N], dist[N], pr[N][20], uni[N];
vector<ii> vi[N], tree[N];
bool spm[N];

int findn(int i)	{ 
	return (uni[i] == i) ? i : (uni[i] = findn(uni[i]));
}

void dfs(int pre, int u)	{
	//cout << u << ' ' << h[u] << '\n';
	for(ii v: tree[u])	if(v.fi != pre)	{
		pr[v.fi][0] = u;
		dist[v.fi] = dist[u] + v.se;
		h[v.fi] = h[u] + 1;
		dfs(u, v.fi);
	}
	// we need to calc the value of dist on the tree
}

void dijka()	{
	FOR(i, 1, n)	if(spm[i])	{
		poweg[++cnt] = i;
		FOR(j, 1, n) d[cnt][j] = oo;
		priority_queue<ii, vector<ii>, greater<ii> > pq;
		d[cnt][i] = 0; pq.push(ii(0, i));
		while(!pq.empty())	{
			int u = pq.top().se, du = pq.top().fi; pq.pop();
			if(d[cnt][u] != du) continue;
			for(ii v: vi[u])	if(d[cnt][v.fi] > du + v.se){
				d[cnt][v.fi] = du + v.se;
				pq.push(ii(du + v.se, v.fi));
			}
		}
	}
}

int LCA(int u, int v)	{
	if(h[u] < h[v]) swap(u, v); //cout << h[u] << ' ' << h[v] << '\n';
	for(int i = 17; i >= 0; --i) if(pr[u][i] != -1 && h[ pr[u][i] ] >= h[v]) 
		u = pr[u][i];
	for(int i = 17; i >= 0; --i)	if(pr[u][i] != -1 && pr[v][i] != -1 && pr[u][i] != pr[v][i])
		u = pr[u][i], v = pr[v][i];
	//cout << u << ' ' << v << '\n';
	if(v != u) return pr[u][0];
	return u;
}

signed main()
{
	//freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(pr, -1, sizeof pr);
    
	cin >> n >> m;
	FOR(i, 1, n) uni[i] = i;
	FOR(i, 1, m) {
		int u, v, c; cin >> u >> v >> c;
		vi[u].pb(ii(v, c));
		vi[v].pb(ii(u, c));
		eg[i] = {u, v, c};
	}
	FOR(i, 1, m)	{
		int u = eg[i].u, v = eg[i].v, c = eg[i].c;
		if(findn(u) != findn(v))	{
			uni[findn(u)] = findn(v);
			//cout << u << ' ' << v << '\n';
			tree[u].pb(ii(v, c));
			tree[v].pb(ii(u, c));
		} else spm[u] = spm[v] = true;
	}
	dfs(1, 1);
	dijka();
	
	FOR(i, 1, 17)	{
		FOR(j, 1, n) if(pr[j][i - 1] != -1) 
			pr[j][i] = pr[ pr[j][i - 1] ][ i - 1 ];
	}
//cout << LCA(3, 1) << '\n'; return 0;
	int t; cin >> t;
	while(t --)	{
		int u, v; cin >> u >> v;
		int uv = LCA(u, v);
		int ans = dist[u] + dist[v] - 2*dist[uv];
		//cout << u << ' ' << v << ' ' << uv << '\n';
		//cout << ans << '\n';
		FOR(i, 1, cnt) ans = min(ans, d[i][u] + d[i][v]);
		cout << ans << '\n';
	}
}
