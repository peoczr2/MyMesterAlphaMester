/*
Megoldás lényege:
A régi raktár (K) nem lehet átmenő csomópont, ezért a gráfból töröljük, vagyis a rá illeszkedő éleket elhagyjuk. Az így kapott gráf erős összefüggő komponenseit Kosaraju-algoritmussal határozzuk meg, majd a komponenseket egy irányított körmentes gráfba (kondenzált gráfba) zsugorítjuk. Forrásnak nevezzük azt a komponenst, amelybe más komponensből nem vezet él; ezekbe csak új út vezethet. Az új raktár egy forrás-komponens bármely csúcsa lehet, a többi forrásba pedig egy-egy új út kell, így a szükséges és elégséges útszám a forrás-komponensek száma mínusz egy. Az időigény O(N+M), a memóriaigény O(N+M).
*/
/*
Hint 1: || A régi raktárat töröld a gráfból: a K-ra illeszkedő éleken nem lehet áthaladni, így a többi csúcs elérhetőségét csak a maradék gráfban kell vizsgálni. ||
Hint 2: || Az erős összefüggő komponensekre zsugorított gráfban azok a komponensek, amelyekbe nem vezet él másik komponensből, csak új úton érhetők el; számold meg őket. ||
Hint 3: || Válassz az egyik ilyen forrás-komponensből egy csúcsot új raktárnak, és a többi forrás-komponensbe húzz egy új utat innen. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ilen = 0, ipos = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static inline int readInt() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = gc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

int main() {
    int n = readInt();
    int m = readInt();
    int ctr = readInt();

    // A régi raktárra illeszkedő éleket elhagyjuk.
    vector<int> eu, ev;
    eu.reserve(m);
    ev.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u = readInt();
        int v = readInt();
        if (u < 1 || u > n || v < 1 || v > n) continue;
        if (u == ctr || v == ctr) continue;
        eu.push_back(u);
        ev.push_back(v);
    }
    int E = eu.size();

    // Szomszédsági lista (CSR), előre és fordított irányban.
    vector<int> fst(n + 2, 0), rst(n + 2, 0);
    for (int i = 0; i < E; ++i) {
        fst[eu[i] + 1]++;
        rst[ev[i] + 1]++;
    }
    for (int i = 1; i <= n + 1; ++i) {
        fst[i] += fst[i - 1];
        rst[i] += rst[i - 1];
    }
    vector<int> fadj(E), radj(E);
    {
        vector<int> fp(fst), rp(rst);
        for (int i = 0; i < E; ++i) {
            fadj[fp[eu[i]]++] = ev[i];
            radj[rp[ev[i]]++] = eu[i];
        }
    }

    // 1. Kosaraju: kifutási sorrend (a K csúcsot kihagyva).
    vector<char> vis(n + 1, 0);
    vis[ctr] = 1;
    vector<int> order;
    order.reserve(n);
    vector<int> it(n + 1);
    for (int v = 1; v <= n; ++v) it[v] = fst[v];
    vector<int> st;
    for (int s = 1; s <= n; ++s) {
        if (vis[s]) continue;
        vis[s] = 1;
        st.push_back(s);
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < fst[v + 1]) {
                int w = fadj[it[v]++];
                if (!vis[w]) {
                    vis[w] = 1;
                    st.push_back(w);
                }
            } else {
                order.push_back(v);
                st.pop_back();
            }
        }
    }

    // 2. Komponensek a fordított gráfon, a kifutási sorrend fordítottjában.
    vector<int> comp(n + 1, -1);
    int C = 0;
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int s = order[i];
        if (comp[s] != -1) continue;
        comp[s] = C;
        st.push_back(s);
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int k = rst[v]; k < rst[v + 1]; ++k) {
                int w = radj[k];
                if (comp[w] == -1) {
                    comp[w] = C;
                    st.push_back(w);
                }
            }
        }
        ++C;
    }

    // Van-e bejövő él más komponensből.
    vector<char> hasIn(C, 0);
    for (int i = 0; i < E; ++i) {
        if (comp[eu[i]] != comp[ev[i]]) hasIn[comp[ev[i]]] = 1;
    }

    // Forrás-komponensek; minden komponensből a legkisebb csúcs a képviselő.
    vector<int> repOf(C, 0);
    for (int v = 1; v <= n; ++v) {
        if (v == ctr) continue;
        if (repOf[comp[v]] == 0) repOf[comp[v]] = v;
    }
    vector<int> sources;
    for (int v = 1; v <= n; ++v) {
        if (v == ctr) continue;
        if (repOf[comp[v]] == v && !hasIn[comp[v]]) sources.push_back(v);
    }

    int X = sources[0];
    cout << X << ' ' << (int)sources.size() - 1 << '\n';
    for (size_t k = 1; k < sources.size(); ++k) {
        cout << X << ' ' << sources[k] << '\n';
    }
    return 0;
}
