#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define int long long

const int mod = 1e9 + 7;
const int N = 2e5 + 10;
const int oo = 1e9;

int n, ans, k;
int dp[N];
vector<int> vi[N];

void solve(int pre, int u)  {
    for(int v: vi[u]) if(v != pre)  {
        solve(u, v);
        dp[u] += dp[v];
    }
    ans += min(dp[u], 2*k - dp[u]);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    FOR(i, 1, 2*k) {
        int x; cin >> x;
        dp[x] = 1;
    }
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        vi[u].pb(v); vi[v].pb(u);
    }
    solve(1, 1);
    cout << ans;
}
