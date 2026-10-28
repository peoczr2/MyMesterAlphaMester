/*
Megoldás lényege:
A K látványos feladat sorrendje rögzített, ezért a sorrend K darab blokkra esik: minden blokk
nem látványos feladatokból áll, és az adott látványos feladattal végződik. A várakozási idők
különbsége legfeljebb 1 lehet, így minden blokk hossza q = N / K vagy q + 1 (egész osztás),
és pontosan r = N mod K blokk hosszú q + 1. Minden nem látványos feladatnak van egy
megengedett blokk-intervalluma: a legkorábbi blokk az utolsó előtte kötelező látványos feladat
utáni blokk, a legkésőbbi az első rá épülő látványos feladat blokkja. A határidők miatt
szükséges "plusz" feladatok prefixösszegeit (a visszafelé számolással a lehető legkésőbbre
tolva) egyértelműen meghatározzuk, majd blokkonként a legkorábbi határidejű elérhető
feladatokat választjuk egy prioritásos sorral. Végül a kapott sorrendet ellenőrizzük.
Időigény O(N log N) tesztesetenként.
*/
/*
Hint 1: || Az egymást követő látványos feladatok között eltelt idők különbsége legfeljebb 1 lehet, ezért a sorrend K darab blokkra bontható, ahol minden blokk egy látványos feladattal végződik, és a blokkok hossza csak q = N / K vagy q + 1 lehet. ||
Hint 2: || Minden nem látványos feladathoz határozd meg, melyik blokkban kezdhet (az utolsó előtte kötelező látványos feladat utáni blokk) és melyikben kell befejeznie (az első rá épülő látványos feladat blokkja). Ezeket a függőségi gráf topologikus sorrendjében, illetve fordítva terjeszd. ||
Hint 3: || Egy blokkban hány „plusz” feladat legyen, azt a határidőkből kapott prefixösszegek adják; ezeket visszafelé haladva a lehető legkésőbbre tolva számold ki. Utána blokkonként prioritásos sorral válaszd ki a legkorábbi határidejű elérhető feladatokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string out;
    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<vector<int>> pre(N + 1), succ(N + 1);
        for (int i = 1; i <= N; i++) {
            int s;
            cin >> s;
            pre[i].resize(s);
            for (int k = 0; k < s; k++) {
                cin >> pre[i][k];
                succ[pre[i][k]].push_back(i);
            }
        }
        vector<int> vis(K + 1), vidx(N + 1, 0);
        for (int j = 1; j <= K; j++) {
            cin >> vis[j];
            vidx[vis[j]] = j;
        }

        // topologikus sorrend (Kahn)
        vector<int> indeg(N + 1, 0), topo, tpos(N + 1, 0);
        topo.reserve(N);
        for (int i = 1; i <= N; i++) indeg[i] = (int)pre[i].size();
        for (int i = 1; i <= N; i++)
            if (indeg[i] == 0) topo.push_back(i);
        for (size_t h = 0; h < topo.size(); h++) {
            int x = topo[h];
            for (int y : succ[x])
                if (--indeg[y] == 0) topo.push_back(y);
        }
        bool ok = ((int)topo.size() == N);
        for (int i = 0; ok && i < N; i++) tpos[topo[i]] = i;

        vector<int> lo(N + 1, 1), hi(N + 1, K);
        if (ok) {
            for (int x : topo) {
                int best = 1;
                for (int p : pre[x]) {
                    int cand = vidx[p] ? vidx[p] + 1 : lo[p];
                    best = max(best, cand);
                }
                lo[x] = best;
            }
            for (int h = N - 1; h >= 0; h--) {
                int x = topo[h];
                int best = K;
                for (int y : succ[x]) {
                    int cand = vidx[y] ? vidx[y] : hi[y];
                    best = min(best, cand);
                }
                hi[x] = best;
            }
            for (int x = 1; x <= N && ok; x++) {
                if (vidx[x]) {
                    if (lo[x] > vidx[x] || hi[x] < vidx[x]) ok = false;
                } else if (lo[x] > hi[x]) {
                    ok = false;
                }
            }
        }

        const long long q = ok ? N / K : 0;
        const long long r = ok ? N % K : 0;

        // P[j]: a j-edik blokkig összesen hány blokk kapott +1 feladatot
        vector<long long> P(K + 1, 0), Lp(K + 1, 0);
        if (ok) {
            vector<long long> cntHi(K + 2, 0);
            long long totalNv = 0;
            for (int x = 1; x <= N; x++)
                if (!vidx[x]) {
                    cntHi[hi[x]]++;
                    totalNv++;
                }
            long long D = 0;
            for (int j = 1; j <= K; j++) {
                D += cntHi[j];
                Lp[j] = max(0LL, D - (long long)j * (q - 1));
                Lp[j] = max(Lp[j], Lp[j - 1]);
            }
            if (Lp[K] > r) ok = false;
            P[K] = r;
            for (int j = K - 1; ok && j >= 0; j--) {
                P[j] = max(P[j + 1] - 1, Lp[j]);
                if (P[j] > P[j + 1]) ok = false;
            }
            if (ok && P[0] != 0) ok = false;
        }

        vector<int> order;
        if (ok) {
            vector<vector<int>> rel(K + 2);
            for (int x = 1; x <= N; x++)
                if (!vidx[x]) rel[lo[x]].push_back(x);

            // (határidő, topologikus index, csúcs) szerinti min-kupac
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> heap;
            order.reserve(N);
            for (int j = 1; ok && j <= K; j++) {
                for (int x : rel[j]) heap.push({hi[x], tpos[x], x});
                long long cap = q - 1 + (P[j] - P[j - 1]);
                if ((long long)heap.size() < cap) {
                    ok = false;
                    break;
                }
                vector<int> chosen;
                chosen.reserve(cap);
                for (long long c = 0; c < cap; c++) {
                    chosen.push_back(get<2>(heap.top()));
                    heap.pop();
                }
                sort(chosen.begin(), chosen.end(),
                     [&](int a, int b) { return tpos[a] < tpos[b]; });
                for (int x : chosen) order.push_back(x);
                order.push_back(vis[j]);
            }
            if (ok && !heap.empty()) ok = false;
        }

        // ellenőrzés: sorrend, függőségek, látványos sorrend, várakozási idők
        if (ok) {
            if ((int)order.size() != N || order.back() != vis[K]) ok = false;
        }
        if (ok) {
            vector<int> pos(N + 1, 0);
            for (int i = 0; i < N; i++) pos[order[i]] = i + 1;
            for (int x = 1; x <= N && ok; x++)
                for (int p : pre[x])
                    if (pos[p] >= pos[x]) {
                        ok = false;
                        break;
                    }
            for (int j = 2; ok && j <= K; j++)
                if (pos[vis[j - 1]] >= pos[vis[j]]) ok = false;
            if (ok) {
                int wmin = INT_MAX, wmax = INT_MIN;
                for (int j = 1; j <= K; j++) {
                    int w = pos[vis[j]] - (j == 1 ? 0 : pos[vis[j - 1]]);
                    wmin = min(wmin, w);
                    wmax = max(wmax, w);
                }
                if (wmax - wmin > 1) ok = false;
            }
        }

        if (!ok) {
            out += "-1\n";
        } else {
            for (int i = 0; i < N; i++) {
                if (i) out += ' ';
                out += to_string(order[i]);
            }
            out += '\n';
        }
    }
    cout << out;
    return 0;
}
