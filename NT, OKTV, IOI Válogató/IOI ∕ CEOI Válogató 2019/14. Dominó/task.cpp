/*
Megoldás lényege:
A dominókat élekként tekintjük a pöttyszámok (1..K) között, így a sor pontosan akkor rakható ki, ha az élek egy összefüggő részben vannak és legfeljebb két csúcs fokszáma páratlan (Euler-út). Egy új (a,b) dominó két csúcs paritását változtatja és a+b pöttyöt ér, így a költség úgy is számolható, hogy minden végpont a saját pöttyszámával szerepel. Ha c komponens van, legalább 2(c-1) végpont-egységre van szükség, és minden komponensnek legalább egy kell; a páratlan csúcsok közül a sor két végpontját kell kihagyni. Legfeljebb két csúcsból álló végpont-halmazt (F) próbálunk: a költség minden F-re O(1) idő alatt kiszámolható, és a jelöltek a legnagyobb páratlan csúcsok, a komponensek legkisebb csúcsai és a legkisebb páros csúcsok közül kerülnek ki. A kiválasztott egységekből a komponenseket mohón kötjük össze (mindig a legkevesebb és a legtöbb egységű csoportot), a maradék egységeket párosítjuk. Az idő tesztenként O(N + K + c log c).
*/
/*
Hint 1: || A dominókat képzeld el élekként a pöttyszámok között. Egy sor pontosan akkor rakható ki, ha az élek egy összefüggő részben vannak, és legfeljebb két csúcs fokszáma páratlan. ||
Hint 2: || Egy új (a,b) dominó két csúcs paritását egyszerre változtatja, és a+b pöttyöt ér. Így a költség csúcsonként számolható: minden végpont annyi pöttyöt ér, amekkora a csúcs száma. Gondold végig, hány új végpontra van szükség az összekötéshez: minden komponensben legalább egy, összesen legalább 2(c-1). ||
Hint 3: || A páratlan csúcsok többségét párosítsd, a sor két végpontját pedig a legnagyobb páratlan csúcsokból érdemes választani. Ha egy komponensben nincs páratlan csúcs, ott az összekötéshez a komponens legkisebb csúcsát kétszer kell használni; a hiányzó egységeket a teljes gráf legkisebb csúcsán vedd. Így elég néhány jelöltpárra kiszámolni a költséget. ||
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
        vector<int> deg(K + 1, 0), par(K + 1);
        vector<char> present(K + 1, 0);
        iota(par.begin(), par.end(), 0);
        auto findr = [&](int x) {
            while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
            return x;
        };
        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            deg[a]++; deg[b]++;
            present[a] = present[b] = 1;
            if (a != b) {
                int ra = findr(a), rb = findr(b);
                if (ra != rb) par[ra] = rb;
            }
        }

        // komponensek (csak a szerepelő pöttyszámok)
        vector<int> cid(K + 1, -1), rootId(K + 1, -1), compMin;
        int c = 0;
        for (int v = 1; v <= K; ++v) {
            if (!present[v]) continue;
            int r = findr(v);
            if (rootId[r] == -1) { rootId[r] = c++; compMin.push_back(v); }
            cid[v] = rootId[r];
        }
        vector<int> compOdd(c, 0), O;
        for (int v = 1; v <= K; ++v)
            if (present[v] && deg[v] % 2 == 1) { O.push_back(v); compOdd[cid[v]]++; }
        int mstar = 0;
        for (int v = 1; v <= K; ++v) if (present[v]) { mstar = v; break; }

        vector<int> Odesc = O;
        sort(Odesc.rbegin(), Odesc.rend());

        vector<int> F;                       // a sor két végpontja (T = O xor F)
        vector<vector<int>> grp(c);          // komponensenkénti egységek (pöttyszámok)

        if (c == 1) {
            if (Odesc.size() >= 2) F = {Odesc[0], Odesc[1]};
        } else {
            long long S0 = 0;
            for (int v : O) S0 += v;
            long long t0 = (long long)O.size();
            long long Z0 = 0, Zcost0 = 0;
            for (int z = 0; z < c; ++z)
                if (compOdd[z] == 0) { Z0++; Zcost0 += 2LL * compMin[z]; }

            // jelöltek
            set<int> cand;
            for (int i = 0; i < (int)Odesc.size() && i < 3; ++i) cand.insert(Odesc[i]);
            vector<int> zm;
            for (int z = 0; z < c; ++z) if (compOdd[z] == 0) zm.push_back(compMin[z]);
            sort(zm.rbegin(), zm.rend());
            for (int i = 0; i < (int)zm.size() && i < 3; ++i) cand.insert(zm[i]);
            int cntEv = 0;
            for (int v = 1; v <= K && cntEv < 3; ++v)
                if (present[v] && deg[v] % 2 == 0 && compOdd[cid[v]] > 0) { cand.insert(v); cntEv++; }

            vector<int> cv(cand.begin(), cand.end());

            // egy F költsége O(1) módon a komponensek változásából
            auto evalF = [&](const vector<int>& FF) -> long long {
                int ids[2];
                int dl[2];
                int nk = 0;
                long long S = S0, t = t0;
                for (int f : FF) {
                    bool inO = deg[f] % 2 == 1;
                    S += inO ? -(long long)f : (long long)f;
                    int d = inO ? -1 : 1;
                    t += d;
                    int z = cid[f];
                    int k2 = -1;
                    for (int i = 0; i < nk; ++i) if (ids[i] == z) k2 = i;
                    if (k2 == -1) { ids[nk] = z; dl[nk] = d; nk++; }
                    else dl[k2] += d;
                }
                long long Zc = Z0, Zcost = Zcost0;
                for (int i = 0; i < nk; ++i) {
                    int z = ids[i];
                    long long before = compOdd[z] == 0 ? 1 : 0;
                    long long after = compOdd[z] + dl[i] == 0 ? 1 : 0;
                    Zc += after - before;
                    Zcost += 2LL * compMin[z] * (after - before);
                }
                long long Pp = (long long)(c - 1) - t / 2 - Zc;
                if (Pp < 0) Pp = 0;
                return S + Zcost + 2LL * mstar * Pp;
            };

            long long best = evalF({});
            for (int a : cv) {
                vector<int> f1 = {a};
                long long e = evalF(f1);
                if (e < best) { best = e; F = f1; }
            }
            for (size_t i = 0; i < cv.size(); ++i)
                for (size_t j = i + 1; j < cv.size(); ++j) {
                    vector<int> f2 = {cv[i], cv[j]};
                    long long e = evalF(f2);
                    if (e < best) { best = e; F = f2; }
                }

            // a kiválasztott F alapján az egységek
            vector<char> isT(K + 1, 0);
            for (int v : O) isT[v] = 1;
            for (int f : F) isT[f] ^= 1;
            long long tt = 0;
            for (int v = 1; v <= K; ++v)
                if (isT[v] && present[v]) { grp[cid[v]].push_back(v); tt++; }
            long long Zc = 0;
            for (int z = 0; z < c; ++z) {
                if (grp[z].empty()) {          // ehhez a komponenshez kell egy pár
                    Zc++;
                    grp[z].push_back(compMin[z]);
                    grp[z].push_back(compMin[z]);
                }
            }
            long long P = (long long)(c - 1) - tt / 2 - Zc;
            if (P < 0) P = 0;
            for (long long i = 0; i < P; ++i) {  // extra párok a legkisebb csúcson
                grp[cid[mstar]].push_back(mstar);
                grp[cid[mstar]].push_back(mstar);
            }
        }

        if (c == 1) {
            vector<char> isT(K + 1, 0);
            for (int v : O) isT[v] = 1;
            for (int f : F) isT[f] ^= 1;
            for (int v = 1; v <= K; ++v)
                if (isT[v] && present[v]) grp[0].push_back(v);
        }

        // összekötés: mindig a legkevesebb és a legtöbb egységű csoportot kötjük össze
        set<pair<size_t, int>> st;
        for (int z = 0; z < c; ++z) if (!grp[z].empty()) st.insert({grp[z].size(), z});
        vector<pair<int, int>> pairs;
        while (st.size() > 1) {
            int a = st.begin()->second;
            int b = prev(st.end())->second;
            st.erase(st.begin());
            st.erase(prev(st.end()));
            int x = grp[a].back(); grp[a].pop_back();
            int y = grp[b].back(); grp[b].pop_back();
            pairs.push_back({x, y});
            if (grp[a].size() < grp[b].size()) swap(grp[a], grp[b]);
            grp[a].insert(grp[a].end(), grp[b].begin(), grp[b].end());
            vector<int>().swap(grp[b]);
            if (!grp[a].empty()) st.insert({grp[a].size(), a});
        }
        // a maradék egységeket párosítjuk (a komponensek már összekötve vannak)
        vector<int> rest;
        for (int z = 0; z < c; ++z) rest.insert(rest.end(), grp[z].begin(), grp[z].end());
        for (size_t i = 0; i + 1 < rest.size(); i += 2) pairs.push_back({rest[i], rest[i + 1]});

        long long sum = 0;
        for (auto &p : pairs) sum += (long long)p.first + p.second;
        out += to_string(sum) + " " + to_string(pairs.size());
        for (auto &p : pairs) out += " " + to_string(p.first) + " " + to_string(p.second);
        out += "\n";
    }
    cout << out;
    return 0;
}
