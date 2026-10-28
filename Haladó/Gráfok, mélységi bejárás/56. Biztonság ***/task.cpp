/*
Megoldás lényege:
Egy kereszteződésen pontosan akkor haladhat át egyszer a vendég A-ból B-be, ha a csúcs rajta van egy olyan körben, amelyen az A-B él is rajta van: a körből az A-B élt elhagyva egy A-ból B-be vezető egyszerű út adódik, és fordítva. Ezért az A és B közé egy virtuális élt húzunk, és a gráf kétszeresen összefüggő komponensei (blokkjai) közül azt keressük, amelyben ez az él van. A blokkok élveremmel, Tarjan-féle mélységi bejárással találhatók meg O(N + M) időben. A blokk csúcsai között az A és B csúcsot nem írjuk ki, a többi csúcs a feladat megoldása. A kiírt szám a csúcsok száma, a második sorban a csúcsok bármilyen sorrendben lehetnek.
*/
/*
Hint 1: || Ha a csúcs egy A-ból B-be vezető egyszerű úton van, akkor az út és egy A-B él együtt kört alkot. Ezért az A és B közé képzelt virtuális éllel dolgozz: az a kör, amely ezen az élen megy át, adja a keresett csúcsokat. ||
Hint 2: || A kétszeresen összefüggő komponensek keresésénél a mélységi bejárás élvermet használ: amikor egy gyerekről a lowpont miatt visszalépünk és low[gyerek] ≥ tin[szülő], a veremből kivett élek egy blokkot adnak. Ha ez a blokk a virtuális élt tartalmazza, megvan a válasz. ||
Hint 3: || A blokk csúcsait a kivett élek két végpontjából gyűjtsd össze, jelöld meg őket egy tömbben, és az A és B csúcsot hagyd ki a kiírásból. Az élek számlálása párhuzamos élek (például az A-B él is szerepelhet az inputban) miatt az élsorszámon történjen. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors beolvasás (fread): M = 5·10^5 élnél a cin lassú.
static char ibuf[1 << 16];
static size_t ilen = 0, ipos = 0;

inline int readChar() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline void readInt(int &x) {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
}

int main() {
    int n, m, a, b;
    readInt(n);
    readInt(m);
    readInt(a);
    readInt(b);
    // Élek: 0..m-1 a bemenetiek, m a virtuális A-B él.
    int E = m + 1;
    vector<int> eu(E), ev(E);
    for (int e = 0; e < m; ++e) {
        readInt(eu[e]);
        readInt(ev[e]);
    }
    eu[m] = a;
    ev[m] = b;

    vector<int> st(n + 2, 0);
    for (int e = 0; e < E; ++e) {
        ++st[eu[e] + 1];
        ++st[ev[e] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) st[v] += st[v - 1];
    vector<int> to(2 * E), eid(2 * E);
    {
        vector<int> pos(st.begin(), st.end());
        for (int e = 0; e < E; ++e) {
            int p = pos[eu[e]]++;
            to[p] = ev[e];
            eid[p] = e;
            p = pos[ev[e]]++;
            to[p] = eu[e];
            eid[p] = e;
        }
    }

    // Tarjan-féle blokkkeresés élveremmel, A-ból indulva (iteratív).
    vector<int> tin(n + 1, -1), low(n + 1, 0), pe(n + 1, -1), it(n + 1, 0);
    vector<int> estack;
    vector<int> answer;  // a virtuális élt tartalmazó blokk csúcsai
    vector<char> mark(n + 1, 0);
    bool found = false;
    {
        vector<int> cs;
        int timer = 0;
        tin[a] = low[a] = timer++;
        it[a] = st[a];
        cs.push_back(a);
        while (!cs.empty() && !found) {
            int v = cs.back();
            if (it[v] < st[v + 1]) {
                int w = to[it[v]], e = eid[it[v]];
                ++it[v];
                if (e == pe[v]) continue;
                if (tin[w] == -1) {
                    estack.push_back(e);
                    tin[w] = low[w] = timer++;
                    pe[w] = e;
                    it[w] = st[w];
                    cs.push_back(w);
                } else if (tin[w] < tin[v]) {
                    // visszaél egy ősre
                    estack.push_back(e);
                    low[v] = min(low[v], tin[w]);
                }
            } else {
                cs.pop_back();
                if (!cs.empty()) {
                    int p = cs.back();
                    low[p] = min(low[p], low[v]);
                    if (low[v] >= tin[p]) {
                        // a p-ből induló blokk: a verem a pe[v] élig
                        vector<int> block;
                        while (true) {
                            int x = estack.back();
                            estack.pop_back();
                            block.push_back(x);
                            if (x == pe[v]) break;
                        }
                        bool hasVirtual = false;
                        for (int x : block)
                            if (x == m) hasVirtual = true;
                        if (hasVirtual) {
                            for (int x : block) {
                                mark[eu[x]] = 1;
                                mark[ev[x]] = 1;
                            }
                            found = true;
                        }
                    }
                }
            }
        }
    }

    // A két végpont (A és B) kimarad a kiírásból.
    mark[a] = 0;
    mark[b] = 0;
    for (int v = 1; v <= n; ++v)
        if (mark[v]) answer.push_back(v);

    string out;
    out.reserve(answer.size() * 8 + 32);
    out += to_string(answer.size());
    out += '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i) out += ' ';
        out += to_string(answer[i]);
    }
    out += '\n';
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
