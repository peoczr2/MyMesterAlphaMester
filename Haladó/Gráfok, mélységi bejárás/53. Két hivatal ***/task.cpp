/*
Megoldás lényege:
Egy település zárt szomszédságában (saját magát is beleértve) kell legyen A és B típusú hivatal. Ez pontosan azt jelenti, hogy minden településnek van ellentétes jelű szomszédja, mert ha a település maga A, akkor B-nek kell lennie a szomszédjai között, és fordítva. Ha van izolált település, akkor nincs megoldás, mert a saját szomszédsága csak egy jelet tartalmazhat. Egyébként egy tetszőleges feszítőerdőt (szélességi bejárással) készítünk: a fa minden éle a szülő és a gyerek között ellentétes paritású szintek közt halad, így a páros szintű csúcsok kapják az A, a páratlan szintűek a B jelet. Minden csúcsnak van ellentétes jelű szomszédja: a nem gyökér csúcsnak a szülője, a gyökérnek a gyereke. Az időigény O(N + M).
*/
/*
Hint 1: || Ha egy településnek nincs szomszédja, akkor a saját szomszédságában csak egyféle hivatal lehet, így nincs megfelelő telepítés. Ezt a foknak a beolvasása után azonnal lehet ellenőrizni. ||
Hint 2: || Egy feszítőfa (például szélességi bejárás) mentén a szülő és a gyerek szintje paritásban különbözik. Ha a páros szintű csúcsok A-t, a páratlanok B-t kapnak, minden fa-élen ellentétes jelek vannak. ||
Hint 3: || A gyökérnek a bejárás során talált gyereke lesz az ellentétes jelű szomszédja, a többi csúcsnak pedig a szülője. Ezért minden település mindkét jelet látja a szomszédságában, és a kimenet azonnal megkapható. ||
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
    int n, m;
    readInt(n);
    readInt(m);
    vector<int> eu(m), ev(m), deg(n + 2, 0);
    for (int e = 0; e < m; ++e) {
        readInt(eu[e]);
        readInt(ev[e]);
        ++deg[eu[e]];
        ++deg[ev[e]];
    }
    for (int v = 1; v <= n; ++v) {
        if (deg[v] == 0) {
            // izolált település: a saját szomszédságában csak egy jelet lehet elhelyezni
            fputs("NEM\n", stdout);
            return 0;
        }
    }

    vector<int> st(n + 2, 0);
    for (int v = 1; v <= n; ++v) st[v + 1] = st[v] + deg[v];
    vector<int> adj(2 * m);
    {
        vector<int> pos(st.begin(), st.end());
        for (int e = 0; e < m; ++e) {
            adj[pos[eu[e]]++] = ev[e];
            adj[pos[ev[e]]++] = eu[e];
        }
    }

    // Szélességi bejárás: a szintek paritása adja a jelet (páros: A, páratlan: B).
    vector<int> depth(n + 1, -1), q;
    q.reserve(n);
    for (int s = 1; s <= n; ++s) {
        if (depth[s] != -1) continue;
        depth[s] = 0;
        q.clear();
        q.push_back(s);
        for (size_t h = 0; h < q.size(); ++h) {
            int v = q[h];
            for (int i = st[v]; i < st[v + 1]; ++i) {
                int w = adj[i];
                if (depth[w] == -1) {
                    depth[w] = depth[v] + 1;
                    q.push_back(w);
                }
            }
        }
    }

    string out = "IGEN\n";
    out.reserve(out.size() + 2 * n + 8);
    for (int v = 1; v <= n; ++v) {
        out += (depth[v] % 2 == 0) ? "A\n" : "B\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
