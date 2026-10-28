/*
Megoldás lényege:
Két csúcshalmazt számolunk ki P-ből indulva. Az első az élek irányában bejárt csúcsok halmaza: ezekbe van út P-ből. A második az élek megfordításával bejárt csúcsok halmaza: ezekből van út P-be. A keresett q pontok pontosan azok, amelyek az elsőben benne vannak, de a másodikban nincsenek, vagyis P-ből van út q-ba, q-ból viszont nincs út P-be. Mindkét bejárás mélységi keresés O(N+M) időben; mivel M akár 10^6 lehet, a bemenetet gyorsan, blokkonként olvassuk be. A kimenet második sorában a pontok sorrendje tetszőleges; itt növekvő sorrendben írjuk ki őket.
*/
/*
Hint 1: || A P-ből elérhető csúcsokat az élek irányában, a P-be vezető utakat pedig az élek megfordításával kapod meg; mindkettő egy-egy bejárás P-ből indítva. ||
Hint 2: || A válasz a P-ből elérhető csúcsok közül azok, amelyeket a megfordított bejárás nem ér el. Az 10^6 él miatt a bemenetet ne cin-nel, hanem nagy blokkokban olvasd, az élek szomszédsági listáit pedig egy tömbbe tömörítve tárold. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
size_t ipos = 0, ilen = 0;

inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline int readInt() {
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
    int n = readInt(), m = readInt(), p = readInt();

    vector<int> eu(m), ev(m);
    vector<int> outDeg(n + 2, 0), inDeg(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        eu[i] = readInt();
        ev[i] = readInt();
        ++outDeg[eu[i]];
        ++inDeg[ev[i]];
    }

    // Szomszédsági listák tömörítve: fstart[v]..fstart[v+1]-1 az élek irányában, rstart[v]..rstart[v+1]-1 a megfordítva.
    vector<int> fstart(n + 2, 0), rstart(n + 2, 0);
    for (int v = 1; v <= n; ++v) {
        fstart[v + 1] = fstart[v] + outDeg[v];
        rstart[v + 1] = rstart[v] + inDeg[v];
    }
    vector<int> fadj(m), radj(m);
    vector<int> fpos(fstart), rpos(rstart);
    for (int i = 0; i < m; ++i) {
        fadj[fpos[eu[i]]++] = ev[i];
        radj[rpos[ev[i]]++] = eu[i];
    }
    vector<int>().swap(eu);
    vector<int>().swap(ev);

    auto bfs = [&](const vector<int> &start, const vector<int> &adj) {
        vector<char> seen(n + 1, 0);
        vector<int> st;
        st.reserve(n);
        st.push_back(p);
        seen[p] = 1;
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (int k = start[x]; k < start[x + 1]; ++k) {
                int y = adj[k];
                if (!seen[y]) {
                    seen[y] = 1;
                    st.push_back(y);
                }
            }
        }
        return seen;
    };

    vector<char> fromP = bfs(fstart, fadj); // P-ből elérhető csúcsok
    vector<char> toP = bfs(rstart, radj);   // innen P is elérhető

    vector<int> ans;
    for (int q = 1; q <= n; ++q)
        if (fromP[q] && !toP[q]) ans.push_back(q);

    string out = to_string(ans.size()) + "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
        out += to_string(ans[i]);
        out += (i + 1 < ans.size() ? ' ' : '\n');
    }
    if (ans.empty()) out += "\n";
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
