/*
Megoldás lényege:
Egy versenyző az x. napon pontosan akkor ismeri a pletykát, ha a kezdő diákokból x−1 hosszú séta vezet hozzá. Egy séta paritása és hossza kétrétegű gráfban kezelhető: (csúcs, paritás) állapotokon BFS-sel minden csúcsra megkapjuk a legrövidebb páros és a legrövidebb páratlan hosszú sétát. Ha egy nem izolált csúcsba van p hosszú séta, akkor oda-vissza lépésekkel p+2, p+4, … hosszú is van, így az x. napon ismerők száma azon nem izolált csúcsok száma, amelyekhez az x−1 paritású legrövidebb séta legfeljebb x−1 hosszú. Az izolált kezdőcsúcsok csak az első napon ismerik a pletykát. A BFS-távolságok 2N-nél kisebbek, ezért 2N+2 nap után a sorozat két értéket vált periodikusan, így a maximum ezen belül van. Az időigény O(N+M).
*/
/*
Hint 1: || Egy versenyző az x. napon akkor és csak akkor ismeri a pletykát, ha az első naptól számítva x−1 hosszú séta vezet hozzá a kezdő diákokból. Gondold át, mit jelent ez a barátsági gráfban. ||
Hint 2: || Ha egy nem izolált csúcsba van p hosszú séta, akkor oda-vissza lépéssel p+2, p+4, … hosszú séta is van. Elég tehát minden csúcsra a legrövidebb páros és a legrövidebb páratlan hosszú sétát ismerni: az x. napon ismerők száma ezekből számolható. ||
Hint 3: || A legrövidebb páros és páratlan sétákat kétrétegű gráfban keresd: az állapot (csúcs, paritás), a kezdő diákok (paritás 0) állapotából indulj, és minden élen a paritás vált. Ezt szélességi bejárással (BFS) számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> start(k);
    for (int &e : start) cin >> e;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // BFS a (csúcs, paritás) állapotokon; az állapot indexe 2*v + p
    vector<int> dist(2 * (n + 1), -1);
    queue<int> q;
    for (int e : start) {
        if (dist[2 * e] == -1) {
            dist[2 * e] = 0;
            q.push(2 * e);
        }
    }
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        int v = s / 2, p = s % 2;
        for (int w : adj[v]) {
            int t = 2 * w + (1 - p);
            if (dist[t] == -1) {
                dist[t] = dist[s] + 1;
                q.push(t);
            }
        }
    }

    // az izolált kezdőcsúcsok csak az első napon ismerik a pletykát
    long long isolatedStart = 0;
    vector<char> seen(n + 1, 0);
    for (int e : start) {
        if (!seen[e]) {
            seen[e] = 1;
            if (adj[e].empty()) ++isolatedStart;
        }
    }

    // ennél későbbi napokon a sorozat periodikus, így a maximum ezen belül van
    int T = 2 * n + 2;
    // byDist[p][d]: nem izolált csúcsok száma, amelyekhez p paritású legrövidebb séta d hosszú
    vector<vector<long long>> byDist(2, vector<long long>(T + 1, 0));
    for (int v = 1; v <= n; ++v) {
        if (adj[v].empty()) continue;
        for (int p = 0; p < 2; ++p) {
            int d = dist[2 * v + p];
            if (d != -1) byDist[p][d]++;
        }
    }

    // t = x - 1: az x. napon ismerők száma
    vector<long long> days;
    days.reserve(T + 1);
    long long cum[2] = {0, 0};
    long long best = -1;
    int bestDay = 0;
    for (int t = 0; t <= T; ++t) {
        cum[0] += byDist[0][t];
        cum[1] += byDist[1][t];
        long long c = cum[t % 2] + (t == 0 ? isolatedStart : 0);
        days.push_back(c);
        if (c > best) {
            best = c;
            bestDay = t + 1;
        }
    }

    cout << best << '\n' << bestDay << '\n';
    for (int i = 0; i < bestDay; ++i)
        cout << days[i] << (i + 1 < bestDay ? ' ' : '\n');
    return 0;
}
