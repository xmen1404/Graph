// onehit
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define FOR(a, b, c) for(int a= b; a <= c; ++a)
#define se second
#define pb push_back
typedef pair<int, int> ii;

const int N = 1e5 + 10;
const int oo = 1e9;

int n, m;
ii ans[N];
void bad() { cout << "-1"; exit(0); }
struct book {
    int uv, id, ty;
}t[N];

bool cmp(const book x, const book y)    {
    if(x.uv != y.uv) return x.uv < y.uv;
    return x.ty < y.ty;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    FOR(i, 1, m)    cin >> t[i].uv >> t[i].ty, t[i].id = i, t[i].ty = 1 - t[i].ty;
    sort(t + 1, t + m + 1, cmp);
    int cur = 1;
    ii eg = ii(3, 1);
    FOR(i, 1, m)    {
        int uv = t[i].uv, ty = t[i].ty;
        if(ty == 0) {
            // spanning tree
            // spanning :D :D :D :D
            cur ++;
            ans[ t[i].id ] = ii(cur, cur - 1);
        } else {
            if(eg.fi > cur) bad();
            ans[ t[i].id ] = eg;
            eg.se --;
            if(eg.se == 0) eg.fi ++, eg.se = eg.fi - 2;
        }
    }
    FOR(i, 1, m) cout << ans[i].fi << ' ' << ans[i].se << '\n';
}
