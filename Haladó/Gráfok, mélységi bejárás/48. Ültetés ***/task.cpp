/*
Megoldás lényege:
Egy diák akkor ül a kívánt diák mellett, ha az ülésszámuk különbsége 1. Gráfot építünk: minden i diákot összekötünk a kívánt diákjával, S_i-vel. Ha két diák kölcsönösen kéri egymást, ez egyetlen élként szerepel, amely 2 teljesülő kérést ér. Az ültetés egy sor, ezért a teljesülő élek lineáris erdőt (utak uniójá) alkotnak: fokszámuk legfeljebb 2, és nincs köztük kör. A feladat tehát a legnagyobb súlyú ilyen élhalmaz megkeresése. A fákat leveleiktől felfelé dolgozzuk fel (fa-DP: a csúcs 0, 1 vagy 2 gyerekélt használ), a körös komponensekben a kör mentén egy újabb DP-vel legalább egy kört alkotó élt kihagyunk. A kapott utakat egymás után fűzzük a sorba, így megkapjuk az ülésszámokat. Az időigény O(N).
*/
/*
Hint 1: || Két diák akkor ül egymás mellett, ha az ülésszámaik különbsége 1. Ezért rajzolj gráfot: minden diákot kösd össze azzal, akit kér. ||
Hint 2: || A teljesülő kapcsolatok fokszáma legfeljebb 2 lehet, és nem alkothatnak kört, mert a sor egy lineáris elrendezés. Kölcsönös kérésnél az él 2 pontot ér. ||
Hint 3: || Fákon fa-DP: minden csúcsra tárold, hogy 0, 1 vagy 2 gyerekéllel a legjobb. A körös komponensben a kör mentén dinamikus programozással válassz ki olyan élhalmazt, amely nem zárja be teljesen a kört. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long NEG = -(1LL << 50);

struct Adj {
    int to, w, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> s[i];

    // Egyszerű gráf: i és s[i] között él. Kölcsönös kérés egyetlen él, súlya 2.
    vector<vector<Adj>> adj(n + 1);
    vector<pair<int, int>> edges;
    auto addEdge = [&](int a, int b, int w) {
        int id = (int)edges.size();
        edges.push_back({a, b});
        adj[a].push_back({b, w, id});
        adj[b].push_back({a, w, id});
    };
    for (int i = 1; i <= n; i++) {
        int j = s[i];
        if (s[j] == i) {
            if (i < j) addEdge(i, j, 2);
        } else {
            addEdge(i, j, 1);
        }
    }

    // Levelek fokozatos eltávolítása: a fák a gyökerük felé, a körök megmaradnak.
    vector<int> deg(n + 1), par(n + 1, 0), parW(n + 1, 0), parE(n + 1, -1);
    vector<char> removed(n + 1, 0);
    for (int v = 1; v <= n; v++) deg[v] = (int)adj[v].size();
    queue<int> q;
    for (int v = 1; v <= n; v++)
        if (deg[v] == 1) q.push(v);
    vector<int> order;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        removed[v] = 1;
        order.push_back(v);
        for (const Adj &e : adj[v]) {
            if (!removed[e.to]) {
                par[v] = e.to;
                parW[v] = e.w;
                parE[v] = e.id;
                if (--deg[e.to] == 1) q.push(e.to);
                break;
            }
        }
    }

    // A[v][k]: a v részfájának legjobb értéke, ha v-nek pontosan k gyerekéle van.
    vector<array<long long, 3>> A(n + 1);
    for (int v = 1; v <= n; v++) A[v] = {0, NEG, NEG};
    vector<array<char, 3>> dec(n + 1);  // dec[c][k]: a c-p él bekerül-e, ha p állapota után k él van
    vector<int> argNot(n + 1, 0), argYes(n + 1, 0);
    vector<vector<int>> kids(n + 1);

    for (int v : order) {
        int p = par[v];
        if (p == 0) continue;  // fa gyökere
        long long notC = max({A[v][0], A[v][1], A[v][2]});
        argNot[v] = 0;
        for (int k = 1; k < 3; k++)
            if (A[v][k] > A[v][argNot[v]]) argNot[v] = k;
        argYes[v] = (A[v][1] > A[v][0]) ? 1 : 0;
        long long yesC = max(A[v][0], A[v][1]) + parW[v];
        array<long long, 3> old = A[p], nw;
        for (int k = 0; k < 3; k++) {
            long long opt0 = old[k] + notC;
            long long opt1 = (k >= 1) ? old[k - 1] + yesC : NEG;
            if (opt1 > opt0) {
                nw[k] = opt1;
                dec[v][k] = 1;
            } else {
                nw[k] = opt0;
                dec[v][k] = 0;
            }
        }
        A[p] = nw;
        kids[p].push_back(v);
    }

    vector<int> chosen(edges.size(), 0);
    vector<pair<int, int>> stateStack;  // (csúcs, a csúcs gyerekéleinek száma)
    long long total = 0;

    // Fák gyökerei
    for (int v : order) {
        if (par[v] != 0) continue;
        int k = 0;
        for (int t = 1; t < 3; t++)
            if (A[v][t] > A[v][k]) k = t;
        total += A[v][k];
        stateStack.push_back({v, k});
    }

    // Körös komponensek: a kör mentén DP, legalább egy kör-él kimarad.
    vector<char> vis(n + 1, 0);
    for (int start = 1; start <= n; start++) {
        if (removed[start] || vis[start]) continue;
        vector<int> cyc, cw, cid;
        int prevE = -1, cur = start;
        do {
            vis[cur] = 1;
            cyc.push_back(cur);
            const Adj *nx = nullptr;
            for (const Adj &e : adj[cur]) {
                if (!removed[e.to] && e.id != prevE) {
                    nx = &e;
                    break;
                }
            }
            cw.push_back(nx->w);
            cid.push_back(nx->id);
            prevE = nx->id;
            cur = nx->to;
        } while (cur != start);

        int L = (int)cyc.size();
        // tv[t][d]: a t-edik kör-csúcs fabeli legjobb értéke, ha a kör-élekből d van rajta.
        vector<array<long long, 3>> tv(L);
        vector<array<int, 3>> tk(L);
        for (int t = 0; t < L; t++) {
            int v = cyc[t];
            for (int d = 0; d < 3; d++) {
                long long best = NEG;
                int arg = 0;
                for (int k = 0; k <= 2 - d; k++)
                    if (A[v][k] > best) {
                        best = A[v][k];
                        arg = k;
                    }
                tv[t][d] = best;
                tk[t][d] = arg;
            }
        }

        // dp[t][x][z]: x = az t-edik kör-él kiválasztása, z = volt-e kihagyott kör-él az 0..t között.
        auto idx = [](int t, int x, int z) { return ((size_t)t * 2 + x) * 2 + z; };
        vector<long long> val[2];
        vector<pair<int, int>> bp[2];
        long long bestTotal[2] = {NEG, NEG};
        int bestXl[2] = {-1, -1};
        for (int sx = 0; sx < 2; sx++) {
            vector<long long> &V = val[sx];
            vector<pair<int, int>> &B = bp[sx];
            V.assign((size_t)L * 4, NEG);
            B.assign((size_t)L * 4, {0, 0});
            int z0 = (sx == 0) ? 1 : 0;
            V[idx(0, sx, z0)] = (long long)sx * cw[0];
            for (int t = 1; t < L; t++) {
                for (int xp = 0; xp < 2; xp++)
                    for (int zp = 0; zp < 2; zp++) {
                        long long c0 = V[idx(t - 1, xp, zp)];
                        if (c0 == NEG) continue;
                        for (int x = 0; x < 2; x++) {
                            long long nv = c0 + (long long)x * cw[t] + tv[t][xp + x];
                            int nz = zp | (x == 0);
                            size_t id2 = idx(t, x, nz);
                            if (nv > V[id2]) {
                                V[id2] = nv;
                                B[id2] = {xp, zp};
                            }
                        }
                    }
            }
            for (int xl = 0; xl < 2; xl++) {
                long long c0 = V[idx(L - 1, xl, 1)];
                if (c0 == NEG) continue;
                long long tot = c0 + tv[0][xl + sx];
                if (tot > bestTotal[sx]) {
                    bestTotal[sx] = tot;
                    bestXl[sx] = xl;
                }
            }
        }

        int bs = (bestTotal[1] > bestTotal[0]) ? 1 : 0;
        total += bestTotal[bs];
        vector<int> x(L, 0);
        int xc = bestXl[bs], zc = 1;
        for (int t = L - 1; t >= 1; t--) {
            x[t] = xc;
            pair<int, int> pr = bp[bs][idx(t, xc, zc)];
            xc = pr.first;
            zc = pr.second;
        }
        x[0] = xc;

        for (int t = 0; t < L; t++) {
            int d = x[(t - 1 + L) % L] + x[t];
            if (x[t]) chosen[cid[t]] = 1;
            stateStack.push_back({cyc[t], tk[t][d]});
        }
    }

    // Visszafejtés: fentről lefelé, a gyerekélek döntéseit a sorrend fordítottjában követjük.
    while (!stateStack.empty()) {
        auto [v, kv] = stateStack.back();
        stateStack.pop_back();
        int k = kv;
        for (int i = (int)kids[v].size() - 1; i >= 0; i--) {
            int c = kids[v][i];
            int childState;
            if (dec[c][k]) {
                chosen[parE[c]] = 1;
                k -= 1;
                childState = argYes[c];
            } else {
                childState = argNot[c];
            }
            stateStack.push_back({c, childState});
        }
    }

    // A kiválasztott élek lineáris erdőt alkotnak: utakat fűzünk egymás után.
    vector<vector<int>> cadj(n + 1);
    for (size_t id = 0; id < edges.size(); id++) {
        if (!chosen[id]) continue;
        cadj[edges[id].first].push_back(edges[id].second);
        cadj[edges[id].second].push_back(edges[id].first);
    }
    vector<int> seat(n + 1, 0);
    vector<char> used(n + 1, 0);
    int pos = 0;
    auto walk = [&](int start) {
        int cur = start;
        while (cur) {
            used[cur] = 1;
            seat[cur] = ++pos;
            int nx = 0;
            for (int w : cadj[cur])
                if (!used[w]) {
                    nx = w;
                    break;
                }
            cur = nx;
        }
    };
    for (int v = 1; v <= n; v++)
        if (!used[v] && cadj[v].size() <= 1) walk(v);
    for (int v = 1; v <= n; v++)
        if (!used[v]) walk(v);

    int T = 0;
    for (int i = 1; i <= n; i++)
        if (abs(seat[i] - seat[s[i]]) == 1) T++;

    cout << T << '\n';
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << seat[i];
    }
    cout << '\n';
    return 0;
}
