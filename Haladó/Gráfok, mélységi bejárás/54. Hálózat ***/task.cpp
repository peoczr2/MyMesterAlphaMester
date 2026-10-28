/*
Megoldás lényege:
A gráfban R-ből minden csúcsba pontosan egy út vezet, és két csúcs között legfeljebb egy út van, ezért a gráf a körök egy láncolata: a bejárás fájának élei és a visszairányú élek által lezárt irányított körök. Egy él akkor "híd", ha nincs benne irányítatlan körben; ezek az élek minden új élet igényelnek, mert csak így lehet a hídláncokat visszazárni. Egy hídláncot (irányított utat a hidakon) egy új él zár vissza a lánc végéből a kezdőpontjába, és a lánc végei pontosan azok a csúcsok, amelyekből nincs kivezető híd. Így a szükséges új élek száma a "híd-levelek" száma, és a mélységi bejárásban a lánc befejezésekor kiírható a zárás. Az időigény O(N + M): két bejárás (Tarjan-féle hídkeresés és R-ből a mélységi bejárás).
*/
/*
Hint 1: || Egy él pontosan akkor nincs irányítatlan körben, ha a Tarjan-féle low-érték alapján hídnak bizonyul. Az irányítatlan változatban a többszörös élekre (oda-vissza él) is figyelni kell, ezért élsorszámot tárolj. ||
Hint 2: || Hídélek mentén a csúcsok befolyásolják, hogy egy lánc melyik csúcsnál kezdődik: ha a belépő él híd, és ez a csúcs első kivezető hídja, a lánc folytatódik, minden más kivezető híd új láncot kezd a csúcsból. ||
Hint 3: || Az új él mindig a lánc végéből (olyan csúcsból, amelyből nincs kivezető híd) a lánc kezdőpontjába mutat. Ha R-ből mélységi bejárást futtatsz a kimenő élek bemeneti sorrendjében, és a befejezéskor írod ki a párokat, a minta sorrendjét is megkapod. ||
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
    int n, m, r;
    readInt(n);
    readInt(m);
    readInt(r);
    vector<int> eu(m), ev(m);
    vector<int> outStart(n + 2, 0), uStart(n + 2, 0);
    for (int e = 0; e < m; ++e) {
        readInt(eu[e]);
        readInt(ev[e]);
        ++outStart[eu[e] + 1];
        ++uStart[eu[e] + 1];
        ++uStart[ev[e] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) {
        outStart[v] += outStart[v - 1];
        uStart[v] += uStart[v - 1];
    }
    // Irányított kimenő élek a bemeneti sorrendben.
    vector<int> outTo(m), outEid(m);
    {
        vector<int> pos(outStart.begin(), outStart.end());
        for (int e = 0; e < m; ++e) {
            int p = pos[eu[e]]++;
            outTo[p] = ev[e];
            outEid[p] = e;
        }
    }
    // Irányítatlan szomszédsági lista a hídkereséshez (élsorszámmal).
    vector<int> uTo(2 * m), uEid(2 * m);
    {
        vector<int> pos(uStart.begin(), uStart.end());
        for (int e = 0; e < m; ++e) {
            int p = pos[eu[e]]++;
            uTo[p] = ev[e];
            uEid[p] = e;
            p = pos[ev[e]]++;
            uTo[p] = eu[e];
            uEid[p] = e;
        }
    }

    // Tarjan-féle hídkeresés (iteratív), R-ből indulva.
    vector<int> tin(n + 1, -1), low(n + 1, 0), pe(n + 1, -1), it(n + 1, 0);
    vector<char> isBridge(m, 0);
    {
        vector<int> st;
        int timer = 0;
        tin[r] = low[r] = timer++;
        it[r] = uStart[r];
        st.push_back(r);
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < uStart[v + 1]) {
                int to = uTo[it[v]], e = uEid[it[v]];
                ++it[v];
                if (e == pe[v]) continue;
                if (tin[to] == -1) {
                    tin[to] = low[to] = timer++;
                    pe[to] = e;
                    it[to] = uStart[to];
                    st.push_back(to);
                } else {
                    low[v] = min(low[v], tin[to]);
                }
            } else {
                st.pop_back();
                if (!st.empty()) {
                    int p = st.back();
                    low[p] = min(low[p], low[v]);
                    if (low[v] > tin[p]) isBridge[pe[v]] = 1;
                }
            }
        }
    }

    // Híd-fokszámok: hány hídél lép ki / lép be a csúcsba.
    vector<int> inB(n + 1, 0), outB(n + 1, 0);
    for (int e = 0; e < m; ++e) {
        if (isBridge[e]) {
            ++outB[eu[e]];
            ++inB[ev[e]];
        }
    }

    // R-ből mélységi bejárás a kimenő élek sorrendjében.
    // start[v]: annak a hídláncnak a kezdőpontja, amely v-be érkezik (ha v-be híd vezet).
    vector<int> start(n + 1, 0);
    vector<char> visited(n + 1, 0), contUsed(n + 1, 0);
    vector<int> od(n + 1, 0);  // kimenő élek iterátora
    vector<pair<int, int>> newEdges;
    {
        vector<int> st;
        visited[r] = 1;
        od[r] = outStart[r];
        st.push_back(r);
        while (!st.empty()) {
            int v = st.back();
            if (od[v] < outStart[v + 1]) {
                int c = outTo[od[v]], e = outEid[od[v]];
                ++od[v];
                if (visited[c]) continue;
                visited[c] = 1;
                if (isBridge[e]) {
                    if (inB[v] == 1 && !contUsed[v]) {
                        start[c] = start[v];
                        contUsed[v] = 1;
                    } else {
                        start[c] = v;
                    }
                }
                od[c] = outStart[c];
                st.push_back(c);
            } else {
                st.pop_back();
                // Hídlánc vége: a csúcsba híd vezet, de onnan nem indul híd.
                if (inB[v] == 1 && outB[v] == 0) newEdges.push_back({v, start[v]});
            }
        }
    }

    string out;
    out.reserve(newEdges.size() * 12 + 16);
    out += to_string(newEdges.size());
    out += '\n';
    for (auto &pr : newEdges) {
        out += to_string(pr.first);
        out += ' ';
        out += to_string(pr.second);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
