#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a= b; a <= c; ++a)
#define pb push_back

const int N = 1e5 + 10;
typedef pair<int, int> ii;
int n, cnt;
int a[N];
bool visit[N];
set<int> yes, no;
ii eg[N];

void bad()  {
    cout << "-1"; exit(0);
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    n = s.length();
    FOR(i, 0, n - 1)    {
        char x = s[i];
        if(x == '0') no.insert(i + 1), no.insert(n - i - 1);
        else yes.insert(i + 1), yes.insert(n - i - 1);
    }
    if(yes.find(n) != yes.end()) bad();

    for(auto it = no.begin(); it != no.end(); ++it) {
        if((*it) == 1 || yes.find(*it) != yes.end()) bad();
    }
    visit[1] = true;
    int cur = 1, ver = 1, nex = 1;
    while(cur < n)  {
        if(no.find(cur) != no.end()) {
            while(nex < n && visit[nex]) nex ++;
            visit[nex] = true;
            eg[++cnt] = ii(ver, nex);
            cur += 1;
        } else {
            while(nex < n && visit[nex]) nex ++;
            cur += 1;
            eg[++cnt] = ii(ver, nex);
            visit[nex] = true;
            ver = nex;
        }
    }
    FOR(i, 1, cnt) cout << eg[i].fi << ' ' << eg[i].se << '\n';
}

