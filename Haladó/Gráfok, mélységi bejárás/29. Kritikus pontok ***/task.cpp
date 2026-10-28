/*
Megoldás lényege:
Egy v csúcs (A-n és B-n kívül) pontosan akkor kritikus, ha minden A–B úton rajta van. Az A-ból indított mélységi bejárási fában az A–B út csúcsai mind ilyenek lehetnek, ezért csak ezeket vizsgáljuk. Minden csúcsnak kiszámítjuk a sorszámát (disc) és a low értékét, ami a részfájából visszavezető élek legkisebb sorszáma (a szülő-élt kihagyva). Ha az A–B út v csúcsa alatti gyermeke c, akkor v kritikus pontosan akkor, ha low[c] ≥ disc[v], mert ekkor c részfája nem tud v fölé jutni. A B-ből a szülőkön át felfelé haladva ezt minden közbülső csúcsra ellenőrizzük. Az időigény O(N+M).
*/
/*
Hint 1: || Keress egy A–B utat, például mélységi bejárással A-ból. Minden kritikus csúcs rajta van ezen az úton, így elég ennek a közbülső csúcsait vizsgálni. ||
Hint 2: || A mélységi bejárási fában a v csúcs akkor választja el A-t B-től, ha a B-t tartalmazó gyermeke c részfájából nincs visszaél v fölé. Ezt a low értékkel mérd: low[c] ≥ disc[v]. ||
Hint 3: || Lépések: 1) mélységi bejárás A-ból, disc és low számítása (a szülő-élt kihagyva); 2) B-ből felfelé a szülőkön haladva, minden közbülső v-re a v alatti gyermekkel (az úton lévővel) ellenőrizd a feltételt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, A, B;
vector<vector<int>> g;
vector<int> disc, low, par;
int timer_ = 0;

void dfs(int v, int p) {
    disc[v] = low[v] = ++timer_;
    par[v] = p;
    for (int w : g[v]) {
        if (w == p) continue;
        if (disc[w]) {
            low[v] = min(low[v], disc[w]);
        } else {
            dfs(w, v);
            low[v] = min(low[v], low[w]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> A >> B;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    disc.assign(n + 1, 0);
    low.assign(n + 1, 0);
    par.assign(n + 1, 0);
    dfs(A, 0);

    vector<int> ans;
    int c = B;             // a B-t tartalmazó gyermek (az úton)
    int v = par[B];
    while (v != A && v != 0) {
        if (low[c] >= disc[v]) ans.push_back(v);
        c = v;
        v = par[v];
    }

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
