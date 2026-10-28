/*
Megoldás lényege:
A bűnöző akkor kerülheti el a v csúcsot, ha van olyan (végtelen vagy zsákutcában véget érő) útja, amely nem érinti v-t. Ez pontosan akkor nem lehetséges, ha v kihagyásával a gráfban nincs kör, és nincs olyan zsákutca (kimenő él nélküli csúcs), amely nem v. Ezért két vagy több zsákutca esetén nincs jó csúcs. Pontosan egy zsákutca d esetén csak d lehet a válasz, és csak akkor, ha d kihagyásával nincs kör. Zsákutca nélkül a jó csúcsok azok, amelyek minden körön rajta vannak; ezeket úgy kapjuk, hogy egy kört keresünk, és csak annak csúcsait ellenőrizzük. A körkeresést és a körmentesség ellenőrzését Kahn-féle topologikus rendezéssel végezzük: a maradék csúcsokon visszafelé lépkedve egy kör adódik. Minden ellenőrzés O(N+M), a jelöltek száma pedig a talált körök metszetével csökken.
*/
/*
Hint 1: || Gondold végig, mi történik, ha egy csúcsot kivesszük a gráfból: ha maradt benne kör, vagy olyan csúcs, ahonnan nincs kifelé vezető út, a bűnöző elkerülheti a kivett csúcsot. ||
Hint 2: || Két zsákutca esetén nincs jó csúcs, pontosan egy zsákutcánál csak az lehet a válasz. Zsákutca nélkül a jó csúcsok mindegyike minden körön rajta van, így elég egy kört keresni, és annak csúcsait ellenőrizni. ||
Hint 3: || Körkereséshez használd a topologikus rendezést (Kahn-algoritmus): a maradék csúcsok mindegyikének van a maradékban bejövő éle, így visszafelé lépkedve egy ismétlődésig eljutsz, és megkapod a kört. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> outAdj, inAdj;

// Kahn-algoritmus a 'removed' csúcs nélküli gráfon (removed = 0: nincs kihagyott csúcs).
// Ha van benne kör, visszaad egy kört csúcsok listájaként, különben üres vektort.
vector<int> findCycle(int removed) {
    vector<int> indeg(N + 1, 0);
    for (int u = 1; u <= N; u++) {
        if (u == removed) continue;
        for (int w : outAdj[u]) {
            if (w != removed) indeg[w]++;
        }
    }

    vector<char> peeled(N + 1, 0);
    vector<int> q;
    for (int u = 1; u <= N; u++) {
        if (u != removed && indeg[u] == 0) q.push_back(u);
    }
    for (size_t i = 0; i < q.size(); i++) {
        int u = q[i];
        peeled[u] = 1;
        for (int w : outAdj[u]) {
            if (w != removed && --indeg[w] == 0) q.push_back(w);
        }
    }

    int start = 0;
    for (int u = 1; u <= N; u++) {
        if (u != removed && !peeled[u]) {
            start = u;
            break;
        }
    }
    if (start == 0) return {};

    // a maradék csúcsokon visszafelé lépkedünk, amíg egy csúcs meg nem ismétlődik
    vector<int> pos(N + 1, -1), seq;
    int u = start;
    while (pos[u] == -1) {
        pos[u] = (int)seq.size();
        seq.push_back(u);
        int nxt = 0;
        for (int w : inAdj[u]) {
            if (w != removed && !peeled[w]) {
                nxt = w;
                break;
            }
        }
        u = nxt;
    }
    return vector<int>(seq.begin() + pos[u], seq.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    outAdj.assign(N + 1, {});
    inAdj.assign(N + 1, {});
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        outAdj[a].push_back(b);
        inAdj[b].push_back(a);
    }

    vector<int> dead;
    for (int u = 1; u <= N; u++) {
        if (outAdj[u].empty()) dead.push_back(u);
    }

    vector<int> ans;
    if (dead.size() == 1) {
        int d = dead[0];
        if (findCycle(d).empty()) ans.push_back(d);
    } else if (dead.empty()) {
        vector<int> cyc = findCycle(0);
        vector<char> inK(N + 1, 0);
        for (int v : cyc) inK[v] = 1;
        for (int v : cyc) {
            if (!inK[v]) continue;
            vector<int> c2 = findCycle(v);
            if (c2.empty()) {
                ans.push_back(v);
            } else {
                // a jó csúcsoknak rajta kell lenni c2-n is, és v maga nem jó
                vector<char> onC2(N + 1, 0);
                for (int x : c2) onC2[x] = 1;
                for (int x = 1; x <= N; x++) {
                    if (!onC2[x]) inK[x] = 0;
                }
                inK[v] = 0;
            }
        }
    }

    if (ans.empty()) {
        cout << 0 << '\n';
        return 0;
    }
    sort(ans.begin(), ans.end());
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    }
    return 0;
}
