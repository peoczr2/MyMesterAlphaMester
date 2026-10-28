/*
Megoldás lényege:
Ha az x. napon a pletykát ismerők halmaza S, akkor az (x+1). napon pontosan azok ismerik, akiknek van barátjuk S-ből.
Így az x. napi ismerők azok a diákok, akik a kezdő diákokból pontosan x-1 hosszú sétával elérhetők.
Mivel a barátság kétirányú, egy séta bármelyik csúccsal oda-vissza lépéssel meghosszabbítható, ezért ha egy diák p paritású legrövidebb
sétája d hosszú, akkor minden d-nél nem rövidebb, p-vel azonos paritású napon is ismeri a pletykát (ha van barátja).
A páros és páratlan sétákat ezért külön kezeljük: a (diák, paritás) párokból álló gráfon szélességi bejárással megkapjuk a legrövidebb hosszakat.
A napi létszámokat a hosszak számlálótömbjéből prefixösszeggel adjuk meg. A legrövidebb hossz legfeljebb 2N-1, így 2N+2 napig számolni elég,
utána a sorozat már csak a két paritás szerint változik. Az időigény O(N+M).
*/
/*
Hint 1: || Figyeld meg, hogy az x+1. napi ismerők pontosan azok, akiknek van barátjuk az x. napi ismerők között. Így a kérdés az, hogy melyik diákot érhetjük el a kezdő diákokból pontosan x-1 lépésből álló sétával. ||
Hint 2: || Sétáknál a hossz paritása számít, mert minden él paritást vált. Készíts egy gráfot, amelynek csúcsai (diák, paritás) párok, az élei pedig a barátságokat követik, és a kezdő diákoktól BFS-t futtass. ||
Hint 3: || Ha egy diák legrövidebb p paritású sétája d hosszú, akkor a d-nél nem rövidebb, p-vel azonos paritású hosszú lépésszámokra is elérhető. Ezért egy számlálótömbbel és prefixösszeggel minden napra megkapod a létszámot, és az első maximumot a 2N+2 napig tartó szakaszban keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> start(k);
    for (int i = 0; i < k; ++i) cin >> start[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // dist[p][v]: a kezdő diákoktól v-ig vezető, p paritású séta legrövidebb hossza (-1: nincs ilyen)
    vector<vector<int>> dist(2, vector<int>(n + 1, -1));
    queue<int> q;  // az állapot kódja: 2 * diák + paritás
    int isolated = 0;
    for (int s : start) {
        if (dist[0][s] != -1) continue;
        dist[0][s] = 0;
        if (adj[s].empty())
            ++isolated;  // barát nélküli kezdő diák: csak az első napon ismeri a pletykát
        else
            q.push(2 * s);
    }

    while (!q.empty()) {
        int code = q.front();
        q.pop();
        int v = code / 2, p = code % 2;
        for (int u : adj[v]) {
            if (dist[1 - p][u] == -1) {
                dist[1 - p][u] = dist[p][v] + 1;
                q.push(2 * u + (1 - p));
            }
        }
    }

    // Legrövidebb séta hossza legfeljebb 2N-1, ezért t = 0 .. days lépésszámig számolunk.
    const int days = 2 * n + 2;
    vector<vector<int>> cnt(2, vector<int>(days + 1, 0));
    for (int v = 1; v <= n; ++v) {
        if (adj[v].empty()) continue;
        for (int p = 0; p < 2; ++p)
            if (dist[p][v] != -1) ++cnt[p][dist[p][v]];
    }

    // known[t]: hányan ismerik a pletykát a (t+1). napon
    vector<int> known;
    int run[2] = {0, 0};
    for (int t = 0; t <= days; ++t) {
        run[0] += cnt[0][t];
        run[1] += cnt[1][t];
        known.push_back(run[t % 2] + (t == 0 ? isolated : 0));
    }

    int best = -1, firstDay = 0;
    for (int t = 0; t <= days; ++t) {
        if (known[t] > best) {
            best = known[t];
            firstDay = t + 1;
        }
    }

    cout << best << '\n' << firstDay << '\n';
    for (int i = 0; i < firstDay; ++i)
        cout << known[i] << (i + 1 < firstDay ? ' ' : '\n');
    return 0;
}
