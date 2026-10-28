/*
Megoldás lényege:
Az utak körmentes irányított gráfot alkotnak, ezért a csúcsokat topologikus sorrendben dolgozhatjuk fel. Egy út e élből áll,
és így e-1 állatot néz meg, ezért minden csúcshoz az odavezető lehetséges élszámok halmazát bitsorozatban tároljuk: a csúcsba
érkező élek halmazait egyesítjük, majd az eredményt eggyel eltoljuk (reach[v] = (OR reach[u]) << 1). Az N-be érkező élszámok
közül keressük a K-hoz legközelebbit (L = e-1), egyenlő távolságnál a kisebb L-t választjuk. Az utat a kijárattól visszafelé építjük fel, a bemeneti éleket fordított sorrendben próbálva.
Az időigény O(M * N / 64), a memóriaigény O(N^2 / 8) bájt.
*/
/*
Hint 1: || Egy út e élből áll, és így e-1 állatot néz meg. Ezért az állatok száma helyett az élek számát érdemes nyilvántartani, és minden csúcshoz az odavezető lehetséges élszámokat gyűjteni. ||
Hint 2: || A lehetséges élszámokat bitsorozatban tárold, és a csúcsokat topologikus sorrendben dolgozd fel. Egy csúcs halmaza a bejövő élek halmazainak egyesítéséből adódik, az eredményt pedig eggyel el kell tolni, mert az út egy éllel hosszabb. ||
Hint 3: || Az L-et növekvő d távolságra keresd: először a K-d, majd a K+d értéket ellenőrizd (az alsó közelítés előnyben van), az utat pedig a kijárattól visszafelé építsd fel. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bitset<10001> reach[10001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> out(n + 1), in(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        out[a].push_back(b);
        in[b].push_back(a);
        ++indeg[b];
    }

    // topologikus sorrend (Kahn)
    vector<int> order;
    order.reserve(n);
    queue<int> q;
    for (int v = 1; v <= n; ++v)
        if (indeg[v] == 0)
            q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : out[v])
            if (--indeg[w] == 0)
                q.push(w);
    }

    // reach[v]: az 1-ből v-be vezető utak élszámai; a v-be érkező élek halmazát egyesítjük, majd egyszer eltoljuk
    reach[1][0] = 1;
    for (int v : order) {
        if (v == 1)
            continue;
        bitset<10001> acc;
        for (int u : in[v])
            acc |= reach[u];
        reach[v] = acc << 1;
    }

    // L = e - 1, ahol e az 1 -> N út éleinek száma
    auto feasible = [&](int L) {
        int e = L + 1;
        return L >= 0 && e <= n && reach[n][e];
    };
    int best = -1;
    for (int d = 0; d <= n && best < 0; ++d) {
        if (feasible(k - d))
            best = k - d;
        else if (d > 0 && feasible(k + d))
            best = k + d;
    }

    // visszafelé rekonstrukció: a bemeneti éleket fordított sorrendben próbáljuk
    vector<int> path{n};
    int cur = n;
    for (int r = best + 1; r > 0; --r) {
        int nxt = -1;
        for (int i = (int)in[cur].size() - 1; i >= 0 && nxt < 0; --i)
            if (reach[in[cur][i]][r - 1])
                nxt = in[cur][i];
        path.push_back(nxt);
        cur = nxt;
    }
    reverse(path.begin(), path.end());

    cout << best << "\n";
    for (size_t i = 0; i < path.size(); ++i)
        cout << path[i] << (i + 1 < path.size() ? ' ' : '\n');
    return 0;
}
